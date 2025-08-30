#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include "ralloc.h"

#define PROT_READ_WRITE (PROT_READ | PROT_WRITE)
#define MAP_FLAGS (MAP_PRIVATE | MAP_ANONYMOUS)

void *rallocmem(size_t size) {
    if (size == 0) return NULL;

    size_t total_size = sizeof(ralloc_header_t) + size;

    void *block;
    long map_flags = MAP_FLAGS;

    __asm__ volatile (
    "mov %1, %%rax\n" // syscall numb for mmap
    "xor %%rdi, %%rdi\n" // addr
    "mov %2, %%rsi\n" // length
    "mov %3, %%rdx\n" // prot = PROT_READ | PROT_WRITE
    "mov %4, %%r10\n" // flags = MAP_PRIAVTE | MAP_ANONYMOUS
    "mov $-1, %%r8\n" // fd = -1
    "xor %%r9, %%r9\n" // offset = 0
    "syscall\n"
    "mov %%rax, %0\n" // storing result in addr
    : "=m" (block) // out 
    : "i" (SYS_MMAP), "r" (total_size), "i" (PROT_READ_WRITE), "r" (map_flags)
    : "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9", "memory"
    );

    if (block == MAP_FAILED) {
        perror("rallocmem : map failed\n");
        return NULL;
    }

    ralloc_header_t *header = (ralloc_header_t *)block;
    header->size = size;
    header->magic = MAGIC_NUMBER;
   
    return (void *)(header + 1);
}

void rallocfree(void *ptr) {
    if (ptr == NULL) return;

    // Getting the header by moving back from the pointer
    ralloc_header_t *header = (ralloc_header_t *)ptr - 1;
    
    // magic number integrity check
    if (header->magic != MAGIC_NUMBER) {
        fprintf(stderr, "rallocfree: invalid pointer or memory corruption detected\n");
        return;
    }

    void *original_block = (void*)header;
    size_t total_size = sizeof(ralloc_header_t) + header->size;

    int result;
    __asm__ volatile (
    "mov %1, %%rax\n" //syscall numb for munmap
    "mov %2, %%rdi\n" // original_block addr
    "mov %3, %%rsi\n" // total_size
    "syscall\n"
    "mov %%eax, %0\n" // storing result
    : "=m" (result) // output
    : "i" (SYS_MUMMAP), "r" (original_block), "r" (total_size)
    : "rax", "rdi", "rsi", "memory"
    );

    if (result != 0) {
        perror("rallocfree: munmap failed\n");
    }
}
   

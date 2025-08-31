#ifndef RALLOC_H_
#define RALLOC_H_

#include <stddef.h> // size_t

#define SYS_MMAP 9
#define SYS_MUNMAP 11
#define MAGIC_NUMBER 0xDEADBEEF

typedef struct {
    size_t size;
    int magic; // magic numb for integrity checks (for practice)
} ralloc_header_t;

typedef struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
    size_t magic;
} block_meta;

void *rallocmem(size_t size);
void rallocfree(void *ptr);
void *rreallocmem(void *ptr, size_t size);
void *rallocmemcpy(void *dest, void *src, size_t n);

#endif

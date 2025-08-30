#ifndef RALLOC_H_
#define RALLOC_H_

#include <stddef.h> // size_t

#define SYS_MMAP 9
#define SYS_MUMMAP 11
#define MAGIC_NUMBER 0xDEADBEEF

typedef struct {
    size_t size;
    int magic; // magic numb for integrity checks (for practice)
} ralloc_header_t;


void *rallocmem(size_t size);
void rallocfree(void *ptr);

#endif

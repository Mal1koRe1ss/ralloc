# ralloc

**ralloc** is a custom memory allocator built in C with x86-64 assembly integrations, designed as a learning project to understand how memory allocators work at a low level.

## Features
- Pure C and x86-64 assembly implementation
- Linux `mmap` and `munmap` syscalls for memory management
- Header-embedded metadata for allocation tracking
- Magic number validation for detecting memory corruption

## Installation & Usage

### Method 1: Install Header System-Wide
```bash
git clone https://github.com/Mal1koRe1ss/ralloc.git
cd ralloc
sudo mv ./src/ralloc.h /usr/include/
```
Now, you can include the allocator in your projects with:
```c
#include <ralloc.h>
```
You only need to compile with `ralloc.c`.

### Method 2: Use Locally in Your Project
```bash
git clone https://github.com/Mal1koRe1ss/ralloc.git
cp ./src/ralloc.h ./src/ralloc.c /your/project/directory/
```
Include the header in your code:
```c
#include "ralloc.h"
```

## Compilation
Compile your project with `ralloc.c`:
```bash
gcc your_program.c ralloc.c -o your_program
```
> **Note for MSVC Users**: Replace `__asm__` with `__asm` in the source code for MSVC compatibility.

## API
- `void *rallocmem(size_t size)`: Allocates `size` bytes of memory.
- `void rfree(void *ptr)`: Frees memory previously allocated by `rallocmem`.

## Roadmap

### Essential Features
- [ ] Proper alignment handling
- [ ] `rreallocmem()` implementation
- [ ] `rcallocmem()` implementation

### Performance Improvements
- [ ] Free list management
- [ ] Size classes for reduced fragmentation

### Safety & Debugging
- [ ] Boundary tags for overflow detection
- [ ] Allocation statistics tracking
- [ ] Thread safety (mutex support)

### Testing
- [ ] Comprehensive test suite
- [ ] Benchmarking against system allocator

## License

[MIT LICENSE](./LICENSE)

section .text
    global _start

_start:
    mov eax, 45        ; sys_brk
    xor ebx, ebx       ; ebx = 0
    int 0x80           ; call kernel

    add eax, 16384     ; reserve 16KB
    mov ebx, eax
    mov eax, 45        ; sys_brk
    int 0x80           ; call kernel

    cmp eax, 0
    jl exit            ; exit if error

    mov edi, eax       ; edi = highest available address
    sub edi, 4         ; point to the last DWORD
    mov ecx, 4096      ; number of DWORDs allocated
    xor eax, eax       ; clear eax
    std                ; backward direction
    rep stosd          ; zero out the allocated memory
    cld                ; restore direction flag

exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80

;; This code is AI written btw, no need to compile this. Just understanding it is enough...

section .text
    global _start

; Syscall numbers
SYS_MMAP   equ 9    ; mmap syscall number
SYS_EXIT   equ 60   ; exit syscall number

; mmap constants
PROT_READ     equ 1
PROT_WRITE    equ 2
MAP_PRIVATE   equ 0x02
MAP_ANONYMOUS equ 0x20

_start:
    ; --- mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) ---
    mov rax, SYS_MMAP      ; syscall number
    xor rdi, rdi           ; address (NULL = let kernel choose)
    mov rsi, 4096          ; length (1 page = 4096 bytes)
    mov rdx, PROT_READ | PROT_WRITE  ; protection
    mov r10, MAP_PRIVATE | MAP_ANONYMOUS ; flags
    mov r8, -1             ; fd (-1 for anonymous memory)
    xor r9, r9             ; offset (0)
    syscall

    ; rax now contains the allocated memory address
    ; Or -1 (0xffffffffffffffff) on error

    ; --- Exit program ---
    mov rax, SYS_EXIT
    xor rdi, rdi           ; exit code 0
    syscall

;; This one is AI generated too...

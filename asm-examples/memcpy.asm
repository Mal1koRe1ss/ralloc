section .text
    global r_memcpy

; void* r_memcpy(void* dest, const void* src, size_t n);
;   rdi - dest (destination pointer)
;   rsi - src (source pointer)
;   rdx - n (number of bytes to copy)
;   output -> rax - original dest pointer

r_memcpy:
    mov rax, rdi        ; Save the original dest pointer to return it later.

    test rdx, rdx       ; Check if n == 0
    jz .end             ; If zero, we're done.

.loop:
    mov cl, [rsi]       ; Load a byte from src into cl (8-bit register)
    mov [rdi], cl       ; Store that byte into dest

    inc rsi             ; Move to next byte in src
    inc rdi             ; Move to next byte in dest
    dec rdx             ; Decrement the counter (n)

    jnz .loop           ; If n != 0, repeat

.end:
    ret                 ; Return (rax already holds the dest pointer)

;; this one is AI generated too. Don't get me wrong, currently i don't know assembly. I get assembly codes from the AI, only when i need them. I also try to implement them on my own.

bits 64

section .data
section	.text

extern      ft_strlen
extern      malloc
extern      __errno_location
extern      ft_strcpy

global      ft_strdup

ft_strdup:
    push	rbp
    push    r12
    mov		rbp, rsp

    call    ft_strlen
    inc     rax
    mov     r12, rdi
    mov     rdi, rax
    call    malloc wrt ..plt
    or      rax, rax
    js      .error
    mov     rsi, r12
    mov     rdi, rax
    call    ft_strcpy
    pop     r12
    pop     rbp
    ret

    .error:
        neg     rax
        mov     rdx, rax
        call    __errno_location
        pop     r12
        pop     rbp
        xor     rax, rax
        ret


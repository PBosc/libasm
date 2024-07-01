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
    mov		rbp, rsp

    call    ft_strlen
    inc     rax
    mov     r8, rdi
    mov     rdi, rax
    call    malloc
    or      rax, rax
    js      .error
    mov     rsi, r8
    mov     rdi, rax
    call    ft_strcpy
    pop     rbp
    ret

    .error:
        neg     rax
        mov     rdx, rax
        call    __errno_location
        pop     rbp
        xor     rax, rax
        ret


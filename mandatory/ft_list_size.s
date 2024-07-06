bits 64

section .data
section	.text

extern  malloc

extern  __errno_location

global	ft_list_size

ft_list_size:
    push	rbp
    mov		rbp, rsp
    push    rdi
    ; rdi = t_list **begin_list
    xor     rax, rax
    .loop:
        cmp     rdi, 0
        je      .end
        mov     rdi, [rdi + 8]
        inc     rax
        jmp     .loop

    .end:
        pop     rdi
        pop     rbp
        ret

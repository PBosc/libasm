bits 64


section .data
section	.text

extern  __errno_location

global	ft_write

ft_write:
    mov     rax, 1
    syscall
    test    rax,rax
    js      .error
    ret
    .error:
        neg rax
        mov rdx, rax
        call [rel __errno_location wrt ..got]
        mov [rax], rdx
        mov rax, -1
        ret
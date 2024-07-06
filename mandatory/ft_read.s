bits 64


section .data
section	.text

extern  __errno_location

global	ft_read

ft_read:
    mov     rax, 0
    syscall
    test    rax,rax
    js      .error
    ret
    .error:
        neg rax
        mov rdx, rax
        call __errno_location
        mov [rax], rdx
        mov rax, -1
        ret
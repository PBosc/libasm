bits 64

section .data
section	.text

extern  malloc

extern  __errno_location

global	ft_list_push_front

ft_list_push_front:
    push	rbp
    mov		rbp, rsp
    ; rdi = t_list **begin_list
    ; rsi = void *data
    ; test    rsi, rsi
    ; jz      .end
    call    ft_create_elem
    test    rax, rax
    jz      .end
    mov     rdx, QWORD [rdi]
    mov     [rax + 8], rdx
    mov     QWORD [rdi], rax

    .end:
        pop     rbp
        ret

ft_create_elem:
    push    rbp
    mov     rbp, rsp
    push    rsi
    push    rdi

    xor     rax, rax
    mov     rdi, 16
    call    malloc
    test    rax, rax
    jz      .error
    pop     rdi
    pop     rsi
    mov     QWORD [rax], rsi
    mov     QWORD [rax + 8], 0
    jmp     .end

    .error:
        call    __errno_location
        pop     rbp
        ret
    .end:
        pop     rbp
        ret

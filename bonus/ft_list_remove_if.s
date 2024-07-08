bits 64

section .data
section	.text

extern  malloc
extern  free

extern  __errno_location

global	ft_list_remove_if

; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))

ft_list_remove_if:
    push	rbp
    mov		rbp, rsp
    push    rdi
    ; rdi = t_list **begin_list rsi = void *data_ref rdx = int (*cmp)() rcx = void (*free_fct)(void *)
    mov     r12, rdx    ; r12 = int (*cmp)()
    mov     r13, rcx    ; r13 = void (*free_fct)(void *)
    xor     rax, rax
    mov     r15, rdi
    mov     rdi, [rdi]  ; rdi = *begin_list
    mov     r14, rdi    ; r14 = prev
    .loop:
        cmp     QWORD rdi, 0
        je      .end
        push    rdi
        push    rsi
        mov     rdi, QWORD [rdi]  ; rdi = list->data
        ; mov     rdi, [rdi]
        call    r12
        pop     rsi
        pop     rdi
        test    rax, rax
        jz      .remove
        mov     r14, rdi
        mov     rdi, [rdi + 8]
        jmp     .loop
    .remove:
        push    rdi
        push    rsi
        cmp     r14, rdi
        je      .remove_head
        mov     r8, QWORD [rdi + 8]
        mov     [r14 + 8], r8
        mov     rdi, [rdi]
        call    r13
        pop     rsi
        pop     rdi
        push    rdi
        call    free
        pop     rdi
        mov     rdi, [r14 + 8]
        jmp     .loop
    .remove_head:
        mov     rdi, [rdi]
        call    r13
        pop     rsi
        pop     rdi
        mov     r14, [rdi + 8]
        push    rdi 
        call    free
        pop     rdi
        mov     rdi, r14
        mov     [r15], rdi
        jmp     .loop
    .end:
        pop     rdi
        pop     rbp
        ret

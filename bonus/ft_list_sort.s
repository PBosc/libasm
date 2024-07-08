bits 64

section .data
section	.text

extern  malloc

extern  __errno_location
extern  ft_list_size
extern  ft_swap

global	ft_list_sort

ft_list_sort:
    push	rbp
    mov		rbp, rsp
    ; rdi = t_list **begin_list rsi = int (*cmp)()
    push    rdi
    push    rsi
    mov     rdi, [rdi]
    call    ft_list_size
    pop     rsi
    pop     rdi
    mov     rcx, rax
    mov     rdi, [rdi]
    mov     r12, rsi
    .loop:
        cmp     rcx, 1
        jl      .end
        mov     r8, rdi
        .loop2:
            cmp     qword [r8 + 8], 0
            je      .loop_inc
            push    r8
            push    rdi
            push    rcx
            mov     rdi, [r8 + 8]
            mov     rdi, [rdi]
            mov     rsi, [r8]
            call    r12
            .b:
            pop     rcx
            pop     rdi
            pop     r8
            cmp     eax, 0
            jle      .swap
            mov     r8, [r8 + 8]
            jmp     .loop2
        .loop_inc:
            dec    rcx
            jmp     .loop
        .swap:
            mov r9, [r8]        ; Load the first pointer into r9
            mov r10, [r8 + 8]    ; Load the second pointer into r10
            mov r10, [r10]
            mov [r8], r10        ; Store the second pointer at the address r8
            mov r10, [r8 + 8]
            mov [r10], r9    ; Store the first pointer at the address r8 + 8
            mov r8, [r8 + 8]
            jmp .loop2
        .end:
            pop     rbp
            ret

ft_swap:
    mov r8, rdi
    mov r11, rsi
    mov r9, r8        ; Load the first pointer into r9
    mov r10, r11    ; Load the second pointer into r10
    mov rdi, r10        ; Store the second pointer at the address r8
    mov rsi, r9    ; Store the first pointer at the address r8 + 8
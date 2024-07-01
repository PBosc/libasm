bits 64

section .data
section	.text

extern  ft_strlen

global	ft_atoi_base

ft_atoi_base:
	push	rbp
	mov		rbp, rsp

	; rdi = str ; rsi = base
	; rax = result ; r12 = sign ; rcx = i ; rdx = len

    xor		rax, rax
    mov     r12, 1
    xor     rdx, rdx
    call    ft_strlen
    mov     rdx, rax
    test    rdx, rdx
    jz      .end
    mov     rcx, -1
    .skip_blanks:
        inc     rcx
        mov     al, [rdi + rcx]
        cmp     al, 32
        je      .skip_blanks
        cmp     al, 9
        je      .skip_blanks
        cmp     al, 10
        je      .skip_blanks
        cmp     al, 13
        je      .skip_blanks
        cmp     al, 43
        je      .set_sign
        cmp     al, 45
        jne     .set_sign
        neg     r12
        jmp     .skip_blanks
    .set_sign:
        cmp     al, 45
        je      .set_neg
        cmp     al, 43
        jne      .check_base
        inc     rcx
        jmp     .set_sign
    .set_neg:
        inc     rcx
        neg     r12
        jmp     .set_sign

    .check_base:
        push    rdi
        mov     rdi, rsi
        call    ft_strlen
        pop     rdi
        cmp     rax, 2
        jl      .error
        .loop:
            mov     al, [rsi]
            cmp     al, 0

            inc     rsi
            jmp     .loop


    .error:
        mov     rax, 0
        jmp     .end
    .end:
        pop     rbp
        ret
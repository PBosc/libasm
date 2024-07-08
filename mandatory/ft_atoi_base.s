bits 64

section .data
section	.text

extern  ft_strlen

global	ft_atoi_base

check_base:
    xor     rcx, rcx
    cmp     rsi, 0
    je      .error
    .loop:
        cmp     byte [rsi + rcx], 0
        je      .end
        cmp     byte [rsi + rcx], 43
        je      .error
        cmp     byte [rsi + rcx], 45
        je      .error
        cmp     byte [rsi + rcx], 9
        je      .error
        cmp     byte [rsi + rcx], 10
        je      .error
        cmp     byte [rsi + rcx], 11
        je      .error
        cmp     byte [rsi + rcx], 12
        je      .error
        cmp     byte [rsi + rcx], 13
        je      .error
        cmp     byte [rsi + rcx], 32
        je      .error

        mov     r8, rcx
        .loop2:
            inc     r8
            cmp     byte [rsi + r8], 0
            je      .continue_loop
            mov     r10, [rsi + rcx]
            cmp     byte r10b, [rsi + r8]
            je      .error
            jmp     .loop2
    .continue_loop:
        inc     rcx
        jmp     .loop
    .end:
        cmp     rcx, 1
        jle     .error
        mov     rax, rcx
        ret
    .error:
        mov     rax, -1
        ret
    ret

get_sign:
    mov     rax, 1
    .skip_spaces:
		cmp		BYTE [rdi + rcx], 32
		je		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 13
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 12
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 11
		je 		.continue_skip_spaces
		cmp 	BYTE [rdi + rcx], 10
		je 		.continue_skip_spaces
		cmp		BYTE [rdi + rcx], 9
		je		.continue_skip_spaces
        jmp     .sign

		.continue_skip_spaces:
			inc		rcx
			jmp		.skip_spaces
        .sign:
            cmp     byte [rdi + rcx], 45
            je      .negative
            cmp     byte [rdi + rcx], 43
            je      .positive
            ret
        .positive:
            inc     rcx
            jmp    .sign
        .negative:
            neg     rax
            inc     rcx
            jmp    .sign
    mov rax, 1
    ret

char_in_base:
    mov     rax, [rdi + rcx]
    mov     r9, rsi
    xor     r8, r8
    .loop:
        cmp     byte al, [r9 + r8]
        je      .found
        inc     r8
        cmp     byte [r9 + r8], 0
        jne     .loop
        mov     rax, -1
        ret
    .found:
        mov     rax, r8
        ret
    ret

ft_atoi_base:
	push	rbp
	mov		rbp, rsp

	; rdi = str ; rsi = base
	; rax = result ; r12 = sign ; rcx = i ; rdx = len

    mov		r12, 1
    xor     rcx, rcx
    xor     rax, rax
    cmp     rdi, 0
    je      .error
    call    check_base
    cmp     rax, 2
    jl     .error
    mov     rdx, rax
    xor     rcx, rcx
    call    get_sign
    mov     r12, rax
    xor     rax, rax
    .loop:
        cmp     byte [rdi + rcx], 0
        je      .end
        push    rax
        call    char_in_base
        mov     r8, rax
        pop     rax
        cmp     r8, -1
        je      .end
        imul    rax, rdx
        add     rax, r8
        inc     rcx
        jmp     .loop
    .error:
        mov     rax, 0
        pop     rbp
        ret

    .end:
        imul    rax, r12
        pop     rbp
        ret
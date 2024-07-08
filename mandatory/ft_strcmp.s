bits 64

section .data
section	.text

global	ft_strcmp

ft_strcmp:
    push	rbp
	push	rcx
	push	rdi
    mov		rbp, rsp

	xor		rcx, rcx
    xor     r8, r8
	xor		rax, rax

	loop:
		mov		rax, [rsi + rcx]
		cmp		byte [rdi + rcx], al
        jne     end
		cmp		al, byte 0
		je		end
		inc		rcx
		jmp		loop

	end:
		xor		r8, r8
        mov     r8b, [rdi + rcx]
		xor		r9, r9
		mov		r9b, al
		sub     r8d, r9d
		xor		rax, rax
        mov     eax, r8d
		pop		rdi
		pop		rcx
		pop		rbp
		ret
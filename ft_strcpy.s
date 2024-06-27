bits 64

section .data
section	.text

global	ft_strcpy

ft_strcpy:
    push	rbp
    mov		rbp, rsp

	xor		rcx, rcx

	loop:
		mov		al, [rsi + rcx]
		mov		[rdi + rcx], al
		inc		rcx
		cmp		al, byte 0
		je		end
		jmp		loop

	end:
		mov		rax, rdi
		pop		rbp
		ret
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
        mov     r8, [rdi + rcx]
		sub     r8, rax
		xor		rax, rax
        mov     eax, r8d
		pop		rdi
		pop		rcx
		pop		rbp
		ret
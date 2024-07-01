bits 64

section .data
section	.text

global	ft_strcmp

ft_strcmp:
    push	rbp
    mov		rbp, rsp

	xor		rcx, rcx
    xor     r8, r8

	loop:
		mov		al, [rsi + rcx]
		cmp		[rdi + rcx], al
        jne     end
		inc		rcx
		cmp		al, byte 0
		je		end
		jmp		loop

	end:
        mov     r8b, [rdi + rcx]
		sub     r8b, al
        mov     rax, r8
		pop		rbp
		ret
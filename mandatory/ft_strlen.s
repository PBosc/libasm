BITS 64
section .data

section .bss

section .text
global ft_strlen


bits 64

section .data
section	.text

global	ft_strlen

ft_strlen:
    push	rbp
    mov		rbp, rsp

	xor		rcx, rcx

	loop:
        cmp     byte [rdi + rcx], 0
		je		end
		inc		rcx
		jmp		loop

	end:
		mov		rax, rcx
		pop		rbp
		ret
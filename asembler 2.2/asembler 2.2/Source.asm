.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
public _main
.data
	bufor1 db '9',0
	bufor2 db ?

.code

_main:

	mov esi, offset bufor1
	mob edi, offset bufor2
	xor al, al
	mov ecx, bufor1 - bufor2 - 1

ptl:
	mov al, [esi]
	mov [edi], al
	inc esi 
	inc edi 
	cmp esi, byte PTR 0
	jnz ptl

	

	 


push 0
call _ExitProcess@4

END
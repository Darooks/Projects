.686
.model flat
extern	_ExitProcess@4		:	PROC
extern	__write				:	PROC
extern	__read				:	PROC
extern	_MessageBoxW@16		:	PROC
public	_main

.data
tytul			db 'Tekst do wy',9Ch,'wietlenia',0
tekst_pocz		db  10, 'Prosz',169,' napisa',134,' jaki',152,' tekst ' 
				db	'i nacisnac Enter', 10

koniec_t		db	?
magazyn			db 80 dup (?)
magazynUni		db 160 dup (?)
nowa_linia		db 10
liczba_znakow	dd ?

.code
_main:

		mov	ecx, (OFFSET koniec_t) - (OFFSET tekst_pocz)
		push ecx
		push OFFSET tekst_pocz
		push 1
		call __write

		add esp, 12

		push 80
		push OFFSET magazyn
		push 0
		call __read
		add esp, 12

		mov liczba_znakow, eax
		mov ecx, eax
		mov ebx, 0

ptl:	mov dl, magazyn[ebx]

		cmp dl, 0A5h
		je zamianaA
		cmp dl, 86h
		jz zamianaC
		cmp dl, 0A9h
		jz zamianaE
		cmp dl, 88h
		jz zamianaL
		cmp dl, 0E4h
		jz zamianaN
		cmp dl, 0A2h
		jz zamianaO
		cmp dl, 98h
		jz zamianaS
		cmp dl, 0BEh
		jz zamianaZ
		cmp dl, 0ABh
		jz zamianaZi

		cmp dl, 'a'
		jb dalej
		cmp dl, 'z'
		ja dalej
		sub dl, 20H
		jmp zamiana

zamianaA: mov magazynUni[si], 04h
		inc si
		mov magazynUni[si], 01h
		jmp	dalej

		zamianaC: mov magazynUni[si], 06h
		inc si
		mov magazynUni[si], 01h
		jmp	dalej
		zamianaE: mov magazynUni[si], 18h 
		inc si
		mov magazynUni[si], 01h
		jmp dalej
		zamianaL: mov magazynUni[si], 41h 
		inc si
		mov magazynUni[si], 01h
		jmp dalej
		zamianaN: mov magazynUni[si], 43h 
		inc si
		mov magazynUni[si], 01h
		jmp dalej
		zamianaO: mov magazynUni[si], 0D3h 
		inc si
		mov magazynUni[si], 00h
		jmp dalej
		zamianaS: mov magazynUni[si], 5Ah 
		inc si
		mov magazynUni[si], 01h
		jmp dalej
		zamianaZ: mov magazynUni[si], 7Bh 
		inc si
		mov magazynUni[si], 01h
		jmp dalej
		zamianaZi: mov magazynUni[si], 79h 
		inc si
		mov magazynUni[si], 01h
		jmp dalej

zamiana:mov magazynUni[si], dl
		inc si
		mov magazynUni[si], 0
dalej:	inc ebx
		inc si
		dec ecx
		jnz ptl

		push 0
		push OFFSET tytul
		push OFFSET magazynUni
		push 0
		call _MessageBoxW@16

		;push liczba_znakow
		;push OFFSET magazyn
		;push 1
		;call __write


		add esp, 12
		push 0
		call _ExitProcess@4

END
.686
.model flat
extern	_ExitProcess@4					:	PROC
extern _GetStdHandle@4					:	PROC
extern _SetConsoleTextAttribute@8		:	PROC
extern	__write							:	PROC
extern	__read							:	PROC

STD_OUTPUT_HANDLE		EQU -11
FOREGROUND_GREEN		EQU 002H
FOREGROUND_INTENSITY	EQU 008H
COLOR					EQU FOREGROUND_GREEN + FOREGROUND_INTENSITY
public	_main

.data
tekst_pocz		db	10, 'Prosze napisac jakis tekst'
				db	'i nacisnac Enter', 10

koniec_t		db	?
magazyn			db 80 dup (?)
nowa_linia		db 10
liczba_znakow	dd ?
handle dd ? 

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
		jz zamianaA

		cmp dl, 'a'
		jb dalej
		cmp dl, 'z'
		ja dalej
		sub dl, 20H
		jmp zamiana

zamianaA: mov dl, 0A4h
		jmp	zamiana

zamiana:mov magazyn[ebx], dl
;-------------------------------------
dalej:	inc ebx
		loop ptl

		push STD_OUTPUT_HANDLE
		call _GetStdHandle@4
		mov handle, eax

		push COLOR
		push handle
		call _SetConsoleTextAttribute@8

		push liczba_znakow
		push OFFSET magazyn
		push 1
		call __write
		add esp, 12

		push 0
		call _ExitProcess@4

END
.686
.model flat
extern	_ExitProcess@4	:	PROC
extern	__write			:	PROC
public	_main			

.data
tekst	db 10, 'Nazywam si', 169, '. . . ', 10
		db 'M', 162, 'j pierwszy 32-bitowy program '
		db 'asemblerowy dzia', 136, 'a', ' ju', 190,' poprawnie!', 10

.code
_main:
	; obliczenie sumy wyraz�w ciagu 3 + 5 + 7 + 9 + 11
	; obliczenie bez uycia petli rozkazowej

	
	mov bl, 5
	mov al, 2
	; mov eax, 5 ; pierwszy element ciagu
	mul bl
	mov	ecx, 5
	add eax, 5 ; dodanie drugiego elementu
	add eax, 7 ; dodanie trzeciego elementu
	add eax, 9 ; dodanie czwartego elementu
	add eax, 11 ; dodanie piatego elementu
	sub eax, 4
	; obliczenie z uyciem petli rozkazowej
	mov eax, 0 ; poczatkowa wartosc sumy
	mov ebx, 3 ; pierwszy element ciagu
	mov ecx, 5 ; liczba obieg�w petli
	ptl: add eax, ebx ; dodanie kolejnego elementu
	add ebx, 2 ; obliczenie nastepnego elementu
	sub ecx, 1 ; zmniejszenie licznka obieg�w petli
	jnz ptl ; skok, gdy licznik obieg�w r�ny od 0
	mov ecx, 85 ; liczba znak�w wyswietlanego tekstu
	; wywo�anie funkcji �write� z biblioteki jezyka C
	push ecx ; liczba znak�w wyswietlanego tekstu
	push dword PTR OFFSET tekst ; po�oenie obszaru

	; ze znakami
	push dword PTR 1 ; uchwyt urzadzenia wyjsciowego
	call __write ; wyswietlenie znak�w

	; (dwa znaki podkreslenia _ )
	add esp, 12 ; usuniecie parametr�w ze stosu

	; zakonczenie wykonywania programu
	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
END
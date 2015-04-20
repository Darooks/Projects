; Program gwiazdki.asm
; Wyswietlanie znak�w * w takt przerwan zegarowych
; Uruchomienie w trybie rzeczywistym procesora x86
; lub na maszynie wirtualnej
; zakonczenie programu po nacisnieciu klawisza 'x'
; asemblacja (MASM 4.0): masm gwiazdki.asm,,,;
; konsolidacja (LINK 3.60): link gwiazdki.obj;

.386
rozkazy SEGMENT use16
ASSUME CS:rozkazy


;============================================================

; procedura obs�ugi przerwania zegarowego

obsluga_zegara PROC

; przechowanie uywanych rejestr�w
push ax
push bx
push es

; wpisanie adresu pamieci ekranu do rejestru ES - pamiec
; ekranu dla trybu tekstowego zaczyna sie od adresu B8000H,
; jednak do rejestru ES wpisujemy wartosc B800H,
; bo w trakcie obliczenia adresu procesor kadorazowo mnoy
; zawartosc rejestru ES przez 16
mov ax, 0B800h ;adres pamieci ekranu
mov es, ax

; zmienna 'licznik' zawiera adres bieacy w pamieci ekranu
mov bx, cs:licznik

; przes�anie do pamieci ekranu kodu ASCII wyswietlanego znaku
; i kodu koloru: bia�y na czarnym tle (do nastepnego bajtu)
mov byte PTR es:[bx], '*' ; kod ASCII
mov byte PTR es:[bx+1], 00000111B ; kolor

; zwiekszenie o 2 adresu bieacego w pamieci ekranu
add bx,2

; sprawdzenie czy adres bieacy osiagna� koniec pamieci ekranu
cmp bx,4000

jb wysw_dalej ; skok gdy nie koniec ekranu
; wyzerowanie adresu bieacego, gdy ca�y ekran zapisany
mov bx, 0

;zapisanie adresu bieacego do zmiennej 'licznik'
wysw_dalej:
mov cs:licznik,bx

; odtworzenie rejestr�w
pop es
pop bx
pop ax

; skok do oryginalnej procedury obs�ugi przerwania zegarowego
jmp dword PTR cs:wektor8

; dane programu ze wzgledu na specyfike obs�ugi przerwan
; umieszczone sa w segmencie kodu
licznik dw 320 ; wyswietlanie poczawszy od 2. wiersza
wektor8 dd ?

obsluga_zegara ENDP
;============================================================
; program g��wny - instalacja i deinstalacja procedury
; obs�ugi przerwan
; ustalenie strony nr 0 dla trybu tekstowego
zacznij:
mov al, 0
mov ah, 5
int 10
mov ax, 0
mov ds,ax ; zerowanie rejestru DS

; odczytanie zawartosci wektora nr 8 i zapisanie go
; w zmiennej 'wektor8' (wektor nr 8 zajmuje w pamieci 4 bajty
; poczawszy od adresu fizycznego 8 * 4 = 32)
mov eax,ds:[32] ; adres fizyczny 0*16 + 32 = 32
mov cs:wektor8, eax

; wpisanie do wektora nr 8 adresu procedury 'obsluga_zegara'
mov ax, SEG obsluga_zegara ; czesc segmentowa adresu
mov bx, OFFSET obsluga_zegara ; offset adresu
cli ; zablokowanie przerwan

; zapisanie adresu procedury do wektora nr 8
mov ds:[32], bx ; OFFSET
mov ds:[34], ax ; cz. segmentowa
sti ;odblokowanie przerwan

; oczekiwanie na nacisniecie klawisza 'x'
aktywne_oczekiwanie:
mov ah,1
int 16H

; funkcja INT 16H (AH=1) BIOSu ustawia ZF=1 jesli
; nacisnieto jakis klawisz
jz aktywne_oczekiwanie

; odczytanie kodu ASCII nacisnietego klawisza (INT 16H, AH=0)
; do rejestru AL
mov ah, 0
int 16H
cmp al, 'x' ; por�wnanie z kodem litery 'x'
jne aktywne_oczekiwanie ; skok, gdy inny znak
; deinstalacja procedury obs�ugi przerwania zegarowego

; odtworzenie oryginalnej zawartosci wektora nr 8
mov eax, cs:wektor8
cli
mov ds:[32], eax ;odes�anie wektora nr 8 do pamieci
sti

; zakonczenie programu
mov al, 0
mov ah, 4CH
int 21H
rozkazy ENDS
nasz_stos SEGMENT stack
db 128 dup (?)
nasz_stos ENDS
END zacznij
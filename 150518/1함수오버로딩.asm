; Listing generated by Microsoft (R) Optimizing Compiler Version 18.00.31101.0 

	TITLE	C:\Users\ioacademy3\Desktop\교육\150518\1함수오버로딩.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?square@@YAHH@Z					; square
PUBLIC	?square@@YANN@Z					; square
PUBLIC	_main
PUBLIC	__real@400a666666666666
EXTRN	__fltused:DWORD
;	COMDAT __real@400a666666666666
CONST	SEGMENT
__real@400a666666666666 DQ 0400a666666666666r	; 3.3
CONST	ENDS
; Function compile flags: /Odtp
; File c:\users\ioacademy3\desktop\교육\150518\1함수오버로딩.cpp
_TEXT	SEGMENT
_b$ = -12						; size = 8
_a$ = -4						; size = 4
_main	PROC

; 11   : void main(){

	push	ebp
	mov	ebp, esp
	sub	esp, 12					; 0000000cH

; 12   : 	int a = square(3);

	push	3
	call	?square@@YAHH@Z				; square
	add	esp, 4
	mov	DWORD PTR _a$[ebp], eax

; 13   : 	double b = square(3.3);

	sub	esp, 8
	movsd	xmm0, QWORD PTR __real@400a666666666666
	movsd	QWORD PTR [esp], xmm0
	call	?square@@YANN@Z				; square
	add	esp, 8
	fstp	QWORD PTR _b$[ebp]

; 14   : }

	xor	eax, eax
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File c:\users\ioacademy3\desktop\교육\150518\1함수오버로딩.cpp
_TEXT	SEGMENT
tv67 = -8						; size = 8
_x$ = 8							; size = 8
?square@@YANN@Z PROC					; square

; 10   : double square(double x) { return x*x; }

	push	ebp
	mov	ebp, esp
	sub	esp, 8
	movsd	xmm0, QWORD PTR _x$[ebp]
	mulsd	xmm0, QWORD PTR _x$[ebp]
	movsd	QWORD PTR tv67[ebp], xmm0
	fld	QWORD PTR tv67[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
?square@@YANN@Z ENDP					; square
_TEXT	ENDS
; Function compile flags: /Odtp
; File c:\users\ioacademy3\desktop\교육\150518\1함수오버로딩.cpp
_TEXT	SEGMENT
_x$ = 8							; size = 4
?square@@YAHH@Z PROC					; square

; 9    :    int square(int x)    { return x*x; }

	push	ebp
	mov	ebp, esp
	mov	eax, DWORD PTR _x$[ebp]
	imul	eax, DWORD PTR _x$[ebp]
	pop	ebp
	ret	0
?square@@YAHH@Z ENDP					; square
_TEXT	ENDS
END

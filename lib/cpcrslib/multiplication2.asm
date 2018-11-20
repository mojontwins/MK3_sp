; Multiplication by 32.
; HL = 32 * E

ld 	l, e
ld 	h, 0

add hl, hl ; 2
add hl, hl ; 4
add hl, hl ; 8
add hl, hl ; 16
add hl, hl ; 32

; Multiplication by generic is slower

;		ld    h, ancho_pantalla_bytes/2
;		LD    L, 0
;		LD    D, L 
;		LD    B, 8
;MULT:  ADD   HL, HL
;       JR    NC, NOADD
;       ADD   HL, DE
;NOADD: DJNZ  MULT	

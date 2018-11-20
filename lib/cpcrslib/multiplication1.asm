; Multiplication by 64
; HL = 64 * E

ld  l, e
ld  h, 0

add hl, hl ; 2
add hl, hl ; 4
add hl, hl ; 8
add hl, hl ; 16
add hl, hl ; 32
add hl, hl ; 64

; Multiplication by generic is slower

;       ld    h, ancho_pantalla_bytes
;       LD    L, 0
;       LD    D, L 
;       LD    B, 8
;MULT:  ADD   HL, HL
;       JR    NC, NOADD
;       ADD   HL, DE
;NOADD: DJNZ  MULT	

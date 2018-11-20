; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins - eliminamos la "cabecera" de los sprites.

XLIB cpc_PutTrSp4x8TileMap2b

XREF tiles_tocados
XREF pantalla_juego					;datos de la pantalla, cada byte indica un tile
XREF posiciones_super_buffer
XREF tiles
XREF ancho_pantalla_bytes 
XREF posicion_inicial_superbuffer

XREF mascara1
XREF mascara2

.cpc_PutTrSp4x8TileMap2b

	;según las coordenadas x,y que tenga el sprite, se dibuja en el buffer 
    ex de,hl	;4
    LD IXH,d	;9
    LD IXL,e	;9 

	;lo cambio para la rutina de multiplicar 
    ld e,(ix+8)		;x
    ld l,(ix+9)		;y

.pasa_bloque_a_sbuffer

.transferir_sprite

	ld h,0
	ld d,h

	; Multiplico HL * 64, offset "Y"
	add hl, hl ; 2
	add hl, hl ; 4
	add hl, hl ; 8
	add hl, hl ; 16
	add hl, hl ; 32
	add hl, hl ; 64
	
	add hl,de 		; sumo offset "X"

	ld de,posicion_inicial_superbuffer
	add hl,de

	;hl apunta a la posición en buffer (destino)
			
	ld e,(ix+0)
    ld d,(ix+1)	;de apunta al sprite

    ; [na_th_an] Comento esta parte porque los sprites ya no incluyen esta cabecera.
	; skip header
	; 
	; inc de
	; inc de
	; ; ;	
	
	ld ixh,8

.loop_alto_map_sbuffer
	ex de,hl

	; DE: buffer
	; HL: sprite

	; El ancho está desenrollado: Hay que procesar y copiar 2 bytes.

	; Esta sección aplica la máscara automática (color transparente)
	
	ld A,(hl)		;sprite
	and $aa
	cp mascara2
	jp z,sig_pixn_der_2
	
	ld b,a 
	ld a,(de)		;fondo
	and $55	
	or b
	ld (de),a 
	
.sig_pixn_der_2
	ld a,(hl) 
	and $55
	cp mascara1
	jp z,pon_buffer_der_2
	
	ld b,a 
	ld a,(de)
	and $aa
	or b
	ld (de),a
	
.pon_buffer_der_2
	INC DE
	INC HL

	;**********************************************
	
	ld A,(hl)
	and $aa			;deja solo los bits a comprobar
	cp mascara2		;los comprueba comparando con mascara2
	jp z,sig_pixn_der_2a

	ld b,a 
	ld a,(de)		;fondo	
	and $55	
	or b
	ld (de),a 

.sig_pixn_der_2a
	ld a,(hl) 
	and $55
	cp mascara1
	jp z,pon_buffer_der_2a
	
	ld b,a 
	ld a,(de)
	and $aa
	or b
	ld (de),a

.pon_buffer_der_2a
	INC DE
	INC HL

	;*************************************************		
		
	dec ixh
	ret z

	EX DE,HL
	;ld b,0
	ld bc, 62
	add HL,BC	
	jp loop_alto_map_sbuffer

; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins - ajustamos a la geometría de 32 columnas

XLIB cpc_ShowTouchedTiles

XREF tiles_tocados
XREF pantalla_juego				; Buffer pantalla
XREF posiciones_super_buffer
XREF posiciones_pantalla

XREF posicion_inicial_area_visible
XREF posicion_inicial_superbuffer
XREF ancho_pantalla_bytes
XREF alto_pantalla_bytes

.cpc_ShowTouchedTiles
	; Recorre la lista de tiles tocados.
	; Copia esos tiles del superbuffer a la pantalla.

	LD IX,tiles_tocados

.bucle_cpc_ShowTouchedTiles	
	LD E,(IX+0)					; Lee un byte de la lista (X)

	LD A,$FF
	CP E
	RET Z 						; Si es $FF, terminamos.

	LD D,(IX+1)					; La lista contiene pares (x,y) (Y)
	INC IX
	INC IX 						; Avanzamos al siguiente par.

.posicionar_superbuffer
	; Usamos DE para obtener un puntero al superbuffer en HL
	SLA d 						; D = Y*2
	LD C,d
	LD B,0
	LD HL,posiciones_super_buffer
	ADD HL,BC 					

	LD C,(HL)
	INC HL
	LD B,(HL)	 				; BC -> fila de tiles en superbuffer
	
	SLA e 						; E = X*2
	LD L,e
	LD H,0  					; HL = X*2
	ADD HL,BC 					; HL -> posición en superbuffer
		
.posicionar_pantalla
	; Buscamos la dirección de pantalla

	PUSH HL 					; Guardamos HL.

	LD C,D						; Remember, D = Y*2
	LD B,0 						; BC = Y*2
	LD HL,posiciones_pantalla
	ADD HL,BC

	LD C,(HL)
	INC HL
	LD B,(HL)	 				; BC -> fila de tiles en pantalla

	LD L,e
	LD H,0						; HL = X*2
	ADD HL,BC 					; HL -> posición en pantalla
		
.transf_bloque_sb_pantalla
	POP DE 						; Sacamos posición en superbuffer a DE
	
	ld a,8
.loop_alto_2
.ancho0

	ex de,hl 					; DE->pantalla, HL->superbuffer
	
.loop_ancho_2		
	ldi
	ldi							; Copia 2 bytes = ancho de un tile

	;;
	;push af
	;xor a
	;ld (de),a
	;inc de
	;ld (de),a
	;inc de
	;pop af
	;;

	; Hemos copiado ya las 8 filas del tile?
	dec a
	JP z,bucle_cpc_ShowTouchedTiles

	; Actualizamos la posición del superbuffer moviéndonos
	; a la siguiente fila:

	LD BC, ancho_pantalla_bytes-2 
	ADD HL,BC

	; Actualizamos la posición en pantalla moviéndonos
	; a la siguiente fila (siguiente octavo!).
	; Añadimos $800 - 2:
		
	EX DE,HL
	LD bC,$07fe
	ADD HL,BC

	; Entiendo que esto de aqui abajo no pasará nunca! 
	; Estamos pintando todo un tile alineado a rejilla, jamás
	; va a pasar esto si nuestro área visible está alineada a
	; caracteres, como es el caso. Así que me lo fumou.
	jp loop_alto_2

;	jp nc,loop_alto_2
;	;si no desborda va a la siguiente linea
;	ld bc,$c050
;	add HL,BC
;.yep		
;	;EX DE,HL
;	jp loop_alto_2	

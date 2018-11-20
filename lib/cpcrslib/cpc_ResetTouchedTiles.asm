; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_ResetTouchedTiles

XREF tiles_tocados
 
.cpc_ResetTouchedTiles
	LD HL,tiles_tocados
	;LD DE,tiles_tocados+1
	;LD BC,149
	LD (HL),$FF
	;LDIR
	RET
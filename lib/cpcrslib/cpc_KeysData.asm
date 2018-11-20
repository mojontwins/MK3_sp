; ******************************************************
; **       Librer�a de rutinas para Amstrad CPC       **
; **	   Ra�l Simarro, 	  Artaburu 2009       **
; ******************************************************

XLIB cpc_KeysData

XDEF tabla_teclas
XDEF keymap

.cpc_KeysData


.keymap0 defs 10

;.teclado defb 0		;Este byte indicar� qu� teclas han sido pulsadas 
			;despu�s de un ciclo de exploraci�n
;x.linea defb 0
;x.bte defb 0
.tecla_0 defw $0204
;teclado_usable	; teclas del cursor, cada tecla est� definida por su bit y su l�nea.
.tabla_teclas0
.tecla_0_x defw $4002	; bit 0, l�nea 2
.tecla_1_x defw $4101	; bit 1, l�nea 1
.tecla_2_x defw $4001		; bit 0, l�nea 1
.tecla_3_x defw $4004		; bit 0, l�nea 4
.tecla_00_x defw $ffff	; bit 0, l�nea 2
.tecla_01_x defw $ffff	; bit 1, l�nea 1
.tecla_02_x defw $ffff		; bit 0, l�nea 1
.tecla_03_x defw $ffff		; bit 0, l�nea 4
.tecla_04_x defw $ffff		; bit 0, l�nea 4
.tecla_05_x defw $ffff		; bit 0, l�nea 4
.tecla_06_x defw $ffff		; bit 0, l�nea 4
.tecla_07_x defw $ffff		; bit 0, l�nea 4

; For increasing keys available just increase this word table
defb 0
;DEFC linea_a_buscar = linea_a_buscar0

DEFC tabla_teclas = tabla_teclas0
DEFC keymap = keymap0
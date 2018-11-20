// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// System Initializacion file

void halt_me (void) {
	#asm
		halt
		halt
		halt
		halt
		halt
	#endasm
}

void system_init (void) {
	#asm
		di
	#endasm

	#ifndef TAPE
		// Decompress ARKOS player and SFX
		// The binary ARKOS+SFX is loaded @ BASE_MUSIC
		// Which is the buffer where we descompress music later on

		unpack ((unsigned char *) (BASE_MUSIC+SIZE_ARKOS_COMPRESSED), (unsigned char *) (BASE_SFX));
		unpack ((unsigned char *) (BASE_MUSIC), (unsigned char *) (BASE_ARKOS));		
	#endif

	// Init arkos (turn it off, in fact!)

	#asm
		; Turn off arkos play routine
		ld a, 201				; Insert a RET!
		ld (PLY_PLAY), a
	#endasm

	// Init interrupts

	#asm
		ld a, 195
		ld (0x38), a

		ld hl,(0x0039)
		ld (_int_original),HL 

		ld HL,_interrupcion
		ld (0x0039),HL
		
		jp term
	._int_original  
		defw 0
	._interrupcion
		push af

		ld a, (_arkc)
		inc a

		cp 6
		jp nz, _noplayer

		push bc
		push hl
		push de
		exx
		push bc
		push hl
		push de
		push af
		push ix
		push iy

		call PLY_PLAY

		pop iy
		pop ix
		pop af 
		pop de 
		pop hl 
		pop bc
		exx
		pop de 
		pop hl 
		pop bc 

		xor a
	._noplayer
		ld (_arkc), a

		ld a, (_isrc)
		inc a
		ld (_isrc), a
		pop af
		ei
		ret
	.term
	#endasm
	//halt_me ();

	// Border 0

	#asm
		ld 	a, 0x54
		ld  bc, 0x7F11
		out (c), c
		out (c), a
	#endasm
		
	// Default keys

	cpc_AssignKey (KEY_LEFT, 		0x4820);      // A
	cpc_AssignKey (KEY_RIGHT, 		0x4720);      // D
	cpc_AssignKey (KEY_DOWN, 		0x4710); 	  // S
	cpc_AssignKey (KEY_UP, 			0x4708);      // W

	cpc_AssignKey (KEY_BUTTON_A,	0x4440);      // M
	cpc_AssignKey (KEY_BUTTON_B, 	0x4540);      // N
	
	cpc_AssignKey (KEY_ESC, 0x4804);		// ESC
	cpc_AssignKey (KEY_ENTER, 0x4204);		// ENTER

	// Set palette

	gpit = 16; while (gpit --) cpc_SetColour (gpit, my_inks [gpit]);
	//halt_me ();

	// Set mode

	cpc_SetMode (0);

	// Set tweaked mode 
	// (thanks Augusto Ruiz for the code & explanations!)
	
	#asm
		; Horizontal chars (32), CRTC REG #1
		ld    b, 0xbc
		ld    c, 1			; REG = 1
		out   (c), c
		inc   b
		ld    c, 32			; VALUE = 32
		out   (c), c

		; Horizontal pos (42), CRTC REG #2
		ld    b, 0xbc
		ld    c, 2			; REG = 2
		out   (c), c
		inc   b
		ld    c, 42			; VALUE = 42
		out   (c), c

		; Vertical chars (24), CRTC REG #6
		ld    b, 0xbc
		ld    c, 6			; REG = 6
		out   (c), c
		inc   b
		ld    c, 24			; VALUE = 24
		out   (c), c
	#endasm

	// Sprite allocation

	gpit = SW_SPRITES_ALL; while (gpit --) {		
		sp_sw [gpit].sp0 = (int) (ss_main);
		sp_sw [gpit].sp1 = (int) (ss_main);
		sp_sw [gpit].move = 0;
		sp_sw [gpit].cx = sp_sw [gpit].ox = 0;
		sp_sw [gpit].cy = sp_sw [gpit].oy = 0;
	}

	//halt_me ();

	#asm
		ei
	#endasm
}

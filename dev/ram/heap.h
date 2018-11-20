// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Reserves static space for everything.

// Look at the size of each kind of your *un*compressed files
// And give proper values to:
#define MAX_MAP_SIZE            2048
#define MAX_DECOS_SIZE          256
#define MAX_LOCKS_SIZE          16
#define MAX_ENEMS_SIZE          184 //256

// Tileset
extern const unsigned char ts [0];
extern const unsigned char tsmaps [0];
extern const unsigned char behs [0];

// Spriteset
extern const unsigned char ss [0];
extern const unsigned char ss_main [0];
extern const unsigned char ss_enems [0];
extern const unsigned char ss_extra [0];
extern const unsigned char ss_small [0];
#ifdef CPC
	extern const unsigned char ss_empty [0];
#endif	

// Map data
extern const unsigned char map [0];
#ifdef ENABLE_DECOS	
extern const unsigned char decos [0];
#endif
#ifdef HOTSPOT_TYPE_KEY
extern const unsigned char locks [0];
#endif

// Enems data
extern const unsigned char enems [0];

// Hotspots
extern const unsigned char hotspots [0];

// Custom fixed screens
extern const unsigned char title_rle [0];
extern const unsigned char ending_rle [0];

#asm
	;; Patterns and tilemaps for the metatileset
	
	#ifdef SPECCY
		._ts
			; First, the main font. Must be 64 chars (512 bytes) long.
			; BINARY "../bin/font.bin"
			; Then, space for the remaining 192 characters (1536 bytes).
			; defs 1536
			; In this game, theres only one level and one ts
			BINARY "../ports/zx/bin/ts.bin" ; 2048 bytes
	#endif
	#ifdef CPC 
			; _ts and tiles are defined and XREFd in tilemap_conf.asm	
	#endif		
	
	._tsmaps
		; Space to define up to 48 metatiles (384 bytes).
		; defs 384
		; In this game, there is only one level.
		#ifdef SPECCY
			BINARY "../ports/zx/bin/ts.tilemaps.bin" ; 384 bytes
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/ts.tilemaps.bin" ; 384 byte
		#endif		

	._behs
		; Space to describe up to 48 metatiles (48 bytes).
		; defs 48
		; In this game, there is only one level.
		#ifdef SPECCY
			BINARY "../ports/zx/bin/behs.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/behs.bin"
		#endif

	;; Sprite cells

		#ifdef SPECCY
			._ss
				; Dummy 8 empty (masked) spaces for vertical rotation
				defb 0, 255
				defb 0, 255
				defb 0, 255
				defb 0, 255
				defb 0, 255
				defb 0, 255
				defb 0, 255
				defb 0, 255
		#endif		
	
	._ss_main
		; First, space for / include the main characters
		#ifdef SPECCY		
			; 21 cells, 192 bytes each
			BINARY "../ports/zx/bin/ssch.bin"
		#endif		
		#ifdef CPC
			; 13 cells, 96 bytes each
			BINARY "../ports/cpc/bin/ssch.bin"
		#endif	

		// Custon for this game:
	#ifdef CPC
		._ss_characters
			; 6 cells, 96 bytes each
			BINARY "../ports/cpc/bin/ssge.bin"
	#endif

	#ifdef CPC
		._ss_empty
			; a 100% transparent sprite
			BINARY "../ports/cpc/bin/ssempty.bin"
	#endif	

	._ss_enems
		; Second, space for the enemies / etc.
		; SPRITES_EXTRA_CELLS masked cells (144 * EXTRA_SPRITES)
		#ifdef SPECCY		
			; defs SPRITES_EXTRA_CELLS * 144
			; 8 cells, 144 bytes each
			BINARY "../ports/zx/bin/ssen.bin"
		#endif
		#ifdef CPC
			; defs SPRITES_EXTRA_CELLS * 64
			; 8 cells, 64 bytes each
			BINARY "../ports/cpc/bin/ssen.bin"
		#endif		

	._ss_extra
		; Third, assorted extra stuff
		; Not used in this game
		#ifdef SPECCY		
			; BINARY "../ports/zx/bin/ssextra.bin"
		#endif	
		#ifdef CPC
			; BINARY "../ports/cpc/bin/ssextra.bin"
		#endif		

	._ss_small
		; Small sprites
		#ifdef SPECCY
			; defs SPRITES_SMALL_CELLS * 64
			; 1 cell, 64 bytes
			BINARY "../ports/zx/bin/sssmall.bin"
		#endif
		#ifdef CPC
			; defs SPRITES_SMALL_CELLS * 64
			; 1 cell, 16 bytes
			BINARY "../ports/cpc/bin/sssmall.bin"
		#endif	

	;; Map data + index
	._map
		/*
		#if defined(MAP_FORMAT_RLE53) || defined (MAP_FORMAT_RLE44) || defined (MAP_FORMAT_BYTE_RLE)
				; You can adjust the amount of reserved bytes to the size of your
				; biggest map when it is in its original RLE format.
				defs MAX_MAP_SIZE
		#elif defined (MAP_FORMAT_PACKED)
				defs MAX_PANTS*75
		#elif defined (MAP_FORMAT_UNPACKED)
				defs MAX_PANTS*150
		#endif
		*/
		; there is only one non-destructible level in this game
		#ifdef SPECCY
			BINARY "../ports/zx/bin/map.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/map.bin"
		#endif

	#ifdef ENABLE_DECOS		
		._decos
			; You can adjust the amount of reserved bytes to the size of your
			; biggest set of map decorations.
			defs MAX_DECOS_SIZE
	#endif

	#ifdef HOTSPOT_TYPE_KEY
		._locks
			; You can adjust the amount of reserved bytes to the size of your
			; biggest set of locks.
			; defs MAX_LOCKS_SIZE
			; In this game, there is just one set of locks.			
			#ifdef SPECCY		
				BINARY "../ports/zx/bin/locks.bin"
			#endif
			#ifdef CPC
				BINARY "../ports/cpc/bin/locks.bin"
			#endif
	#endif

	;; Enems data + index
	._enems
		; You can adjust the amount of reserved bytes to the size of you.
		; biggest set of enemies.
		; defs MAX_ENEMS_SIZE
		; there is only one level in this game
		#ifdef SPECCY
			BINARY "../ports/zx/bin/enems.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/enems.bin"
		#endif		

	;; Hotspots

	._hotspots
		; reserve two bytes per screen
		;defs 2*MAX_PANTS
		; there is only one level in this game
		#ifdef SPECCY
			BINARY "../ports/zx/bin/hotspots.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/hotspots.bin"
		#endif	

	;; Fixed screens

	._title_rle
		#ifdef SPECCY
			BINARY "../ports/zx/bin/title.rle.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/title.rle.bin"
		#endif

	._ending_rle
		#ifdef SPECCY
			BINARY "../ports/zx/bin/ending.rle.bin"
		#endif
		#ifdef CPC
			BINARY "../ports/cpc/bin/ending.rle.bin"
		#endif

#endasm

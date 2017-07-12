// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Reserves static space for everything.

// Look at the size of each kind of your *un*compressed files
// And give proper values to:
#define MAX_MAP_SIZE            2048
#define MAX_DECOS_SIZE          256
#define MAX_LOCKS_SIZE          16
#define MAX_ENEMS_SIZE          256

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

// Map data
extern const unsigned char map [0];
#ifdef ENABLE_DECOS	
extern const unsigned char decos [0];
#endif
#ifdef ENABLE_LOCKS
extern const unsigned char locks [0];
#endif

// Enems data
extern const unsigned char enems [0];

// Hotspots
extern const unsigned char hotspots [0];

#asm
	;; Patterns and tilemaps for the metatileset
		; A little marker, for debugging. Should remove
		defb 0x11, 0x22, 0x33, 0x44
	._ts
		; First, the main font. Must be 64 chars (512 bytes) long.
		BINARY "../bin/font.bin"
		; Then, space for the remaining 192 characters (1536 bytes).
		defs 1536
	._tsmaps
		; Space to define up to 64 metatiles (512 bytes).
		defs 512
	._behs
		; Space to describe up to 64 metatiles (64 bytes).
		defs 64

	;; Sprite cells

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
	._ss_main
		; First, space for / include the main characters
		; 8 masked cells (1152 bytes)
		; cells 0-7
		BINARY "../bin/ssmain.bin"
	._ss_enems
		; Second, space for the enemies / etc.
		; SPRITES_EXTRA_CELLS masked cells (144 * EXTRA_SPRITES)
		; cells 8-15
		defs SPRITES_EXTRA_CELLS * 144
	._ss_extra
		; Third, assorted extra stuff
		; Explosion
		; cell 16
		BINARY "../bin/ssextra.bin"
	._ss_small
		; Extra space for projectiles, etc.
		; defs SPRITES_SMALL_CELLS * 64
		BINARY "../bin/sssmall.bin"

	;; Map data + index
	._map
#if defined(MAP_FORMAT_RLE53) || defined (MAP_FORMAT_RLE44) || defined (MAP_FORMAT_BYTE_RLE)
		; You can adjust the amount of reserved bytes to the size of your
		; biggest map when it is in its original RLE format.
		defs MAX_MAP_SIZE
#elif defined (MAP_FORMAT_PACKED)
		defs MAX_PANTS*75
#elif defined (MAP_FORMAT_UNPACKED)
		defs MAX_PANTS*150
#endif
#ifdef ENABLE_DECOS		
	._decos
		; You can adjust the amount of reserved bytes to the size of your
		; biggest set of map decorations.
		defs MAX_DECOS_SIZE
#endif

#ifdef ENABLE_LOCKS
	._locks
		; You can adjust the amount of reserved bytes to the size of your
		; biggest set of locks.
		defs MAX_LOCKS_SIZE
#endif

	;; Enems data + index
	._enems
		; You can adjust the amount of reserved bytes to the size of you.
		; biggest set of enemies.
		defs MAX_ENEMS_SIZE

	;; Hotspots

	._hotspots
		; reserve two bytes per screen
		defs 2*MAX_PANTS
#endasm

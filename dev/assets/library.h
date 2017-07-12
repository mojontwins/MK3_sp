// MTEZX MK3
// Copyleft 2017 by The Mojon Twins

// library

extern const unsigned char level0_ts_patterns_c [0];
#asm
	._level0_ts_patterns_c
		BINARY "../bin/level0/ts.patterns.c.bin"
#endasm

extern const unsigned char level0_ts_tilemaps_c [0];
#asm
	._level0_ts_tilemaps_c
		BINARY "../bin/level0/ts.tilemaps.c.bin"
#endasm

extern const unsigned char level0_behs_c [0];
#asm
	._level0_behs_c
		BINARY "../bin/level0/behs.c.bin"
#endasm

extern const unsigned char level0_ss_c [0];
#asm
	._level0_ss_c
		BINARY "../bin/level0/ss.c.bin"
#endasm

extern const unsigned char level0_map_c [0];
#asm
	._level0_map_c
		BINARY "../bin/level0/map.c.bin"
#endasm

extern const unsigned char level0_enems_c [0];
#asm
	._level0_enems_c
		BINARY "../bin/level0/enems.c.bin"
#endasm

extern const unsigned char level0_hotspots_c [0];
#asm
	._level0_hotspots_c
		BINARY "../bin/level0/hotspots.c.bin"
#endasm

extern const unsigned char level1_ts_patterns_c [0];
#asm
	._level1_ts_patterns_c
		BINARY "../bin/level1/ts.patterns.c.bin"
#endasm

extern const unsigned char level1_ts_tilemaps_c [0];
#asm
	._level1_ts_tilemaps_c
		BINARY "../bin/level1/ts.tilemaps.c.bin"
#endasm

extern const unsigned char level1_behs_c [0];
#asm
	._level1_behs_c
		BINARY "../bin/level1/behs.c.bin"
#endasm

extern const unsigned char level1_ss_c [0];
#asm
	._level1_ss_c
		BINARY "../bin/level1/ss.c.bin"
#endasm

extern const unsigned char level1_map_c [0];
#asm
	._level1_map_c
		BINARY "../bin/level1/map.c.bin"
#endasm

extern const unsigned char level1_enems_c [0];
#asm
	._level1_enems_c
		BINARY "../bin/level1/enems.c.bin"
#endasm

extern const unsigned char level1_hotspots_c [0];
#asm
	._level1_hotspots_c
		BINARY "../bin/level1/hotspots.c.bin"
#endasm

extern const unsigned char level2_ts_patterns_c [0];
#asm
	._level2_ts_patterns_c
		BINARY "../bin/level2/ts.patterns.c.bin"
#endasm

extern const unsigned char level2_ts_tilemaps_c [0];
#asm
	._level2_ts_tilemaps_c
		BINARY "../bin/level2/ts.tilemaps.c.bin"
#endasm

extern const unsigned char level2_behs_c [0];
#asm
	._level2_behs_c
		BINARY "../bin/level2/behs.c.bin"
#endasm

extern const unsigned char level2_map_c [0];
#asm
	._level2_map_c
		BINARY "../bin/level2/map.c.bin"
#endasm

extern const unsigned char level2_enems_c [0];
#asm
	._level2_enems_c
		BINARY "../bin/level2/enems.c.bin"
#endasm

extern const unsigned char level2_hotspots_c [0];
#asm
	._level2_hotspots_c
		BINARY "../bin/level2/hotspots.c.bin"
#endasm

const unsigned char * library [] = {
	level0_ts_patterns_c, 
	level0_ts_tilemaps_c, 
	level0_behs_c, 
	level0_ss_c, 
	level0_map_c, 
	level0_enems_c, 
	level0_hotspots_c, 
	level1_ts_patterns_c, 
	level1_ts_tilemaps_c, 
	level1_behs_c, 
	level1_ss_c, 
	level1_map_c, 
	level1_enems_c, 
	level1_hotspots_c, 
	level2_ts_patterns_c, 
	level2_ts_tilemaps_c, 
	level2_behs_c, 
	level2_map_c, 
	level2_enems_c, 
	level2_hotspots_c
};

#define LEVEL0_TS_PATTERNS_C 0x00
#define LEVEL0_TS_TILEMAPS_C 0x01
#define LEVEL0_BEHS_C 0x02
#define LEVEL0_SS_C 0x03
#define LEVEL0_MAP_C 0x04
#define LEVEL0_ENEMS_C 0x05
#define LEVEL0_HOTSPOTS_C 0x06
#define LEVEL1_TS_PATTERNS_C 0x07
#define LEVEL1_TS_TILEMAPS_C 0x08
#define LEVEL1_BEHS_C 0x09
#define LEVEL1_SS_C 0x0A
#define LEVEL1_MAP_C 0x0B
#define LEVEL1_ENEMS_C 0x0C
#define LEVEL1_HOTSPOTS_C 0x0D
#define LEVEL2_TS_PATTERNS_C 0x0E
#define LEVEL2_TS_TILEMAPS_C 0x0F
#define LEVEL2_BEHS_C 0x10
#define LEVEL2_MAP_C 0x11
#define LEVEL2_ENEMS_C 0x12
#define LEVEL2_HOTSPOTS_C 0x13


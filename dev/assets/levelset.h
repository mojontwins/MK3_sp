// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// levelset.h
// Manually compiled assets lists for levels

// Costomize as needed

// For me each level is:

// ts_patterns
// ts_tilemaps
// behs
// ss
// map
// enems
// hotspots
// ini_x (tiles)
// ini_y (tiles)
// scr_x

#define PLAYER_INI_X	7
#define PLAYER_INI_Y	8
#define PLAYER_SCR_INI	9
#define LEVEL_MAP_W		10

const unsigned char level0 [] = {
	LEVEL0_TS_PATTERNS_C, LEVEL0_TS_TILEMAPS_C, LEVEL0_BEHS_C, 
	LEVEL0_SS_C, LEVEL0_MAP_C, LEVEL0_ENEMS_C, LEVEL0_HOTSPOTS_C,
	3, 3, 0, 10
};

const unsigned char level1 [] = {
	LEVEL1_TS_PATTERNS_C, LEVEL1_TS_TILEMAPS_C, LEVEL1_BEHS_C, 
	LEVEL1_SS_C, LEVEL1_MAP_C, LEVEL1_ENEMS_C, LEVEL1_HOTSPOTS_C,
	2, 5, 0, 10
};

const unsigned char level2 [] = {
	LEVEL2_TS_PATTERNS_C, LEVEL2_TS_TILEMAPS_C, LEVEL2_BEHS_C, 
	LEVEL1_SS_C, LEVEL2_MAP_C, LEVEL2_ENEMS_C, LEVEL2_HOTSPOTS_C,
	2, 2, 0, 0
};

const unsigned char * levels [] = {
	level0, level1, level2
};

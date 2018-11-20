// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Printer

void p_s (unsigned char *s) {
	rdxx = _x;  rdyy = _y;
	while (*s) {
		rdch = *s ++;
		if (rdch == '/') { rdxx = _x;  rdyy ++; } else {
			DRAW_PATTERN (rdxx ++, rdyy, rdc, rdch - 32);
		}
	}
}

#ifdef SPECCY
	#include "engine/printer_speccy.h"
	#define DRAW_TILE 		draw_tile
	#define DRAW_TILE_UPD	draw_tile
#endif
#ifdef CPC
	#include "engine/printer_cpc.h"
	#define DRAW_TILE 		draw_tile
	#define DRAW_TILE_UPD	draw_tile_upd
#endif

void set_map_tile (void) {
	rdf = (_y << 4) | _x;
	scr_buff [rdf] = _t; scr_attr [rdf] = behs [_t];
	_x = SCR_X + (_x << 1); _y = SCR_Y + (_y << 1);
	DRAW_TILE_UPD ();
}

void draw_tile_advance (void) {
	DRAW_TILE (); 
	_x += 2; 
	if (_x == MAP_CHARSW + SCR_X) { 
		_x = SCR_X; 
		_y += 2; 
		#ifndef MAP_WIDTH_16		
			gpit ++;
		#endif
	}
}

const unsigned char alt_tile [] = {
	16, 1, 4, 8, 4, 21, 6, 7, 8, 9, 10, 20, 12, 13, 14, 15
};

void advance_worm (void) {
	_t = rdt;

	// CUSTOM {
		if (rand8() & 1) {
			_t = alt_tile [_t];
		}
	// } END_OF_CUSTOM

	#ifdef MAP_USE_ALT_TILE
		if (_t == 0 && ALT_TILE_EXPRESSION) _t = MAP_USE_ALT_TILE;
	#endif

	rda = behs [_t];
	#ifdef FLOATY_PUSH_BOXES
		scr_buff [gpit] = (rda & PUSHABLE_BEH) ? FLOATY_PUSH_BOXES_SUBST : _t;
	#else	
		scr_buff [gpit] = _t; 
	#endif	

	scr_attr [gpit] = rda;
	draw_tile_advance (); gpit ++;
}

void scr_rand (void) {
	// Set random seed
	seed1 [0] = n_pant; seed2 [0] = n_pant + 69; srand ();
}

void draw_scr (void) {
	#ifdef CPC
		cpc_ResetTouchedTiles ();
	#endif	

	scr_rand ();

	// Find address
	gp_map = map_base_address ();

	#ifdef MAP_FORMAT_RLE44
		gpit = 0; _x = SCR_X; _y = SCR_Y;
		while (gpit < SCR_BUFFER_SIZE) {
			rdt = *gp_map ++;
			rdct = 1 + (rdt >> 4);
			rdt &= 0x0f;
			while (rdct --) advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_RLE53	
		gpit = 0; _x = SCR_X; _y = SCR_Y;
		while (gpit < SCR_BUFFER_SIZE) {
			rdt = *gp_map ++;
			rdct = 1 + (rdt >> 5);
			rdt &= 0x1f;
			while (rdct --) advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_PACKED
		gpit = 0; _x = SCR_X; _y = SCR_Y; rde = 1;
		while (gpit < SCR_BUFFER_SIZE) {
			rdt = (*gp_map) >> 4; advance_worm ();
			rdt = (*gp_map) & 0x0f; advance_worm ();
			gp_map ++;
		}
	#endif

	// CUSTOM {

		// Draw a character
		#ifdef SPECCY
			ob_char_y = 0; gpit = 6; while (gpit --) if (ob_char_n_pants [gpit] == n_pant) {
				rda = ob_char_yx [gpit];
				_t = 32 + (gpit << 1);
				rdx = rda & 0xf; rdy = (rda >> 4) - 1;
				ob_char_x = rdx << 4;
				ob_char_y = (rda & 0xf0) + 24;
				_x = rdx; _y = rdy;     set_map_tile (); 
				_t ++;
				_x = rdx; _y = rdy + 1; set_map_tile (); 
				ob_char_id = gpit;
				break;
			}
		#endif

		#ifdef CPC
			spr_on [SPR_CHARACTER] = 0;
			ob_char_y = 0; gpit = 6; while (gpit --) if (ob_char_n_pants [gpit] == n_pant) {
				rda = ob_char_yx [gpit];
				_t = 32 + (gpit << 1);
				rdx = rda & 0xf; rdy = (rda >> 4) - 1;
				ob_char_x = rdx << 4;
				ob_char_y = (rda & 0xf0) + 24;
				rdy ++; scr_attr [(rdy << 4) | rdx] = 8; 	// Non walkable 
				spr_on [SPR_CHARACTER] = 1;
				spr_x [SPR_CHARACTER] = ob_char_x;
				spr_y [SPR_CHARACTER] = ob_char_y - 8;
				spr_next [SPR_CHARACTER] = sprite_cells [13 + gpit];
				ob_char_id = gpit;
				break;
			}
		#endif

	// } END_OF_CUSTOM
}

void draw_scr_buffer (void) {
	#ifdef CPC
		cpc_ResetTouchedTiles ();
	#endif	

	scr_rand ();

	gpit = 0; _x = SCR_X; _y = SCR_Y;
	gp_map = scr_buff;
	while (gpit < 160) {
		_t = scr_buff [gpit ++];
		draw_tile_advance ();
	}

	#ifdef CPC
		cpc_ShowTileMap (0);
	#endif	
}

void p_t2 (void) {
	DRAW_PATTERN_UPD (_x ++, _y, _t, DIGIT(_n/10));
	DRAW_PATTERN_UPD (_x   , _y, _t, DIGIT(_n%10));
}

#ifdef DEBUG
	unsigned char hexd (unsigned char n) {
		if (n < 10) return DIGIT(n);
		return 'A'-10+n-32;
	}

	void p_hex (unsigned char x, unsigned char y, unsigned char n) {
		DRAW_PATTERN_UPD (x ++, y, 71, hexd(n >> 4));
		DRAW_PATTERN_UPD (x   , y, 71, hexd(n & 0xf));
	}
#endif

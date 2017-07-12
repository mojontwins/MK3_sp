// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Printer

void draw_tile (void) {
	gp_gen = tsmaps + (rdt << 3);
	sp_PrintAtInv (rdy    , rdx    , *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy    , rdx + 1, *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy + 1, rdx    , *gp_gen ++, *gp_gen ++);
	sp_PrintAtInv (rdy + 1, rdx + 1, *gp_gen ++, *gp_gen );
}

void set_map_tile (void) {
	rdf = (rdy << 4) | rdx;
	scr_buff [rdf] = rdt; scr_attr [rdf] = behs [rdt];
	rdx = SCR_X + (rdx << 1); rdy = SCR_Y + (rdy << 1);
	draw_tile ();
}

void draw_tile_advance (void) {
	draw_tile (); rdx += 2; if (rdx == 30 + SCR_X) { rdx = SCR_X; rdy += 2; gpit ++;}
}

void advance_worm (void) {
	rdd = rdt;

#ifdef MAP_USE_ALT_TILE
	if (rdt == 0 && ALT_TILE_EXPRESSION) rdt = MAP_USE_ALT_TILE;
#endif

	rda = behs [rdt];
	scr_buff [gpit] = rdt; scr_attr [gpit] = rda;
	draw_tile_advance (); gpit ++;

	rdt = rdd;
}

void draw_scr (void) {
	// Set random seed
	seed1 [0] = n_pant; seed2 [0] = n_pant + 69; srand ();

	// Find address
	gp_map = map_base_address ();

#ifdef MAP_FORMAT_RLE53	
	// Draw 150 tiles
	gpit = 0; rdx = SCR_X; rdy = SCR_Y;
	while (gpit < 160) {
		rdt = *gp_map ++;
		rdct = 1 + (rdt >> 5);
		rdt &= 0x1f;
		while (rdct --) advance_worm ();
	}
#endif

#ifdef MAP_FORMAT_PACKED
	gpit = 0; rdx = SCR_X; rdy = SCR_Y; rde = 1;
	while (gpit < 160) {
		if (rde) {
			rdct = *gp_map ++; rdt = rdct >> 4;
		} else {
			rdt = rdct & 0x0f;
		}
		rde = 1 - rde;
		advance_worm ();
	}
#endif
}

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	sp_PrintAtInv (y, x ++, 71, DIGIT(n/10));
	sp_PrintAtInv (y, x   , 71, DIGIT(n%10));
}

#ifdef DEBUG
unsigned char hexd (unsigned char n) {
	if (n < 10) return DIGIT(n);
	return 'A'-10+n-32;
}

void p_hex (unsigned char x, unsigned char y, unsigned char n) {
	sp_PrintAtInv (y, x ++, 71, hexd(n >> 4));
	sp_PrintAtInv (y, x   , 71, hexd(n & 0xf));
}
#endif

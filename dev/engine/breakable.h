// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Breakable walls

void breakable_init (void) {
	gpit = BREAKABLE_MAX; while (gpit --) {
		brk_ac [gpit] = 0;
		brk_slots [gpit] = gpit;
	}
	brk_slot = BREAKABLE_MAX;
}

void breakable_break (void) {
	// Expects tile attributes at rdx, rdy,

#if !defined (PLAYER_HITTER)
	// If we come from the hitter, rdi is already on.
	rdi = rdx | (rdy << 4);
#endif

#ifdef BREAKABLE_HITS
	// Increment count at 1cc· ····
	scr_attr [rdi] += BREAKABLE_INCREMENT_COUNTER;	
	// Encode this value carefully when modifying the "define"
	if ((scr_attr [rdi] & 0x60) == BREAKABLE_HITS)
#endif
	{
		// Get slot
		if (brk_slot) {
			brk_slot --; rda = brk_slots [brk_slot];
#ifdef BREAKABLE_TILE_SPECIAL
			brk_sp [rda] = (scr_buff [rdi] == BREAKABLE_TILE_SPECIAL);
#endif
			brk_ac [rda] = BREAKABLE_FRAMES_DESTROY;
			brk_x [rda] = rdx;
			brk_y [rda] = rdy;

			process_breakable = 1;
			
			rdt = BREAKABLE_BREAKING_TILE;
			set_map_tile ();
		}
	}
}

void breakable_do (void) {
	if (0 == process_breakable) return;

	process_breakable = 0;
	gpit = BREAKABLE_MAX; while (gpit --) {
		if (brk_ac [gpit]) {
			process_breakable = 1;
			brk_ac [gpit] --;
			if (brk_ac [gpit] == 0) {
				brk_slots [brk_slot] = gpit; brk_slot ++;	
				rdx = brk_x [gpit]; rdy = brk_y [gpit]; 
				rdt = 0;
				alter_map ();
#ifdef BREAKABLE_TILE_SPECIAL
				if (brk_sp [gpit] && BREAKABLE_TILE_EXPRESION) 
					rdt = BREAKABLE_TILE_GET;
#endif
				set_map_tile ();
			}
		}
	}
}

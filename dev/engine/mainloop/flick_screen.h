// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

	// Change screen
	// Very basic. Extend when needed.

	if (prx == 4 && pvx < 0 && n_pant) {
		n_pant --; px = 228<<FIX_BITS;
	} else if (prx == 228 && pvx > 0) {
		n_pant ++; px = 4<<FIX_BITS;
	} 

	if (pry == 0 && pvy < 0
#ifdef MAP_CHECK_TOP
		&& n_pant >= c_level [LEVEL_MAP_W]
#endif
	) {
		n_pant -= c_level [LEVEL_MAP_W]; py = 160<<FIX_BITS;

#if defined (PLAYER_JUMPS) || defined (PLAYER_MONONO)
#ifdef ENABLE_WATER
		if (pwater) pvy = -PLAYER_VY_FLICK_TOP_SWIMMING; else
#endif
		{ pvy = -PLAYER_VY_FLICK_TOP; pj = 0; }
#endif

	} else if (pry >= 160 && pvy > 0) {
		n_pant += c_level [LEVEL_MAP_W]; py = 0;
	}

	if (on_pant != n_pant && do_game) {
		prx = px >> FIX_BITS; pry = py >> FIX_BITS;
		game_prepare_screen ();
		on_pant = n_pant;
	} 

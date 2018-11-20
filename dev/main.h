// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// main.h - You see flags

void main (void) {
	system_init ();
	sprite_cells_init ();
	
	while (1) {
		game_title (); 			// Set option in gpit!

		level = 0;
#ifdef HOTSPOT_TYPE_STAR		
		pstars = 0;
#endif	
		plife = LIFE_INI;
#ifdef ENABLE_TILE_GET		
		ptile_get_ctr = 0;
#endif		

		while (1) {
			level_setup ();
			game_init ();
			game_loop ();

			if (pkilled) {
				game_over ();
				break;
			} else {
				/*if (level < 3)
					level ++;
				else*/ 
				game_ending ();
				break;
			}
		}
	}
}

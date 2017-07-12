// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// main.h - You see flags

void main (void) {
	system_init ();
	sprite_cells_init ();
	
	while (1) {
		gpit = 1; controls_setup ();

		level = 2;
		plife = LIFE_INI;

		while (1) {
			level_setup ();
			game_init ();
			game_loop ();

			if (pkilled) {
				game_over ();
				break;
			} else {
				if (level < 3)
					level ++;
				else game_ending ();
			}
		}
	}
}

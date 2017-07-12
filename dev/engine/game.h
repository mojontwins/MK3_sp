// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Game functions

void game_shutdown_sprites (void) {
	gpit = SW_SPRITES_ALL; while (gpit --) spr_on [gpit] = 0;
}

void game_init (void) {

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)
	enems_persistent_deaths_init ();
#endif	

#ifdef PERSISTENT_ENEMIES
	persistent_enems_load ();
#endif

#ifndef DISABLE_HOTSPOTS
	hotspots_ini ();
#endif

	player_init ();

	n_pant = c_level [PLAYER_SCR_INI];
	on_pant = 0xff;
	pobjs = 0; opobjs = 0xff;
	max_hotspots_type_1 = 1;	// This works for Ninjajar.

	first_time = 1;
}

void game_prepare_screen (void) {
	// TODO: Pre-render inits

	draw_scr ();

#ifndef DISABLE_HOTSPOTS	
	hotspots_load ();
#endif

	if (first_time) first_time = 0; else {
#ifdef PERSISTENT_ENEMIES
		persistent_update ();
#endif
	}

#ifdef BREAKABLE_WALLS
	breakable_init ();
#endif	

	enems_load ();

#ifdef ENABLE_HITTER
	hitter_frame = 0;
#endif

#ifdef ENABLE_COCOS
	simplecoco_init ();
#endif

	enems_do ();
}

void game_loop (void) {

	do_game = 1; pkilled = 0;

	while (do_game) {
		#include "engine/mainloop/flick_screen.h"

		half_life = 1 - half_life;
		hl_proc = half_life;
		frame_counter ++;

		pad0 = CONTROLLER_READ;

		pgotten = pgtmx = pgtmy = 0;

		enems_do ();
		player_move ();

#ifdef ENABLE_COCOS
		simplecoco_do ();
#endif		
		
#ifndef DISABLE_HOTSPOTS	
		hotspots_do ();
#endif	
		hitter_do ();
		breakable_do ();

		// Update screen
		if (isrc < 2) {
			#asm
				halt
			#endasm
		}
		isrc = 0;
		
		// Update sprites
		gpit = SW_SPRITES_ALL; while (gpit --) if (spr_on [gpit]) {
			rdx = spr_x [gpit]; rdsint = spr_y [gpit] - 16;
			SPRITE_UPDATE_ABS (gpit, rdx, rdsint);
			SPRITE_CELL_PTR_UPDATE (gpit);
		} else SPRITE_OUT (gpit);

		SCREEN_UPDATE;
		
		// Moar
		if (pwashit) player_hit ();

		// Customize the ending condition
		if (pkilled 
			|| (pobjs == max_hotspots_type_1)
		) do_game = 0;
	}
}

void game_over (void) {

}

void game_ending (void) {

}

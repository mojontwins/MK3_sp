// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Game functions

#ifdef SCRIPTING_ON
	void game_run_fire_script (void) {
		run_script (2 * MAX_PANTS + 2);		// Press fire in any room.
		run_script (n_pant + n_pant + 1);		// Press fire in current room.
	}
#endif

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

	#ifdef HOTSPOT_TYPE_KEY
		bolts_load ();
	#endif	

		n_pant = c_level [PLAYER_SCR_INI]; // n_pant=4;prx = 224; px=prx<<4;

		player_init ();

		pkeys = pobjs = 0;
		on_pant = oplife = opobjs = opkeys = 0xff;

	#ifdef HOTSPOT_TYPE_STAR
		opstars = 0xff;
	#endif	

	#ifdef ENABLE_TILE_GET
		optile_get_ctr = 0xff;
	#endif	
		max_hotspots_type_1 = 1;	// This works for Ninjajar.

		first_time = 1;

		// DRAW GAME FRAME
		CLEAR_RECT (RECT_FULL_SCREEN);
		rdc = 71;
		_y  = 0; _x  = 1;    p_s ("LIFE:");
		         _x  = 0xb;  p_s ("KEYS:");
		         _x  = 0x15; p_s ("OBJECTS:");

		// Custom characters
		ob_init ();
}

void game_prepare_screen (void) {
	draw_scr ();

	#ifdef HOTSPOT_TYPE_KEY
		bolts_update_screen ();
	#endif
		
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

	#ifdef FLOATY_PUSH_BOXES
		fpb_init ();
	#endif

		enems_load ();

	#ifdef ENABLE_HITTER
		hitter_frame = 0;
	#endif

	#ifdef ENABLE_COCOS
		simplecoco_init ();
	#endif

	enems_do ();

	#ifdef SCRIPTING_ON
		f_zone_ac = 0;
		fzx1 = fzx2 = fzy1 = fzy2 = 0;
		run_script (2 * MAX_PANTS + 1);		// Entering any script
		run_script (n_pant + n_pant);			// Entering this room script
	#endif	

	#ifdef CPC
		gpit = SW_SPRITES_ALL; while (gpit --) {
			sp_sw [gpit].ox = 0;
			sp_sw [gpit].oy = 0;
		}
		cpc_ResetTouchedTiles ();
		cpc_ShowTileMap (0);
	#endif	
}

void game_loop (void) {
	#ifdef CPC
		cpc_ResetTouchedTiles ();
	#endif	
		hud_update ();
	#ifdef CPC
		cpc_ShowTouchedTiles ();
		cpc_ResetTouchedTiles ();
	#endif

	// Entering Game
	#ifdef SCRIPTING_ON
		#ifdef CLEAR_FLAGS
			msc_clear_flags ();
		#endif
		script_result = 0;
		// Entering game script
		run_script (2 * MAX_PANTS);
	#endif

	do_game = 1; pkilled = 0;
	MUSIC_PLAY (M0_C);

	#ifdef SE_BEEPER
		queued_sound = 0xff;
	#endif

	while (do_game) {
		#include "engine/mainloop/flick_screen.h"

		half_life = 1 - half_life;
		hl_proc = half_life;
		frame_counter ++;
		ticker ++; if (ticker >= 
		#ifdef SPECCY
			25
		#endif
		#ifdef CPC
			16
		#endif
		) ticker = 0;

		#ifdef SPECCY
			pad0 = CONTROLLER_READ;
		#endif		

		pgotten = pgtmx = pgtmy = 0;
		enems_do ();
		player_move ();

		#ifdef ENABLE_COCOS
			simplecoco_do ();
		#endif		
		
		#ifndef DISABLE_HOTSPOTS	
			hotspots_do ();
		#endif

		#ifdef BREAKABLE_WALLS
			breakable_do ();
		#endif

		#ifdef FLOATY_PUSH_BOXES
			fpb_do ();
		#endif		

		#ifdef ENABLE_HITTER
			hitter_do ();
		#endif

		hud_update ();
		
		#ifdef ENABLE_TIMED_MESSAGE
			timed_message_do ();
		#endif		

		// CUSTOM { 
			#include "engine/mainloop/ob.h"
		// } END_OF_CUSTOM

		// Update screen
		#ifdef SPECCY		
			if (isrc < 2) {
				#asm
					halt
				#endasm
			}
			isrc = 0;
		#endif		
		
		#ifdef CPC		
			while (isrc [0] < 18) {
				#asm 
					halt
				#endasm
			}
			isrc [0] = 0;
		#endif
		
		// Update sprites
		#if defined (TALL_PLAYER)
			gpit = SW_SPRITES_ALL; while (gpit --) if (spr_on [gpit]) {
				rdx = spr_x [gpit]; rdsint = spr_y [gpit] - 16;
				if (gpit < SW_SPRITES_16x24) rdsint -= 8;
				SPRITE_UPDATE_ABS (gpit, rdx, rdsint);
				SPRITE_CELL_PTR_UPDATE (gpit);
			} else SPRITE_OUT (gpit);
		#else		
			gpit = SW_SPRITES_ALL; while (gpit --) if (spr_on [gpit]) {
				rdx = spr_x [gpit]; rdsint = spr_y [gpit] - 16;
				SPRITE_UPDATE_ABS (gpit, rdx, rdsint);
				SPRITE_CELL_PTR_UPDATE (gpit);
			} else SPRITE_OUT (gpit);
		#endif
		
		SCREEN_UPDATE;

		#ifdef SE_BEEPER
			if (queued_sound != 0xff) {
				beep_fx (queued_sound);
				queued_sound = 0xff;
			}
		#endif

		#ifdef SCRIPTING_ON
			if (f_zone_ac) {
				if (pry >= fzy1 && pry <= fzy2)
					if (prx >= fzx1 && prx <= fzx2)
						game_run_fire_script ();
			}
		#endif
		
		// Moar
		if (pwashit) player_hit ();

		// Customize the ending condition
		/*
		if (pkilled 
			|| pobjs == c_level [MAX_HOTSPOTS_TYPE_1]
			#ifdef SCRIPTING_ON			
				|| (script_result)
			#endif			
			#ifdef CHEAT_ON
				|| (CONTROLLER_LEFT(pad) && CONTROLLER_RIGHT(pad))
			#endif			
		) do_game = 0;
		*/
		if (pkilled
			|| (pobjs == MAX_HOTSPOTS_0_TYPE_1 && character_order_idx == 5)
		) do_game = 0;

	}
	all_sprites_out ();
	MUSIC_STOP;
}

void game_title (void) {

	#ifdef SPECCY	
		gp_aux = title_rle; unrle (); 

		rdc = 71;
		_x = 15; _y = 9; p_s ("OF THE BOSQUE/EN OTRO BOSQUE");
		_x = 5; _y = 19; p_s ("@ 2018 THE MOJON TWINS");

		_x = 10; _y = 13; p_s ("1.KEYS WASDM/2.KEYS OPQAS/3.KEYS QAOPS/4.KEMPSTON/5.SINCLAIR");

		sp_UpdateNow (); 

		while (1) {
			gpit = KEY_ASCII - '0';
			if (gpit >= 1 && gpit <= 4) break;
		}

		if (gpit > 2) gpit --; // Fix the joke
		controls_setup ();
	#endif	

	#ifdef CPC
		gp_aux = title_rle; unrle (); 

		_x = 15; _y = 9; p_s ("OF THE BOSQUE/EN OTRO BOSQUE");
		_x = 5; _y = 19; p_s ("@ 2018 THE MOJON TWINS");

		_x = 6; _y = 15; p_s ("PRESS ESC TO REDEFINE/PRESS ENTER TO START ");

		cpc_ShowTileMap (0);

		while (cpc_AnyKeyPressed());
		while (1) {
			if (cpc_TestKey (KEY_ESC)) {
				controls_setup (); break;
			} 
			if (cpc_TestKey (KEY_ENTER)) {
				rdf = 0; break;
			}
		}

	#endif
}

void game_over (void) {
	CLEAR_RECT (RECT_FULL_SCREEN);
	rdc = 71; _x = 11; _y = 12; p_s ("GAME OVER!");
	SCREEN_UPDATE_NO_SPRITES;
	//MUSIC_PLAY (M2_C);
	#ifdef SPECCY
		SFX_PLAY_DIRECT (SFX_ITEM);
	#endif
	wait_button ();
	MUSIC_STOP;
}

void game_ending (void) {
	MUSIC_PLAY (M0_C);
	#ifdef SPECCY
		gp_aux = ending_rle; unrle ();

		_x = 4; _y = 14; rdc = 71;
		p_s (" AND THIS IS HOW CHERIL// GOT OUT OF THE BOSQUE.//NOW HER ADVENTURE BEGINS//SEE YOU SOON, CATUNAMBU!");

		sp_UpdateNow ();
		SFX_PLAY_DIRECT (SFX_ITEM);
		SFX_PLAY_DIRECT (SFX_ITEM);
		SFX_PLAY_DIRECT (SFX_ITEM);

		wait_button ();
	#endif	
	#ifdef CPC
		gp_aux = ending_rle; unrle ();

		_x = 4; _y = 14;
		p_s (" AND THIS IS HOW CHERIL// GOT OUT OF THE BOSQUE.//NOW HER ADVENTURE BEGINS//SEE YOU SOON, CATUNAMBU!");

		cpc_ShowTileMap (0);
		SFX_PLAY_DIRECT (SFX_ITEM);

		wait_button ();
	#endif	

	MUSIC_STOP;
	CLEAR_RECT (RECT_FULL_SCREEN);
	SCREEN_UPDATE_NO_SPRITES;
}


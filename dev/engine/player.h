// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Player movement & stuff

#ifdef PLAYER_SAFE
void player_register_safe_spot (void) {
	safe_prx = prx; safe_pry = pry;
	safe_n_pant = n_pant;
}

void player_restore_safe_spot (void) {
	prx = safe_prx; px = prx << FIX_BITS;
	pry = safe_pry; py = pry << FIX_BITS;
	n_pant = safe_n_pant;	
}
#endif

#ifdef ENABLE_HOLES
void player_holed (void) {
	pholed = 48; 
	pvx = ADD_SIGN(pvx, PLAYER_V_INERTIA);
	pvy = ADD_SIGN(pvy, PLAYER_V_INERTIA);
	pad = 0xff;
}
#endif

void player_reset_movement (void) {
	pvx = pvy = 0;
	pfixct = pfiring = 0;
	phit = 0;
	pvylast = 0;
#ifdef PLAYER_JUMPS	
	pj = pjustjumped = 0;
#endif
#ifdef PLAYER_JETPAC	
	pthrust = 0;
#endif
#ifdef PLAYER_SPINS	
	pspin = 0;
#endif	
#ifdef PLAYER_BUTT
	pbutt = 0;
#endif
#ifdef ENABLE_HOLES
	pholed = 0;
#endif
#ifdef ENABLE_FUMETTOS
	thrustct = 0;
#endif
#ifdef ENABLE_WATER
	pwater = 0;
#endif
#ifdef PLAYER_FLOATS
	pfloat = 0;
#endif
}

#ifdef PLAYER_PROCESS_BLOCK
#ifdef PLAYER_GRAVITY
void player_process_block (signed char x, signed char y) {
	if (y) y --;
	rdc = x + (y << 4);
	rda = scr_buff [rdc];
	switch (rda) {
#ifdef PLAYER_PUSH_BOXES		
		case 14:
#ifdef PLAYER_FIRE_TO_PUSH
			if (BUTTON_A (pad)) 
#endif		
			{
				// push block
				pbx1 = x;
				if (CONTROLLER_LEFT (pad)) {
					if (x > 0) if (0 == scr_attr [x - 1 + (y << 4)]) pbx1 = x - 1;
				} else if (CONTROLLER_RIGHT (pad)) {
					if (x < 15) if (0 == scr_attr [x + 1 + (y << 4)]) pbx1 = x + 1;
				}
				if (pbx1 != x) {
					set_map_tile (x, y, 0); set_map_tile (pbx1, y, 14);
					//sfx_play (SFX_BUTT_HIT, SC_LEVEL);
				}

#ifdef PLAYER_FIRE_TO_PUSH				
				pfiring = 1;
#endif								
			}
			break;
#endif

#ifdef HOTSPOT_TYPE_KEY			
		case 15:
			// Key hole
			if (pkeys) {
				pkeys --;
				bolts_clear_bolt ();
				set_map_tile (x, y, 0);
				//sfx_play (SFX_CHOF, SC_LEVEL);
			}
			break;
#endif				
	}
}
#else
void player_process_block (signed char x, signed char y, unsigned char direction) {
	if (y) y --;
	rdc = x + (y << 4);
	rda = scr_buff [rdc];
	switch (rda) {
#ifdef PLAYER_PUSH_BOXES		
		case 14:
#ifdef PLAYER_FIRE_TO_PUSH
			if (BUTTON_A (pad)) 
#endif		
			{
				// push block
				pbx1 = x; pby1 = y;
				if (direction) {
					if (CONTROLLER_LEFT (pad)) {
						if (x > 0) if (0 == scr_attr [x - 1 + (y << 4)]) pbx1 = x - 1;
					} else if (CONTROLLER_RIGHT (pad)) {
						if (x < 15) if (0 == scr_attr [x + 1 + (y << 4)]) pbx1 = x + 1;
					}
				} else {
					if (CONTROLLER_UP (pad)) {
						if (y > 0) if (0 == scr_attr [x + ((y - 1) << 4)]) pby1 = y - 1;
					} else if (CONTROLLER_DOWN (pad)) {
						if (y < 11) if (0 == scr_attr [x + ((y + 1) << 4)]) pby1 = y + 1;
					}
				}
				if (pbx1 != x || pby1 != y) {
					set_map_tile (x, y, 0); set_map_tile (pbx1, pby1, 14);
					//sfx_play (SFX_BUTT_HIT, SC_LEVEL);
				}

#ifdef PLAYER_FIRE_TO_PUSH				
				pfiring = 1;
#endif								
			}
			break;
#endif
#ifdef HOTSPOT_TYPE_KEY			
		case 15:
			// Key hole
			if (pkeys) {
				pkeys --;
				bolts_clear_bolt ();
				set_map_tile (x, y, 0);
				//sfx_play (SFX_CHOF, SC_LEVEL);
			}
			break;
#endif				
	}
}
#endif
#endif

void player_init (void) {
	// Init player data
	prx = (signed int) (c_level [PLAYER_INI_X] << 4); px = prx << FIX_BITS;
	pry = (signed int) (c_level [PLAYER_INI_Y] << 4); py = pry << FIX_BITS;

#ifdef PLAYER_SAFE
	player_register_safe_spot ();
#endif
	
#ifdef ENABLE_HITTER
	hitter_frame = 0;
#endif

#ifdef PLAYER_GENITAL
	pfacing = pfacingv = CELL_FACING_DOWN;		
	pfacinglast = pfacingh = CELL_FACING_RIGHT;
#else
	pfacing = CELL_FACING_RIGHT;
#endif

	player_reset_movement ();
	pkilled = 0;

	psprid = 0;
}

void player_hit (void) {
	//sfx_play (SFX_ENEMY_HIT, SC_PLAYER);

	SCREEN_UPDATE;

#ifdef PLAYER_DIE_AND_RESPAWN
	//player_render ();
	pad0 = 0xff;
	//music_pause (1);
	//delay (60);
	//music_pause (0);
	player_reset_movement ();
	player_restore_safe_spot ();
#endif

#ifdef ENABLE_HOLES
	if (pholed) {
		player_reset_movement ();
		player_restore_safe_spot ();
		pholed = 0;
	}
#endif

#ifdef PLAYER_FLICKERS
	pflickering = PLAYER_FLICKERS;
#endif
	
	if (plife) {
		plife --;
	} else {
		pkilled = 1;
	}
	
	phit = PLAYER_HIT_FRAMES;

	pwashit = 0;

#ifdef ENABLE_HITTER
	hitter_frame = 0;
#endif
}

void player_move (void) {
	// Player state
	if (phit) phit --;
	if (pflickering) pflickering --;

	// Refine this with use_ct, guay_ct, etc.
	pad = 0xff;

#ifdef FIRE_SCRIPT_WITH_ANIMATION
	if (use_ct) {
		psprid = CELL_USE_BASE + use_ct;
		if (fr_ct) fr_ct --; else {
			use_ct ++;
			if (use_ct == 7) {
				if (containers_get) {
					//sfx_play (SFX_GET_ITEM, SC_LEVEL);
					if (flags [PLAYER_INV_FLAG] != flags [containers_get]) {
						rda = flags [PLAYER_INV_FLAG];
						flags [PLAYER_INV_FLAG] = flags [containers_get];
						flags [containers_get] = rda;
						commands_executed = 1;
					}
#ifdef CONTAINER_ACTION_STOPS_CHECKS
				} else {
#else
				}
				if (0 == commands_executed) {
#endif
					game_run_fire_script ();
				}
			}
			if (use_ct == 13 && !commands_executed) {
				use_ct = 0;
				pfacing = CELL_FACING_RIGHT;
				no_ct = ticks;
			}
			if (use_ct == 18) use_ct = 0;
			fr_ct = 6;
		}
	} else if (guay_ct) {
		guay_ct --;
		if (guay_ct == 0) pflickering = ticks;
	} else
#endif 
		pad = pad0;

#ifdef ENABLE_HOLES
	if (pholed) pad = 0xff;
#endif	

#ifdef ENABLE_EVIL_TILE
	evil_tile_hit = 0;
#endif

#if defined (EVIL_TILE_MULTI) || defined (EVIL_TILE_CENTER)
	pcx = px; pcy = py;
#endif

	// ********
	// Vertical
	// ********

#ifdef PLAYER_GRAVITY
#ifdef ENABLE_WATER
	if (pwater) {
		pvy += PLAYER_G_WATER;
		if (pvy > PLAYER_VY_MAX_SINK_WATER) pvy = PLAYER_VY_MAX_SINK_WATER;
	} else
#endif
	// Gravity
	if (!pgotten
#ifdef PLAYER_JETPAC
		&& !pthrust
#endif
	) {
		if (!pj) {
#ifdef PLAYER_FLOATS
			if (pfloat) {
				if (half_life) { if (pvy < 16) pvy ++; else pvy = 16; }
			} else
#endif			
			pvy += PLAYER_G; 
		} else pvy += PLAYER_G_JUMPING;
		if (pvy > PLAYER_VY_FALLING_MAX) pvy = PLAYER_VY_FALLING_MAX;
	}
#endif

#ifdef PLAYER_GENITAL
	// Poll pad
	if (CONTROLLER_UP (pad)) {
		if (!pfixct) if (pvy > -PLAYER_VY_MAX) {
			pvy -= PLAYER_AY;			
		}
		pfacingv = CELL_FACING_UP;
	} else if (CONTROLLER_DOWN (pad)) {
		if (!pfixct) if (pvy < PLAYER_VY_MAX) {
			pvy += PLAYER_AY;
		}
		pfacingv = CELL_FACING_DOWN;		
	} else {
#ifdef ENABLE_HOLES
		if (!pholed)
#endif
			if (pvy > 0) {
				pvy -= PLAYER_RY; if (pvy < 0) pvy = 0; 
			} else if (pvy < 0) {
				pvy += PLAYER_RY; if (pvy > 0) pvy = 0;
			}

		pfacingv = 0xff;
	}
#endif

	// Move
	py += pvy;

	// Collision
	//prx = px >> FIX_BITS;
	if (py < 0) { py = pry = 0; }
	else if (py > (192<<FIX_BITS)) pry = 192;
	else pry = py >> FIX_BITS;

	cx1 = prx >> 4;
	cx2 = (prx + 7) >> 4;
	if (pvy + pgtmy) {
		if (pvy + pgtmy < 0) {
#ifdef PLAYER_8_PIXELS
			cy1 = cy2 = (pry + 6) >> 4;
#else
			cy1 = cy2 = pry >> 4;
#endif
			cm_two_points ();
#ifdef PLAYER_GENITAL
			if ((at1 & FLOOR_BITS) || (at2 & FLOOR_BITS))
#else
			if ((at1 & OBSTACLE_BIT) || (at2 & OBSTACLE_BIT))
#endif
			{
				pgotten = pvy = 0;
#ifdef PLAYER_8_PIXELS
				pry = ((cy1 + 1) << 4) - 6;
#else
				pry = (cy1 + 1) << 4;
#endif
				py = pry << FIX_BITS;
			} else {

#ifdef EVIL_TILE_MULTI
				if ((at1 & EVIL_BIT) || (at2 & EVIL_BIT)) {
					pvy = PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif	

#ifdef ENABLE_HOLES
				if (!pholed) {
					cy1 = cy2 = (pry + 14) >> 4;
					cm_two_points ();
					if ((at1 & HOLE_BIT) && (at2 & HOLE_BIT)) player_holed ();
				} 
#endif

#ifdef ENABLE_QUICKSANDS
				if ((at1 & QUICKSANDS_BIT) || (at2 & QUICKSANDS_BIT)) {
					//if (pctj > 2) pj = pvy = 0;
					if (pvy < -PLAYER_VY_EXIT_QUICKSANDS) pvy = -PLAYER_VY_EXIT_QUICKSANDS;
				}
#endif
			}
		} else if (pvy + pgtmy > 0)	{
			cy1 = cy2 = (pry + 15) >> 4; 
			cm_two_points (); 
	 		if (((pry - 1) & 15) < 4 && ((at1 & (OBSTACLE_BIT | PLATFORM_BIT)) || (at2 & (OBSTACLE_BIT | PLATFORM_BIT)))) {
				pgotten = pvy = 0;
				pry = (cy1 - 1) << 4;
				py = pry << FIX_BITS;
			} else {
#ifdef ENABLE_HOLES
				if (!pholed && ((at1 & HOLE_BIT) && (at2 & HOLE_BIT))) player_holed ();
#endif			

#ifdef EVIL_TILE_MULTI
				if ((at1 & EVIL_BIT) || (at2 & EVIL_BIT)) {
					pvy = -PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif		

#ifdef ENABLE_QUICKSANDS
				if ((at1 & QUICKSANDS_BIT) || (at2 & QUICKSANDS_BIT)) pvy = PLAYER_VY_SINKING;
#endif	
			}
		}
#ifdef PLAYER_PROCESS_BLOCK
#ifdef PLAYER_GENITAL		
		if (at1 == SPECIAL_BEH) player_process_block (cx1, cy1, 0);
		if (at2 == SPECIAL_BEH) player_process_block (cx2, cy2, 0);
#endif		
#endif
	}

#ifdef PLAYER_GRAVITY
	// Floor detections: possee

	cy1 = cy2 = (pry + 16) >> 4;
	cm_two_points ();
	ppossee = ((at1 & FLOOR_BITS) || (at2 & FLOOR_BITS)) && pvy >= 0 && ((pry & 0xf) == 0);
#ifdef PLAYER_JUMPS	
	if (ppossee || pgotten) {
		pjustjumped = 0;
#ifdef PLAYER_DOUBLE_JUMP
		njumps = 0;
#endif		
	}
#endif	
#endif	

	// Floor detections: Conveyors
	
#ifdef ENABLE_CONVEYORS
	if (ppossee) {
		if (at1 & CONVEYOR_BIT) { if (at1 & EVIL_BIT) pgtmx = CONVEYOR_SPEED; else pgtmx = -CONVEYOR_SPEED; pgotten = 1; }
		if (at2 & CONVEYOR_BIT) { if (at2 & EVIL_BIT) pgtmx = CONVEYOR_SPEED; else pgtmx = -CONVEYOR_SPEED; pgotten = 1; }
	}
#endif	

	// Floor detections: Propellers
#ifdef ENABLE_PROPELLERS
	if ((at1 & PROPELLERS_BIT) || (at2 & PROPELLERS_BIT)) {
		pvy -= PLAYER_G + PLAYER_AY_PROPELLER;
		if (pvy < -PLAYER_VY_PROPELLER_MAX) pvy = -PLAYER_VY_PROPELLER_MAX;
	}
#endif

	// Floor detections: Evil tile

#ifdef ENABLE_EVIL_TILE
#ifdef EVIL_TILE_ON_FLOOR
	cy1 = cy2 = (pry + 12) >> 4;	// Let it bleed a bit
	cm_two_points ();
	if (at1 == 1 || at2 == 1) evil_tile_hit = 1;
#endif	
#endif

	// Floor detections: Slippery
#ifdef ENABLE_SLIPPERY
	pslips = ppossee && ((at1 & SLIPPERY_BIT) || (at2 & SLIPPERY_BIT));
#endif

	// Jump!

#ifdef PLAYER_JUMPS
	if (BUTTON_B || CONTROLLER_UP(pad)) {
		if (!pjb) {
			pjb = 1;
#ifdef ENABLE_WATER
			if (pwater) {
				if (ppossee) player_register_safe_spot ();
				pvy -= PLAYER_AY_SWIM;
				if (pvy < -PLAYER_VY_SWIM_MAX) pvy = -PLAYER_VY_SWIM_MAX;
				pwaterthrustct ++;
				if (rand8 () & 0xf) hearts_create ();
			} else
#endif			
			if (!pj) {
				if (
					(pgotten || ppossee || phit)
#ifdef PLAYER_DOUBLE_JUMP
					|| (njumps < 2)
#endif
				) {
#ifdef PLAYER_DOUBLE_JUMP					
					if (njumps) {
						fumettos_add ();
						pctj = 2;
					} else
#endif					
					pctj = 0; 
#ifdef PLAYER_DOUBLE_JUMP
					njumps ++;
#endif					
					pj = 1; pjustjumped = 1;
					pvy = -PLAYER_VY_JUMP_INITIAL;
					//sfx_play (SFX_JUMP, SC_PLAYER);

#ifdef PLAYER_DIE_AND_RESPAWN
					if (ppossee) {
						player_register_safe_spot ();
					}
#endif					
				}
			} 
		}
		if (pj) {
			pctj ++; if (pctj == PLAYER_VY_JUMP_A_STEPS) pj = 0;
		}
	} else {
		pjb = 0;
		if (pj) {
			if (pvy < -PLAYER_VY_JUMP_RELEASE) pvy = -PLAYER_VY_JUMP_RELEASE;
			pj = 0;
		}
	}
#endif

	// Monono!

#ifdef PLAYER_MONONO
	if (!(BUTTON_B || CONTROLLER_UP(pad))) { pj = 0; pvylast = -PLAYER_VY_JUMP_INITIAL; } else {
		if (ppossee || pgotten) {
			pvy = SATURATE_N (pvylast - PLAYER_AY_JUMP, -PLAYER_VY_JUMP_MAX);
			pvylast = pvy;
			pj = 1;
			//sfx_play (SFX_JUMP, SC_PLAYER);
		}
	}
#endif	

#ifdef PLAYER_JETPAC
	if (BUTTON_B || CONTROLLER_UP(pad)) {
		pvy = SATURATE_N (pvy - PLATER_AY_JETPAC, -PLAYER_VY_JETPAC_MAX);		
		pthrust = 1;
		if (!(thrustct)) fumettos_add ();
				thrustct ++; if (thrustct == 7) thrustct = 0; // so it stays out of phase
	} else thrustct = pthrust = 0;
#endif

#ifdef PLAYER_SPINS
	//if (!pvy < 0) pspin = 0;
	if (CONTROLLER_DOWN (pad)) {
		if (ppossee && ABS (pvx) > PLAYER_VX_MIN) {
			pspin = 1; //sfx_play (SFX_BUTT_FALL, SC_PLAYER);
		}
	}
#endif

	// **********
	// Horizontal
	// **********
	
	// Poll pad

	if (CONTROLLER_LEFT (pad)) {
		if (!pfixct) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx --;
			} else
#endif
			pvx -= PLAYER_AX;
#ifdef ENABLE_WATER
			if (pwater) { if (pvx < -PLAYER_VX_MAX_SWIMMING) pvx = -PLAYER_VX_MAX_SWIMMING; } else
#endif
			if (pvx < -PLAYER_VX_MAX) pvx = -PLAYER_VX_MAX;
		}
#ifdef PLAYER_GENITAL
		pfacinglast = pfacingh = CELL_FACING_LEFT;
#else
		pfacing = CELL_FACING_LEFT;

#endif
	} else if (CONTROLLER_RIGHT (pad)) {
		if (!pfixct) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx ++;
			} else
#endif
			pvx += PLAYER_AX;
#ifdef ENABLE_WATER
			if (pwater) { if (pvx > PLAYER_VX_MAX_SWIMMING) pvx = PLAYER_VX_MAX_SWIMMING; } else
#endif
			if (pvx > PLAYER_VX_MAX) pvx = PLAYER_VX_MAX;

		}
#ifdef PLAYER_GENITAL		
		pfacinglast = pfacingh = CELL_FACING_RIGHT;		
#else
		pfacing = CELL_FACING_RIGHT;
#endif		
	} else {
#ifdef PLAYER_SPINS
		if (!pspin)
#endif

#ifdef ENABLE_HOLES
		if (!pholed)
#endif			
			if (pvx > 0) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx --;
			} else
#endif
				pvx -= PLAYER_RX; 
				if (pvx < 0) pvx = 0;
			} else if (pvx < 0) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx ++;
			} else
#endif
				pvx += PLAYER_RX; 
				if (pvx > 0) pvx = 0;
			}
#ifdef PLAYER_GENITAL
		pfacingh = 0xff;
#endif		
	}

	// Move
	px += pvx;		
	if (pgotten) px += pgtmx;
	
	// Collision
	if (px < (4<<FIX_BITS)) px = 4<<FIX_BITS;
	else if (px > (228<<FIX_BITS)) px = 228<<FIX_BITS;
	
	prx = px >> FIX_BITS;
	
#ifdef PLAYER_8_PIXELS
	cy1 = (pry + 6) >> 4;
#else
	cy1 = pry >> 4;
#endif
	cy2 = (pry + 15) >> 4;
	if (pvx + pgtmx) {
		if (pvx + pgtmx < 0) {
			cx1 = cx2 = prx >> 4;
			cm_two_points ();
#ifdef PLAYER_GENITAL
			if ((at1 & FLOOR_BITS) || (at2 & FLOOR_BITS)) {
#else
			if ((at1 & OBSTACLE_BIT) || (at2 & OBSTACLE_BIT)) {
#endif
				pvx = 0;
				prx = (cx1 + 1) << 4;
				px = prx << FIX_BITS;
			} else {

#ifdef ENABLE_HOLES
				if (!pholed && ((at1 & HOLE_BIT) && (at2 & HOLE_BIT))) player_holed ();
#endif

#ifdef EVIL_TILE_MULTI
#ifdef PLAYER_SMALLER_ETCB
				cy1 = (pry + PLAYER_ETCB_UP) >> 4;
				cy2 = (pry + PLAYER_ETCB_DOWN) >> 4;
				cx1 = cx2 = (prx + PLAYER_ETCB_LEFT) >> 4;
				cm_two_points (); 
#endif
				if ((at1 & EVIL_BIT) || (at2 & EVIL_BIT)) {
					pvx = PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif
			}
		} else if (pvx + pgtmx > 0)	{
			cx1 = cx2 = (prx + 7) >> 4; 
			cm_two_points (); 
#ifdef PLAYER_GENITAL
			if ((at1 & FLOOR_BITS) || (at2 & FLOOR_BITS)) {
#else
	 		if ((at1 & OBSTACLE_BIT) || (at2 & OBSTACLE_BIT)) {
#endif
				pvx = 0;
				prx = ((cx1 - 1) << 4) + 8;
				px = prx << FIX_BITS;
			} else {

#ifdef ENABLE_HOLES
				if (!pholed && ((at1 & HOLE_BIT) && (at2 & HOLE_BIT))) player_holed ();
#endif			

#ifdef EVIL_TILE_MULTI
#ifdef PLAYER_SMALLER_ETCB
				cy1 = (pry + PLAYER_ETCB_UP) >> 4;
				cy2 = (pry + PLAYER_ETCB_DOWN) >> 4;
				cx1 = cx2 = (prx + PLAYER_ETCB_RIGHT) >> 4;
				cm_two_points (); 
#endif
				if ((at1 & EVIL_BIT) || (at2 & EVIL_BIT)) {
					pvx = -PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif
			}
		}
#ifdef PLAYER_PROCESS_BLOCK
#ifdef PLAYER_GRAVITY
		if (at1 == SPECIAL_BEH) player_process_block (cx1, cy1);
		if (at2 == SPECIAL_BEH) player_process_block (cx2, cy2);
#else
		if (at1 == SPECIAL_BEH) player_process_block (cx1, cy1, 1);
		if (at2 == SPECIAL_BEH) player_process_block (cx2, cy2, 1);
#endif
#endif
	}

	// Once the player has moved, center point detections

#ifdef PLAYER_ENABLE_CENTER_DETECTIONS
	cx1 = cx2 = (prx + 4) >> 4;
	cy1 = cy2 = (pry + 8) >> 4;
	cm_two_points ();

#ifdef EVIL_TILE_CENTER
	evil_tile_hit = (at1 & EVIL_BIT);
#endif

#ifdef ENABLE_WATER
	rda = pwater;
	pwater = (at1 & WATER_BIT);
	if (pwater != rda) //sfx_play (SFX_FLUSH, SC_PLAYER);
	if (!pwater && rda) pvy = -PLAYER_VY_OUT_OF_WATER;
#endif

#ifdef ENABLE_TILE_GET
	if (at1 & TILE_GET_BIT) {

		rdx = cx1; rdy = cy1 - 1, rdt = 0;
		set_map_tile ();
		//sfx_play (SFX_RING, SC_LEVEL);

#ifdef TILE_GET_COUNT_ON_FLAG
		flags [TILE_GET_COUNT_ON_FLAG] ++;
#else 
		tile_get_ctr ++;
		if (tile_get_ctr == 100) {
			tile_get_ctr = 1; 
			plife ++;
			//sfx_play (SFX_START, SC_PLAYER);
		}
#endif	

#ifdef PERSISTENT_TILE_GET
		gpint = tile_got_offset + (cy1 - 1);
		rda = tile_got [gpint];
		tile_got [gpint] = rda | bitmask [cx1 >> 1];
#endif
	}
#endif

#endif

	// Evil tile (continued)

#ifdef ENABLE_EVIL_TILE

	if (evil_tile_hit) {
#ifdef PLAYER_SPINS
		pspin = 0;
#endif
#ifdef PLAYER_JUMPS
		pjustjumped = 0;
#endif

#ifdef EVIL_TILE_ON_FLOOR
		pvy = -PLAYER_V_REBOUND; 
#endif
#ifdef EVIL_TILE_MULTI
		px = pcx; py = pcy;
#endif
#if defined (EVIL_TILE_CENTER) && !defined (PLAYER_DIE_AND_RESPAWN)
		px = pcx; py = pcy;
		pvy = -PLAYER_V_REBOUND_MULTI;
#endif

		if (
#ifdef PLAYER_FLICKERS
		!pflickering
#else				
		!phit
#endif
		)
		pwashit = 1;
#ifdef PLAYER_DIE_AND_RESPAWN 
		else {
			px = pcx; py = pcy;
			pvy = -PLAYER_V_REBOUND_MULTI;
		}
#endif
	}
#endif	

	// Hidden
#ifdef ENABLE_ESPECTROS
	cx1 = cx2 = (prx + 4) >> 4;
	cy1 = cy2 = (pry + 8) >> 4;
	cm_two_points ();
	phidden = (ABS (pvy) < PLAYER_VY_MIN) && (ABS (pvx) < PLAYER_VX_MIN) && (at1 & PLAYER_HIDES_BIT);
#endif

	// Spinning

#ifdef PLAYER_SPINS
	if (!pvx && ppossee) pspin = 0;
#endif

	// Can't remember

#ifdef PLAYER_TURRET
	if (pfixct) pfixct --;
#endif

	// Float

#ifdef PLAYER_FLOATS	
	if (!ppossee && !pj && (pad0 & PAD_DOWN)) {
		if (!pfloat) pvy = 0;
		pfloat = 1;
	} else pfloat = 0;
#endif

	// PAD B Stuff!
	// In order:
	// 1. containers
	// 2. scripting
	// 3. fire

	// If you are using "FIRE_SCRIPT_WITH_ANIMATION", well...
	// that's incompatible with PLAYER_CAN_FIRE. Unless you work it out.

	// For genital games you *should* change PAD_B to PAD_A

	if (BUTTON_A(pad)) {
#ifdef ENABLE_CONTAINERS
		commands_executed = containers_get = 0;
		if (!pfiring) {
			containers_do ();
#ifdef CONTAINERS_HAS_GOT_FLAG			
			flags [CONTAINERS_HAS_GOT_FLAG] = containers_get;
#endif
			if (containers_get) {
#ifdef FIRE_SCRIPT_WITH_ANIMATION
				player_reset_movement ();
				use_ct = 1;
#else
				rda = flags [PLAYER_INV_FLAG];
				flags [PLAYER_INV_FLAG] = flags [containers_get];
				flags [containers_get] = rda;
#endif
#ifdef CONTAINER_ACTION_STOPS_CHECKS
				pfiring = 1;
#endif
			}
		}
#endif

#ifdef SCRIPTING_ON
		if (!pfiring) {
#ifdef FIRE_SCRIPT_WITH_ANIMATION
			if (ppossee){
				player_reset_movement ();
				use_ct = 1;
			} 
#else
			game_run_fire_script ();
			if (commands_executed) pfiring = 1;
#endif
		}
#endif

#ifdef PLAYER_PUAS
		if (!pfiring) {
			//sfx_play (SFX_SHOOT, SC_PLAYER);
			puas_create ();
		}
#endif

#ifdef PLAYER_CAN_FIRE
		if (!pfiring) {
			bullets_fire ();
#ifdef PLAYER_TURRET		
			pfixct = TURRET_FRAMES;
#endif	
		}
#endif

#ifdef ENABLE_FABOLEES
		if (!pfiring) fabolee_new ();
#endif

#ifdef PLAYER_PUNCHES
		if (0 == hitter_frame && !pfiring) {
			hitter_frame = 1;
		}
#endif

		pfiring = 1;
	} else pfiring = 0;

/*
#ifdef PLAYER_CAN_FIRE
	if (BUTTON_A (pad)) {
		if (!pfiring) bullets_fire ();
		pfiring = 1;
#ifdef PLAYER_TURRET		
		pfixct = TURRET_FRAMES;
#endif		
	} else pfiring = 0;
#endif	
*/

	// Butt

#ifdef PLAYER_BUTT
	if (ppossee || phit 
#ifdef ENABLE_WATER
		|| pwater
#endif
	) pbutt = 0; else {
		if (BUTTON_B) {
			if (!pbutt) {
				pbutt = 1; pj = 0;
				//sfx_play (SFX_BUTT_FALL, SC_PLAYER);			
			}
		}
	}
#endif	

	// Hitter todo
	/*
	if ((BUTTON_B) && !hitter_on && pstatespradder) {
		hitter_on = 1; hitter_frame = 0;
		//sfx_play (SFX_SHOOT, SC_PLAYER);
	}
	*/
	
	// Solve facing
#ifdef PLAYER_GENITAL	
	if (pfacingv != 0xff) pfacing = pfacingv; else if (pfacingh != 0xff) pfacing = pfacingh;
#endif

	// Sprite cell selection is usually pretty custom...

	if (ppossee || pgotten) {
		if (ABS (pvx) > PLAYER_VX_MIN) {
			psprid = walk_frames [(prx >> 3) & 3];
		} else psprid = CELL_IDLE;
	} else psprid = CELL_AIRBORNE;

	psprid += pfacing;

	spr_on [SPR_PLAYER] = (pflickering == 0) || half_life;
	spr_x [SPR_PLAYER] = prx - 4;
	spr_y [SPR_PLAYER] = pry;
	spr_next [SPR_PLAYER] = sprite_cells [psprid];
}

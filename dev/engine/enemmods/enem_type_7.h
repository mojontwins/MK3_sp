// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

#ifdef TYPE7_WITH_GENERATOR
	if (en_gen_washit [gpit]) en_gen_washit [gpit] --;
#endif	

	if (_en_state) {
		// Minion on
		if (!en_washit [gpit]) if (!phit && (en_hl [gpit] || half_life) && !en_fishing [gpit] && !pflickering ) {
			// Pursue relentlessly
			_en_mx = ADD_SIGN2 ((prx >> 2) << 2, _en_x, en_v [gpit]);
			_en_my = ADD_SIGN2 ((pry >> 2) << 2, _en_y, en_v [gpit]);

			// Move, check colision. Use what fits your needs!
			// CUSTOM {
			// if en_s [gpit] == 0, the minion is a fish, which only collides with 8.
			//if (en_s [gpit]) rda = 12; else rda = 8;
			//rda = 0xf; // 1 | 2 | 4 | 8.
			rda = EVIL_BIT | PLATFORM_BIT | OBSTACLE_BIT;

			if (_en_mx) {
				_en_x += _en_mx;
				
				cy1 = (_en_y + 8) >> 4; cy2 = (_en_y + 15) >> 4;
				if (_en_mx < 0) {
					cx1 = cx2 = (_en_x + 4) >> 4;
					rdb = ((cx1 + 1) << 4) - 4;
				} else if (_en_mx > 0) {
					cx1 = cx2 = (_en_x + 11) >> 4;
					rdb = ((cx1 - 1) << 4) + 4;
				}
				cm_two_points ();
				if ((at1 & rda) || (at2 & rda)) _en_x = rdb;
			}

			if (_en_my) {
				_en_y += _en_my;

				cx1 = (_en_x + 4) >> 4; cx2 = (_en_x + 11) >> 4;
				if (_en_my < 0) {
					cy1 = cy2 = (_en_y + 8) >> 4;
					rdb = ((cy1 + 1) << 4) - 8;
				} else if (_en_my > 0) {
					cy1 = cy2 = (_en_y + 15) >> 4;
					rdb = ((cy1 - 1) << 4);
				}
				cm_two_points ();
				if ((at1 & rda) || (at2 & rda)) _en_y = rdb;
				
			}

			if ((rand8 () & TYPE7_STOP_RATE) == 2) en_fishing [gpit] = TYPE7_STOP_FRAMES + rand8 () & TYPE7_STOP_FRAMES;
		}

		if (en_fishing [gpit]) en_fishing [gpit] --;
		spr_id = en_s [gpit] + ((_en_mx > 0) ? 0 : 2) + ((frame_counter >> 4) & 1);
	} else {
		// This makes life easier later on and somewhere else
		_en_x = _en_x1; 
		_en_y = _en_y1;
		// Idling
		if (_en_ct) _en_ct --; else {
			//if (generators_active) { // this is custom
				// Spawn. 

				/*
				// Velocities may be .5 1 2 1
				rda = rand8 () & 3;
				if (!rda) { rda = 1; en_hl [gpit] = 0; } else {
					if (rda == 3) rda = 1;
					en_hl [gpit] = 1;
				}
				en_v [gpit] = rda;
				*/
				// Velocities 0.5 1
				en_hl [gpit] = rand8 () & 1;
				en_v [gpit] = 1;

				// Type
#ifdef TYPE7_FIXED_SPRITE
				en_s [gpit] = TYPE7_FIXED_SPRITE << 2;
#else				
				if (_en_t & 0x0f) {
					en_s [gpit] = 0;
				} else {
					rda = rand8 () & 7; if (rda > 4) rda -= 3;
					en_s [gpit] = 4 + (rda << 2);
				}
#endif				

				_en_state = 1;
				en_life [gpit] = TYPE7_MINION_LIFE;
			//}
		}

		spr_id = 0xff;
		if (_en_ct < TYPE7_SMOKE_TIME) {
			_en_x = _en_x1; 
			_en_y = _en_y1;
			if (_en_ct < (TYPE7_SMOKE_TIME>>1)) 
				spr_id = 16;
			else if (half_life)
				spr_id = 17;
		} 
	}

	// enems_spr ();
	

// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Hotspots

void hotspots_ini (void) {
	#ifdef HOTSPOTS_MAY_CHANGE
		gp_gen = (unsigned char *) (hotspots);
		for (gpit = 0; gpit < MAX_PANTS; ++gpit) {
			ht [gpit] = *gp_gen ++; gp_gen ++;
			hact [gpit] = 1;
		}
	#else
		gpit = MAX_PANTS; while (gpit --) hact [gpit] = 1;
	#endif
}

void hotspots_paint (void) {
	if (hrt) {
		_y = SCR_Y + (hry >> 3) - 2;
		_x = SCR_X + (hrx >> 3);
		#ifdef HOTSPOT_SIMPLE_SIGNS
			_t = HOTSPOTS_BASE_TILE + (hrt & 0xf);
		#else			
			_t = HOTSPOTS_BASE_TILE + hrt;
		#endif			
		DRAW_TILE_UPD ();
	}
}

void hotspots_load (void) {
	if (hact [n_pant]) {
		#ifdef HOTSPOTS_MAY_CHANGE
			rda = hotspots [1 + (n_pant << 1)];
			hrt = ht [n_pant];
		#else
			gp_gen = (unsigned char *) (hotspots + (n_pant << 1));
			hrt = *gp_gen ++; rda = *gp_gen;
		#endif
		hry = rda & 0xf0; hrx = rda << 4;

		hotspots_paint ();
	} else hrt = 0;
}

void hotspots_do (void) {

	if (hrt) {
		if (collide (prx, pry, hrx, hry)) {
			#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
				rda = 1;
			#endif

			#ifdef HOTSPOT_SIMPLE_SIGNS
				switch (hrt & 0xf)
					case HOTSPOT_SIMPLE_SIGNS:
						if (CONTROLLER_DOWN (pad)) {
							rdt = hrt >> 4;
							text_window ();
						}
						rda = 0;
						break;
			#else			
				switch (hrt)
			#endif
			{

			#ifdef HOTSPOT_TYPE_REFILL
				case HOTSPOT_TYPE_REFILL:
					plife += LIFE_REFILL; if (plife > 99) plife = 99;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_OBJECT
				case HOTSPOT_TYPE_OBJECT:
					#ifdef ONLY_ONE_OBJECT_FLAG
						if (flags [ONLY_ONE_OBJECT_FLAG]) {
							rda = 0;
						} else {
							flags [ONLY_ONE_OBJECT_FLAG] = 1;
						}
					#else				
						pobjs ++;
					#endif
					break;
			#endif

			#ifdef HOTSPOT_TYPE_KEY
				case HOTSPOT_TYPE_KEY:
					pkeys ++;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_AMMO
				case HOTSPOT_TYPE_AMMO:
					if (AMMO_MAX - pammo < AMMO_REFILL) pammo = AMMO_MAX; else pammo += AMMO_REFILL;
					break;
			#endif

			#ifdef HOTSPOT_TYPE_STAR
				case HOTSPOT_TYPE_STAR:
					pstars ++;
					break;
			#endif
			}
			
			#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
				if (rda)
			#endif
			{
				SFX_PLAY (SFX_ITEM);
				
				// Delete hotspot
				_y = (hry >> 4) - 1; _x = hrx >> 4; 
				#ifdef HOTSPOTS_RESTORE_WITH_MAP_DATA				
					_t = scr_buff [(_y << 4) | _x];
				#else
					_t = 0;
				#endif
				set_map_tile ();

				hact [n_pant] = hrt = 0;
			}
		}
	}
}

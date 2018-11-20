// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Hud - customize here your hud routines.

void hud_update (void) {
	rdc = 71;
/*
	if (ptile_get_ctr != optile_get_ctr) {
		p_t2 (29, 0, ptile_get_ctr);
		optile_get_ctr = ptile_get_ctr;
	}
*/ 
	_y = 0; _t = 71;

	if (plife != oplife) {
		_x = 6; _n = plife; p_t2 ();
		oplife = plife;
	}

	if (pobjs != opobjs) {
		_x = 0x1d; _n = c_level [MAX_HOTSPOTS_TYPE_1] - pobjs; p_t2 (); 
		opobjs = pobjs;
	}

	if (pkeys != opkeys) {
		_x = 0x10; _n = pkeys; p_t2 ();
		opkeys = pkeys;
	}
		
/*
	rdc = 15;

	if (pstars != opstars) {
		p_t2 (18, 23, pstars);
		opstars = pstars;
	}
*/
}

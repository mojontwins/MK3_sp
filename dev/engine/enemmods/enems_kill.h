// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

	// All hail the monococo!

	//sfx_play (SFX_BUTT_HIT, SC_LEVEL);
	rdt = en_t [gpit] = 0;
#ifdef PERSISTENT_DEATHS	
	ep_killed [enoffs + gpit] = 1;
#endif

#ifdef COUNT_KILLED_ON_FLAG
	flags [COUNT_KILLED_ON_FLAG] ++;
#endif
	pbodycount ++;

#ifdef ENABLE_FABOLEES
	rdd = FABOLEES_MAX; while (rdd --) if (fbl_lock_on [rdd] == gpit) fbl_ct [rdd] = 0;
#endif

// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Level decompressor

// There's only one level, so this isn't needed. Most of it.

void level_setup (void) {
	// Decompress current level to the heap
	// Costomize as needed. See assets/levelset.h

	c_level = /*gp_gen = */levels [level];
	/*
	librarian_get_resource (*gp_gen ++, tsmaps);
	librarian_get_resource (*gp_gen ++, behs);
	//librarian_get_resource (*gp_gen ++, ss_enems);
	librarian_get_resource (*gp_gen ++, map);
	librarian_get_resource (*gp_gen ++, enems);
	librarian_get_resource (*gp_gen ++, hotspots);
	*/
#ifdef SCRIPTING_ON
	//scripts_index = scripts + level_script_offsets [*gp_gen];
	scripts_index = scripts;
#endif
	// Now you can use c_level as an array (pointed to the current level array)
}

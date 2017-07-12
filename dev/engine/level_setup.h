// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Level decompressor

void level_setup (void) {
	// Decompress current level to the heap
	// Costomize as needed. See assets/levelset.h

	c_level = gp_gen = levels [level];
	librarian_get_resource (*gp_gen ++, ts + 512);
	librarian_get_resource (*gp_gen ++, tsmaps);
	librarian_get_resource (*gp_gen ++, behs);
	librarian_get_resource (*gp_gen ++, ss_enems);
	librarian_get_resource (*gp_gen ++, map);
	librarian_get_resource (*gp_gen ++, enems);
	librarian_get_resource (*gp_gen ++, hotspots);

	// Now you can use c_level as an array (pointed to the current level array)
}

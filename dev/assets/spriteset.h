// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Organize stuff to make it useable to the engine.

// Pointers to sprite cells in the heap:

// Add more if you need them, and customize the init function

#define MAX_CELLS_16x16 	17
#define MAX_CELLS_16x8		0
#define MAX_CELLS_8x16		0
#define MAX_CELLS_8x8		3
#define MAX_CELLS 			(MAX_CELLS_8x8+MAX_CELLS_16x8+MAX_CELLS_8x16+MAX_CELLS_16x16)


unsigned char *sprite_cells [MAX_CELLS];

void sprite_cells_init (void) {
	rda = 0; 

	// 16x16 cells
	gp_gen = ss_main; gpit = MAX_CELLS_16x16; while (gpit --) {
		sprite_cells [rda ++] = gp_gen;
		gp_gen += 144;
	}

	// 8x8 cells
	gp_gen = ss_small; gpit = MAX_CELLS_8x8; while (gpit --) {
		sprite_cells [rda ++] = gp_gen;
		gp_gen += 64;
	}
}

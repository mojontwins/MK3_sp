// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Organize stuff to make it useable to the engine.

// Pointers to sprite cells in the heap:

// Add more if you need them, and customize the init function

#ifdef SPECCY
#define MAX_CELLS_16x24		21
#define MAX_CELLS_16x16 	8
#define MAX_CELLS_16x8		0
#define MAX_CELLS_8x16		0
#define MAX_CELLS_8x8		1
#define MAX_CELLS 			(MAX_CELLS_8x8+MAX_CELLS_16x8+MAX_CELLS_8x16+MAX_CELLS_16x16+MAX_CELLS_16x24)

unsigned char *sprite_cells [MAX_CELLS];

	void sprite_cells_init (void) {
		rda = 0; 

		// 24x24 cells
		gp_gen = ss_main; gpit = MAX_CELLS_16x24; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 192;
		}

		// 16x16 cells
		gp_gen = ss_enems; gpit = MAX_CELLS_16x16; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 144;
		}

		// 8x8 cells
		gp_gen = ss_small; gpit = MAX_CELLS_8x8; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 64;
		}
	}
#endif

#ifdef CPC

	#define MAX_CELLS_8x24		20			// Main player + characters + empty
	#define MAX_CELLS_8x16 		8			// 8 frames enems
	#define MAX_CELLS_4x8		1			// 1 Small (projectiles)
	#define MAX_CELLS 			(MAX_CELLS_8x24+MAX_CELLS_8x16+MAX_CELLS_4x8)

	unsigned char *sprite_cells [MAX_CELLS];
	void sprite_cells_init (void) {
		rda = 0; 

		gp_gen = ss_main; gpit = MAX_CELLS_8x24; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 96;
		}

		gp_gen = ss_enems; gpit = MAX_CELLS_8x16; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 64;
		}
		/*
		gp_gen = ss_small; gpit = MAX_CELLS_4x8; while (gpit --) {
			sprite_cells [rda ++] = gp_gen;
			gp_gen += 16;
		}
		*/
		sprite_cells [COCO_CELL_BASE] = ss_small;
	}

#endif

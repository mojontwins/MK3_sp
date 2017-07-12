// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

//#define DEBUG

// Main memory allocation & setup
#ifdef MODE_128K
#pragma output STACKPTR=23999
#define FREEPOOL 		61697
#define BASE_EP 		61857	// (FREEPOOL+160);
#else
//#pragma output STACKPTR=61952
#pragma output STACKPTR=61936
#define FREEPOOL 		23296
#define BASE_EP 		23696	// (FREEPOOL+400);
#endif

#include <spritepack.h>

#include "definitions.h"		// Main #defines
#include "ram/globals.h"		// Variables

// Compressed stuff at the beginning.
#include "assets/library.h"

// Now, stuff.
#include "ram/heap.h"			// Space for stuff (level + graphics)

#include "assets/levelset.h"
#include "assets/spriteset.h"
#include "assets/precalcs.h"

// Util base
#ifdef SPECCY
	#include "util/system_speccy.h"
#endif

#include "util/general.h"
#include "util/aplib.h"
#include "util/librarian.h"
#include "util/random.h"
#include "util/collisions.h"
#include "util/controls.h"

// Engine
#include "engine/level_setup.h"
#include "engine/printer.h"
#include "engine/simplecoco.h"
#ifndef DISABLE_HOTSPOTS
	#include "engine/hotspots.h"
#endif
#ifdef BREAKABLE_WALLS
	#include "engine/breakable.h"
#endif
#ifdef ENABLE_HITTER
	#include "engine/hitter.h"
#endif
#include "engine/enems.h"
#include "engine/player.h"
#include "engine/game.h"

#include "main.h"				// Main loop

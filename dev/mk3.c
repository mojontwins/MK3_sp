// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

//#define DEBUG
//#define CHEAT_ON

// Main memory allocation & setup
#ifdef SPECCY
#ifdef MODE_128K
	#pragma output STACKPTR=23999
	#define FREEPOOL 		61697
	#define BASE_EP 		61857	// (FREEPOOL+160);
#else
	//#pragma output STACKPTR=61952
	#pragma output STACKPTR=61936
	#define RAMTOP 			61440

	#define TEXTBUFF		23296
	#define BASE_EP 		23296 + 116
	#define FREEPOOL 		23296 + 116 + 252

	// Beware! If you use breakables, and 16x12, 
	// Change 320 for 384 and move the binary to 24050!
	#define BASE_BREAKABLE	23296 + 116 + 252 + 320

#endif
#endif

#ifdef CPC
	// This does not work. That's why I have replaced
	// cpc_crt0.asm. You can find my modified copy in
	// the cpc folder.
	// #pragma output STACKPTR=0xFFFF

	#define TEXTBUFF		0xC000 + 0x600
	#define FREEPOOL 		0xC800 + 0x600
	#define BASE_EN 		0xD000 + 0x600
	#define BASE_BREAKABLE	0xD800 + 0x600
	#define BASE_SPRITES 	0xE000 + 0x600
	#define BASE_SFX		0xE800 + 0x600	
	#define BASE_EP 		0xF000 + 0x600

	#define BASE_ARKOS		34868 	// 0x8834
	#define BASE_MUSIC		32250	// 0x7DFA
	#define BASE_SUPERBUFF	0x9000

	// Arkos addresses
	#define PLY_STOP		BASE_ARKOS+0x0753
	#define PLY_INIT		BASE_ARKOS+0x06FE
	#define PLY_SFX_INIT	BASE_ARKOS+0x0762
	#define PLY_PLAY 		BASE_ARKOS+0x000A // 0x883E
	#define PLY_SFX_PLAY	BASE_ARKOS+0x0776

	extern unsigned char nametable [0];

	#define SIZE_ARKOS_COMPRESSED 1149
#endif

#ifdef SPECCY
#include <spritepack.h>
#endif

#ifdef CPC
#include <cpcrslib.h>
#endif

#include "definitions.h"		// Main #defines
#include "ram/globals.h"		// Variables

#ifdef CPC
	#include "assets/pal.h"
#endif

#include "_somedefs.h"

// Compressed stuff at the beginning.
#include "assets/library.h"

// The script
#ifdef SCRIPTING_ON
	#include "assets/scripts.h"
#endif

// Now, text
#ifdef ENABLE_TEXT_WINDOW
	#include "assets/texts.h"
#endif

// Now, stuff.
#include "ram/heap.h"			// Space for stuff (level + graphics)

#include "assets/levelset.h"
#include "assets/spriteset.h"
#include "assets/precalcs.h"

// Custom assets
#include "assets/ob_data.h"
#include "assets/ob_texts.h"

// Utils
#include "util/aplib.h"
#ifdef SPECCY
	#include "util/system_speccy.h"
#endif
#ifdef CPC
	#include "util/system_cpc.h"
#endif

#include "util/random.h"
//#include "util/passwd_ninjajar_M.h"

#include "util/general.h"
#include "util/librarian.h"
#include "util/collisions.h"
#include "util/controls.h"

// Sound
#ifdef CPC
	#include "sound/arkos_cpc.h"
#endif

// Engine
#include "engine/printer.h"
#ifdef ENABLE_TIMED_MESSAGE
	#include "engine/timed_message.h"
#endif
#ifdef ENABLE_TEXT_WINDOW
	#include "engine/text_window.h"
#endif
#ifdef ENABLE_COCOS
	#include "engine/simplecoco.h"
#endif	
#ifndef DISABLE_HOTSPOTS
	#include "engine/hotspots.h"
#endif
#ifdef HOTSPOT_TYPE_KEY
	#include "engine/bolts.h"
#endif
#ifdef BREAKABLE_WALLS
	#include "engine/breakable.h"
#endif
#ifdef FLOATY_PUSH_BOXES
	#include "engine/fpb.h"
#endif
#ifdef ENABLE_HITTER
	#include "engine/hitter.h"
#endif
#include "engine/enems.h"
#include "engine/player.h"
#include "engine/hud.h"
#ifdef SCRIPTING_ON
	#ifdef ENABLE_EXTERN_CODE
		#include "engine/extern.h"
	#endif
	#include "engine/msc.h"
#endif
#include "engine/level_setup.h"

// Custom
#include "engine/ob.h"

#include "engine/game.h"

#include "main.h"				// Main loop

// Sound
#ifdef SE_BEEPER
	//#include "sound/beeper_music.h"
	#include "sound/beeper_sfx.h"
#endif

extern unsigned char END_OF_MAIN_BIN [0];

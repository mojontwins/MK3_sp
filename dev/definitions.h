// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Platform
	#define SPECCY

// General
	#define FIX_BITS						4

// Useful macros

// System stuff
	#define SW_SPRITES_16x16				4		// # of 16x16 software sprites
	#define SW_SPRITES_16x8					0		// # of 16x8 software sprites
	#define SW_SPRITES_8x16					0		// # of 8x16 software sprites
	#define SW_SPRITES_8x8					4		// # of 8x8 software sprites

	#define SW_SPRITES_ALL					(SW_SPRITES_16x16+SW_SPRITES_16x8+SW_SPRITES_8x16+SW_SPRITES_8x8)

	#define SPR_PLAYER						0
	#define SPR_ENEMS_BASE					1
	#define SPR_HITTER						4
	#define SPR_COCOS_BASE					5

	#define NUMBLOCKS 						(((SW_SPRITES_16x16*10)+(SW_SPRITES_8x8*5)+((SW_SPRITES_16x8+SW_SPRITES_8x16)*7)))
	#define AD_FREE							(61440-NUMBLOCKS*15)

// Macros
	#define MSB(x)							((x)>>8)
	#define LSB(x)							((x)&0xff)
	#define MAX(x1,x2)						((x1)<(x2)?(x2):(x1))
	#define MIN(x1,x2)						((x1)<(x2)?(x1):(x2))
	#define SGNI(n)							((n)<0?-1:((n)>0?1:0))
	#define SGNC(a,b,c)						((a)<(b)?-(c):(c))
	#define SATURATE_Z(n)					((n)<0?0:(n))
	#define SATURATE(v,max)					((v)>=0?((v)>(max)?(max):(v)):((v)<-(max)?-(max):(v)))
	#define SATURATE_N(v,min)				(v<min?min:v)
	#define ABS(n)							((n)<0?-(n):(n))
	#define DELTA(a,b)						((a)<(b)?(b)-(a):(a)-(b))
	#define CL(x1,y1,x2,y2)					((x1)+4>=(x2)&&(x1)<=(x2)+12&&(y1)+12>=(y2)&&(y1)<=(y2)+12)
	#define SUBSTR_SAT(a,b)					((a)>(b)?(a)-(b):0)
	#define DISABLE_SFX_NEXT_FRAME			*((unsigned char*)0x01bf)=1;
	#define ADD_SIGN2(a,b,v)				((a)==(b))?(0):(((a)>(b))?(v):(-(v)))
	#define ADD_SIGN(a,v) 					((a)?(((a)>0)?(v):(-(v))):(0))

	#define DIGIT(n)						(16+(n))

// About the heap
	#define SPRITES_EXTRA_CELLS				8		// # of 16x16 sprite cells besides the player
	#define SPRITES_SMALL_CELLS				3		// # of 8x8 sprite cells (sword, punch, bullets...)

// Game definitions
	#define MAX_PANTS						21
	#define MAX_LEVELS 						3

	#define N_ENEMS							3
	#define BOLTS_MAX 						1
	#define ENEMS_GENERAL_LIFE				1
	#define ENEMS_GENERAL_DYING_FRAMES		16
	#define ENEMS_GENERAL_HIT_FRAMES		16

	#define LIFE_INI						5
	#define LIFE_REFILL						1

// Screen position of stuff
	#define SCR_X							1
	#define SCR_Y 							2

// Game engine values

	//#define PERSISTENT_DEATHS
	#define PERSISTENT_ENEMIES
	#define ENEMS_SUFFER_WHEN_HITTING_PLAYER
	//#define ENEMS_MIN_KILLABLE			0x12
	//#define ENEMS_DIE_ON_EVIL_TILE

// Printer

	// Choose:
	#define PRINT_PSEUDOASCII				// patterns 0-63 == ASCII 32-95
	//#define PRINT_CUSTOM					// Custom 0xff-terminated strings (mkts)
	//#define PRINT_UL_PRINTER				// Used from the TEXT command (Scripting) 

// Map types & configurations

	//#define ENABLE_HOLES					// hole in the ground, for top-down view games.
	//#define HOLE_BIT						2

	#define ENABLE_CONVEYORS
	#define CONVEYOR_SPEED					16
	#define CONVEYOR_BIT 					32

	//#define ENABLE_SLIPPERY
	//#define SLIPPERY_BIT					16

	//#define ENABLE_QUICKSANDS
	//#define QUICKSANDS_BIT 				2

	//#define ENABLE_WATER 					
	//#define WATER_BIT 					2

	#define ENABLE_TILE_GET
	#define TILE_GET_BIT					2
	//#define TILE_GET_COUNT_ON_FLAG		1	// If not defined, count on tile_get_ctr
	
// Those are quite standard and 99% of the time you don't need to touch them

	#define EVIL_BIT						1
	#define PLATFORM_BIT					4
	#define OBSTACLE_BIT					8

	#define FLOOR_BITS						(OBSTACLE_BIT | PLATFORM_BIT)
	#define NOTAIR_BITS						(FLOOR_BITS | EVIL_BIT)

	#define SPECIAL_BEH						10	// For keyholes & pushable. Should include OBSTACLE_BIT

// Map format

	//#define MAP_FORMAT_RLE44
	//#define MAP_FORMAT_RLE53
	//#define MAP_FORMAT_BYTE_RLE
	#define MAP_FORMAT_PACKED
	//#define MAP_ENABLE_AUTOSHADOWS
	#define MAP_FORMAT_NOINDEX				// Use with PACKED/UNPACKED.

	//#define SCENERY_BITS					13	

	// Alt tile defines a substitute for tile 0 at random		
	#define MAP_USE_ALT_TILE				19
	#define ALT_TILE_EXPRESSION				((rand8()&31)==0)

	//#define MAP_DONT_PAINT_TILE_0			// If you want to use backdrops, make the painter skip tile 0
	#define MAP_CHECK_TOP
	//#define MAP_CHECK_BOTTOM

	//#define MAP_WITH_DECORATIONS

// Enems format

	//#define ENEMS_FORMAT_UNPACKED			// Good ol' unpacked format.
	#define ENEMS_FORMAT_COMPACTED			// Only active enems stored + index

// Enems stuff
	
	//#define ENEMS_UPSIDE_DOWN				// Enems may have this state (ie. when hit with Yun's fabolees)
	#define ENEMS_CELL_BASE					8

// Linear enemies

	#define ENABLE_LINEAR
	#define ENABLE_PLATFORMS				
	//#define LINEAR_COLLIDES				// Collides with BG & 8.
	//#define LINEAR_COLLIDE_EVERYTHING		// Collides with BG != 0.

// Type7 (with or without generators) enemies

	//#define ENABLE_TYPE7
	//#define TYPE7_BASE_SPRITE 			24
	//#define TYPE7_WITH_GENERATOR
	#define TYPE7_GENERATOR_LIFE			10
	#define TYPE7_MINION_LIFE 				1					// Actually this value + 1
	#define TYPE7_SPAWN_TIME				100+(rand8()&63)	// Must be of course > TYPE7_DYING_FRAMES!
	#define TYPE7_SMOKE_TIME				80 //40
	#define TYPE7_MINION_DYING_FRAMES		16
	#define TYPE7_MINION_HIT_FRAMES			16
	#define TYPE7_GENERATOR_DYING_FRAMES	16
	#define TYPE7_GENERATOR_HIT_FRAMES		16
	#define TYPE7_FIXED_SPRITE				3
	#define TYPE7_STOP_FRAMES				0x0f 				// 0x1f meghan
	#define TYPE7_STOP_RATE					0x0f 				// 0x7 meghan
	#define TYPE7_MINION_CELL_BASE			8

// Walker 

// Steady shooters
	//#define ENABLE_STEADY_SHOOTER
	#define STEADY_SHOOTER_CELL				18

// Monococo
	//#define ENABLE_MONOCOCO
	#define MONOCOCO_BASE_TIME_HIDDEN		150
	#define MONOCOCO_BASE_TIME_APPEARING	50
	#define MONOCOCO_BASE_TIME_ONBOARD		50
	#define MONOCOCO_FIRE_COCO_AT			MONOCOCO_BASE_TIME_ONBOARD/2
	//#define MONOCOCO_CELL_BASE			(en_s [gpit])
	#define MONOCOCO_CELL_BASE				8

// Monococo simple
	// Ninjajar's. A linear enemy which soots at random.
	#define ENABLE_MONOCOCO_SIMPLE
	#define MONOCOCO_SIMPLE_SHOOTING_FREQ	63

// Gyrosaws
	//#define ENABLE_GYROSAW
	#define GYROSAW_CELL_BASE				72
	#define GYROSAW_V						1
	//#define GYROSAW_SLOW

// Saws
	//#define ENABLE_SAW
	#define SAW_CELL_BASE					20
	#define SAW_V_DISPL						4
	#define SAW_EMERGING_STEPS				10
	#define SAW_CELL_OCCLUSION				sssaw_02

// Precalc Fanty (0x3x)
	//#define ENABLE_PRECALC_FANTY
	
// Precalc, all integer homing fanty from Goddess. (0x3x)	
	#define ENABLE_PRECALC_HOMING_FANTY
	#define FANTY_ST_IDLE					0
	#define FANTY_ST_PURSUING				1
	#define FANTY_ST_RETREATING				2
	#define FANTY_ST_RESET					3
	#define FANTY_SIGHT_DISTANCE			96

// Precalc, all integer fanty adapted from Goddess (with timer)
// Substitutes Fanty (0x3x as well)	
	//#define ENABLE_PRECALC_TIMED_FANTY

// Global for all fanties
	//#define FANTY_COLLIDES
	#define FANTY_CELL_BASE 				12
	#define FANTY_REPOSITION_NONETHELESS			// Reposition fanty to origin when entering screen regardless of configuration

// Catacrock
	//#define ENABLE_CATACROCK
	#define CATACROCK_CELL_BASE 			28
	#define CATACROCK_CROCK_FRAMES			50
	#define CATACROCK_G 					4
	#define CATACROCK_MAXV					64

// Nube (Ninjajar!)
	#define ENABLE_NUBE
	#define NUBE_SIMPLE_SHOOTING_FREQ		63

// Espectros
	//#define ENABLE_ESPECTROS
	#define ESPECTRO_CELL_BASE 				8
	#define ESPECTRO_A 						1
	#define ESPECTRO_MAXV 					32
	#define ESPECTRO_REBOUND				48
	#define ESPECTRO_V_RETREATING			8

// Custom fumettos
	//#define ENABLE_FUMETTOS
	#define FUMETTOS_MAX 					3
	#define FUMETTO_BASE_PATTERN 			2

// Saws
	//#define ENABLE_SAWS
	// What else?

// Springs
	//#define ENABLE_SPRINGS
	#define SPRINGS_MAX 					8
	#define SPRINGS_TILE					44
	#define SPRINGS_SOUND					6
	//#define SPRINGS_CREATE_FROM_MAP		28			// Detect this tile # in the map to create
	//#define SPRINGS_X 					flags [15]	// Where to look up coordinates (if you are not creating from map)
	//#define SPRINGS_Y 					flags [14]	// Where to look up coordinates

// Propellers

	//#define ENABLE_PROPELLERS
	#define PROPELLERS_MAX					8
	#define PROPELLERS_PATTERN				64			// Animating patterns start here
	#define PROPELLERS_BIT 					64			// Bit to make a tile "propellable"
	#define PROPELLERS_LIMIT				5			// max # of tiles high. Comment for no limit
	//#define PROPELLERS_CREATE_FROM_MAP	33			// Detect this tile # in the map to create
	//#define PROPELLERS_X 					flags [15] 	// Use these if you want to create propellers
	//#define PROPELLERS_Y 					flags [14]	// by other means (for example script & EXTERN)
	#define PROPELLERS_ON_OFF
	#define PROPELLERS_MAX_CTR_FIXED		120
	#define PROPELLERS_INI_CTR				(PROPELLERS_MAX_CTR_FIXED - (propellers_idx << 2))

// Estrujators

	//#define ENABLE_ESTRUJATORS
	#define ESTRUJATORS_MAX					8			// 
	//#define ESTRUJATORS_CREATE_FROM_MAP
	#define ESTRUJATORS_TILE 				21			// Detect this tile # in the map to create
	//#define ESTRUJATORS_X					flags [15]	// Use these if you want to create estrujators
	//#define ESTRUJATORS_Y					flags [14]	// by other means (for example script & EXTERN)
	//#define ESTRUJATORS_DELAY				flags [13]	// Same, for the delay.
	#define ESTRUJATORS_DOWN_IDLE_TIME 		10
	#define ESTRUJATORS_TILE_DELETER		3
	#define ESTRUJATORS_HEIGHT				3			// In tiles.
	#define ESTRUJATORS_SLOW							// Half as slow. Twice as predictable

// Cataracts

	// Remember, cataracts & estrujators share memory structures,
	// If you define CATARACTS but not ESTRUJATORS, please keep
	// ESTRUJATORS_MAX #define'd.

	//#define ENABLE_CATARACTS
	//#define CATARACTS_CREATE_FROM_MAP		
	//#define CATARACTS_X					flags [15]	// Use these if you want to create cataracts
	//#define CATARACTS_Y					flags [14]	// by other means (for example script & EXTERN)
	#define CATARACTS_IDLE_TIME				240
	#define CATARACTS_PATTERN 				0xcc
	#define CATARACTS_DELETE_PATTERN 		0xca
	#define CATARACTS_HEIGHT				4			// In tiles.
	#define CATARACTS_TILE					23
	#define CATARACTS_TILE_ALT				16

// Pezón
	//#define ENABLE_PRECALC_PEZON
	#define PEZON_WAIT						50
	#define PEZONS_BASE_SPRID				60

// Auxiliary stuff

	#if defined (ENABLE_STEADY_SHOOTER) || defined (ENABLE_MONOCOCO) || defined (ENABLE_MONOCOCO_SIMPLE) || defined (ENABLE_LAME_BOSS_1)
	
	#define ENABLE_COCOS
	#define COCOS_MAX 						2
	#define COCO_CELL_BASE					17
	#define COCO_V							128
	#define ONE_PER_ENEM

	#if defined (ENABLE_MONOCOCO) || defined (ENABLE_MONOCOCO_SIMPLE) || defined (ENABLE_LAME_BOSS_1)
	#define ENABLE_COCO_AIMED
	#define COCO_FAIR_D						64
	#endif

	#if defined (ENABLE_STEADY_SHOOTER)
	#define ENABLE_COCO_STRAIGHT
	#endif

	#if defined (ENABLE_NUBE)
	#define ENABLE_COCO_AIMED_DOWN
	#endif

	#endif

	#if defined (ENABLE_FANTY) || defined (ENABLE_GENERATONIS) || defined (ENABLE_ESPECTROS) || defined (ENABLE_CATACROCK)
	#define ENEMIES_NEED_FP
	#endif

	#if defined (PROPELLERS_CREATE_FROM_MAP) || defined (SPRINGS_CREATE_FROM_MAP) || defined (ESTRUJATORS_CREATE_FROM_MAP) || defined (CATARACTS_CREATE_FROM_MAP)
	#define CREATE_STUFF_FROM_MAP
	#endif

// Evil tiles

	// Enable the ones you need. Use a custom way to switch between them if you activate several:
	//#define EVIL_TILE_ON_FLOOR
	//#define EVIL_TILE_ON_CEILING
	//#define EVIL_TILE_MULTI
	#define EVIL_TILE_CENTER

	#if defined (EVIL_TILE_MULTI) || defined (EVIL_TILE_ON_FLOOR) || defined (EVIL_TILE_ON_CEILING) || defined (EVIL_TILE_CENTER)
	#define ENABLE_EVIL_TILE
	#endif

// Player

	// Enable the ones you need. Use a custom way to switch between them if you activate several:
	//#define PLAYER_GENITAL
	#define PLAYER_JUMPS
	//#define PLAYER_DOUBLE_JUMP
	//#define PLAYER_MONONO
	//#define PLAYER_JETPAC
	//#define PLAYER_HIDES

	#define PLAYER_8_PIXELS					// Collision box is 8x8 instead of 8x16

	//#define PLAYER_PUSH_BOXES
	//#define PLAYER_FIRE_TO_PUSH

	//#define PLAYER_NO

	#if defined (PLAYER_JUMPS) || defined (PLAYER_MONONO) || defined (PLAYER_JETPAC)
	#define PLAYER_GRAVITY
	#endif

	// When hit

	//#define PLAYER_REBOUNDS
	#define PLAYER_FLICKERS					50
	#define PLAYER_DIE_AND_RESPAWN

	// Ways to kill

	//#define PLAYER_FABOLEES
	//#define PLAYER_SPINS
	//#define PLAYER_SPINS_KILLS
	//#define PLAYER_STEPS_ON_ENEMIES
	//#define PLAYER_STEPS_KILLS
	//#define PLAYER_JUMPS_ON_ENEMIES		// requires PLAYER_STEPS_ON_ENEMIES
	//#define PLAYER_BUTT
	#define PLAYER_PUNCHES
	#define KILLABLE_CONDITION				(1)	

	#ifdef PLAYER_PUNCHES
	#define HITTER_LAST_FRAME				6
	#define HITTER_HOT_MIN					3
	#define HITTER_HOT_MAX					4
	#define HITTER_CELL_BASE				18
	#endif

	#if defined(PLAYER_PUNCHES)
	#define ENABLE_HITTER
	#endif

// Things related to shooting

	//#define PLAYER_CAN_FIRE
	//#define PLAYER_VX_RECOIL				32

	// Ammonition
	//#define AMMO_MAX						99
	#define AMMO_REFILL						50

	// Turret

	//#define PLAYER_TURRET
	#define TURRET_FRAMES					16 	

	// Bullets

	#define BULLETS_MAX						4
	#define BULLETS_V 						4

	//#define SHOOTING_DRAINS

	//#define ENABLE_PUAS
	#define PUAS_MAX						2
	#define PUAS_VX							2

	// Fabolees

	//#define ENABLE_FABOLEES
	#define FABOLEES_MAX 					3

	// Movement values 

	#define PLAYER_VX_MAX					64
	#define PLAYER_AX						16
	#define PLAYER_RX						24	
	#define PLAYER_VX_MIN 					8		// (PLAYER_AX << 2)

	#define PLAYER_VY_FALLING_MAX			64
	#define PLAYER_G						6 
	#define PLAYER_G_JUMPING				1
	#define PLAYER_VY_MIN 					16

	//#define PLAYER_VY_SINKING				2		// For quicksands
	//#define PLAYER_VY_EXIT_QUICKSANDS 	8

	// #define PLAYER_VY_JETPAC_MAX			12		// Jetpac values
	// #define PLATER_AY_JETPAC 			2

	#define PLAYER_VY_JUMP_INITIAL			56
	#define PLAYER_VY_JUMP_RELEASE			24
	#define PLAYER_VY_JUMP_A_STEPS 			8
	//#define PLAYER_AY_JUMP				8

	//#define PLAYER_VY_JUMP_FROM_ENEM 		32
	
	//#define PLAYER_AY_PROPELLER			2
	//#define PLAYER_VY_PROPELLER_MAX		32
	
	// Y Axis, genital
	/*
	#define PLAYER_VY_MAX					32
	#define PLAYER_AY						6
	#define PLAYER_RY						8
	#define PLAYER_VY_MIN 					8
	*/

	//#define PLAYER_G_WATER 				1
	//#define PLAYER_VY_MAX_SINK_WATER		16
	//#define PLAYER_VY_OUT_OF_WATER		64
	//#define PLAYER_AY_SWIM				24
	//#define PLAYER_VY_SWIM_MAX			24

	//#define PLAYER_AX_SWIMMING			1
	//#define PLAYER_RX_SWIMMING			2
	//#define PLAYER_VX_MAX_SWIMMING		20

	#define PLAYER_V_INERTIA				4
	#define PLAYER_V_REBOUND				64
	#define PLAYER_V_REBOUND_MULTI			96
	#define PLAYER_VY_BUTT_REBOUND			48
	#define PLAYER_HIT_FRAMES				32
	#define PLAYER_REBOUND_REVERSE_DIRECTION

	#define PLAYER_VY_FLICK_TOP				64
	#define PLAYER_VY_FLICK_TOP_SWIMMING	PLAYER_VY_SWIM_MAX

	// Breakable walls

	#define BREAKABLE_WALLS
	#define BREAKABLE_PERSISTENT					// Make changes persistent. Does not work with RLE'd maps.
	#define BREAKABLE_MAX 					4		// Breaking at the same time
	#define BREAKABLE_FRAMES_DESTROY		8		// Show breaking tile for N frames
	#define BREAKABLE_BREAKING_TILE			31
	#define BREAKABLE_BIT					128		// 1··· ····

	// Define those so you have to hit tiles several times
	// Each time you hit, the attr gets added the INCREMENT_COUNTER.
	// Tile is broken if attr & MASK == HITS. Do your bit math.
	//#define BREAKABLE_AND_MASK			0x60	// ·11· ····
	//#define BREAKABLE_HITS 				0x60	// ·11· ····
	//#define BREAKABLE_INCREMENT_COUNTER	0x20    // ·01· ····
	//#define BREAKABLE_FRAMES_HIT			4

	#define BREAKABLE_TILE_SPECIAL			12		// If the broken tile is this one, spawn
	#define BREAKABLE_TILE_GET				22		// this tile if this expression is true:
	#define BREAKABLE_TILE_EXPRESION		((rand8()&3)<2)

// Hotspots
// Define those to include all related code

	#define HOTSPOT_TYPE_OBJECT				1
	//#define HOTSPOT_TYPE_KEY 				2
	#define HOTSPOT_TYPE_REFILL 			3
	//#define HOTSPOT_TYPE_AMMO				4
	#define HOTSPOTS_BASE_TILE				15		// Draw tile hrt+constant
	#define HOTSPOTS_RESTORE_WITH_MAP_DATA			// Delete hotspot tile with the proper tile.

	//#define HOTSPOTS_MAY_CHANGE					// Copy hotspot type to RAM. It may change ingame
	//#define DISABLE_HOTSPOTS

// Expand upon this when needed

	#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_SPINS_KILLS) || defined (PLAYER_STEPS_ON_ENEMIES) || defined (ENEMS_DIE_ON_EVIL_TILE) || defined (ENABLE_HITTER)
	#define ENEMIES_CAN_DIE
	#define EXPLOSION_CELL_BASE 			16
	#endif

	#if defined (PLAYER_DIE_AND_RESPAWN) || defined (ENABLE_HOLES)
	#define PLAYER_SAFE
	#endif

// Handy (expand?)
	#if defined (HOTSPOT_TYPE_KEY) || defined (PLAYER_PUSH_BOXES)
	#define PLAYER_PROCESS_BLOCK
	#endif

	#if defined (ENABLE_WATER) || defined (EVIL_TILE_CENTER)
	#define PLAYER_ENABLE_CENTER_DETECTIONS
	#endif

// Scripting stuff

	//#define SCRIPTING_ON
	//#define CLEAR_FLAGS
	//#define MAX_FLAGS 					32
	//#define COUNT_KILLED_ON_FLAG 			1
	//#define ONLY_ONE_OBJECT_FLAG 			2
	//#define PLAYER_INV_FLAG				0 		// Exports pinv to this flag

	//#define LINE_OF_TEXT_Y				24
	//#define LINE_OF_TEXT_X				1

	//#define ENABLE_FIRE_ZONE
	//#define ENABLE_EXTERN_CODE
	//#define FIRE_SCRIPT_WITH_ANIMATION

	//#define ENABLE_CONTAINERS
	#define CONTAINERS_MAX 					5		// As few as you need!
	//#define CONTAINER_ACTION_STOPS_CHECKS			// ifdef, container hit means no fire script ran
	#define CONTAINERS_HAS_GOT_FLAG			30
	#define CONTAINERS_X 					sc_x
	#define CONTAINERS_Y 					(sc_y+1)
	#define CONTAINERS_N 					sc_n

	//#define SPRITE_NO 					ssmisc_05

	// Some stuff make hotspots managing slightly more complex

	#if defined (ONLY_ONE_OBJECT_FLAG)
	#define HOTSPOTS_LOGIC_MORE_COMPLEX
	#endif

// Animation cells

	#define CELL_FACING_RIGHT 				0
	#define CELL_FACING_LEFT				4
	#define CELL_IDLE						1
	#define CELL_AIRBORNE					3
	const unsigned char walk_frames [] = {1, 0, 1, 2};

// SFX

	#define SFX_START						0
	#define SFX_JUMP						1			
	#define SFX_GET_ITEM					2
	#define SFX_ENEMY_HIT					3
	#define SFX_EXTRA_1						4
	#define SFX_SHOOT						5
	#define SFX_FART						6
	#define SFX_CHOF						7
	#define SFX_BUTT_FALL					8
	#define SFX_BUTT_HIT					9
	#define SFX_BLOCO						10
	#define SFX_THUNDER						11
	#define SFX_ESTRUJATOR 					11
	#define SFX_FABOLEE 					12
	#define SFX_TU 							13
	#define SFX_TICK						14
	#define SFX_FLUSH						15
	#define SFX_RING						2
	#define SFX_EMMERALD					13

// Music

	#define MUSIC_TITLE						0
	#define MUSIC_INGAME 					1
	//#define MUSIC_EVENT					1
	//#define MUSIC_GAME_OVER 				3

// Make code more readable:

	#define MONOCOCO_COUNTER 				en_my
	#define _MONOCOCO_COUNTER				_en_my

	#define GYROSAW_COUNTER 				en_mx
	#define GYROSAW_DIRECTION				en_my
	#define _GYROSAW_DIRECTION				_en_my
	#define _GYROSAW_COUNTER 				_en_mx
	
	#define CATACROCK_COUNTER 				en_mx
	#define CATACROCK_WAIT 					en_my
	#define _CATACROCK_WAIT 				_en_my
	#define _CATACROCK_COUNTER				_en_mx
	#define _CATACROCK_STATE 				_en_state

	#define GENERATONI_COUNTER 				en_x2
	#define GENERATONI_WAIT 				en_y2
	#define GENERATONI_HL 					en_my

	#define STEADY_SHOOTER_DIRECTION		en_my
	#define STEADY_SHOOTER_WAIT				en_mx
	#define _STEADY_SHOOTER_WAIT 			_en_mx
	#define _STEADY_SHOOTER_DIRECTION       _en_my

	#define SAW_ORIENTATION					en_s
	#define SAW_EMERGING_DIRECTION			en_my
	#define SAW_MOVING_DIRECTION 			en_mx
	#define _SAW_EMERGING_DIRECTION			_en_my
	#define _SAW_MOVING_DIRECTION 			_en_mx

	#define PEZON_TIMER 					en_mx
	#define PEZON_MAX_TIME					en_y2
	#define PEZON_INCS_IDX 					en_my
	#define _PEZON_TIMER					_en_mx
	#define _PEZON_MAX_TIME					_en_y2
	#define _PEZON_INCS_IDX					_en_my

	#define SW_SPRITES_16x16_BASE			0
	#define SW_SPRITES_16x8_BASE			SW_SPRITES_16x16_BASE+SW_SPRITES_16x16
	#define SW_SPRITES_8x16_BASE			SW_SPRITES_16x8_BASE+SW_SPRITES_16x8
	#define SW_SPRITES_8x8_BASE				SW_SPRITES_8x16_BASE+SW_SPRITES_8x16
	
	// Custom stuff

	//#define PGAUGE_MAX 					7
	//#define PGAUGE_TRANSFORM_PENALTY		4

// platform-related features
	#ifdef SPECCY
	#define CONTROLLER_READ 				((joyfunc) (&keys));
	#define CONTROLLER_LEFT(a)				(((a) & sp_LEFT) == 0)
	#define CONTROLLER_RIGHT(a)				(((a) & sp_RIGHT) == 0)
	#define CONTROLLER_UP(a)				(((a) & sp_UP) == 0)
	#define CONTROLLER_DOWN(a)				(((a) & sp_DOWN) == 0)
	#define BUTTON_A(a)						(((a) & sp_FIRE) == 0)
	#define BUTTON_B						(sp_KeyPressed (key_jump))

	#define SCREEN_UPDATE					sp_UpdateNow ()
	#define SPRITE_CELL_PTR_UPDATE(a)		spr_cur [(a)] = spr_next [(a)]
	#define SPRITE_UPDATE_ABS(a, x, y)		sp_MoveSprAbs (sp_sw [(a)], spritesClip, spr_next [(a)] - spr_cur [(a)], SCR_Y + ((y)>>3), SCR_X + ((x)>>3), (x) & 7, (y) & 7)
	#define SPRITE_OUT(a)					sp_MoveSprAbs (sp_sw [(a)], spritesClip, 0, -2, -2, 0, 0);

	#endif

// Custom flags for level properties may go here. Or may not.

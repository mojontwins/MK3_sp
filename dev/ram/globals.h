// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// ----------------------------------------------------------
// System 
// ----------------------------------------------------------
#ifdef SPECCY
	struct sp_UDK keys;
	void *joyfunc;
	int key_jump;

	struct sp_Rect spritesClipValues = { SCR_Y, SCR_X, 20, 30 };
	struct sp_Rect *spritesClip;

	struct sp_SS *sp_sw [SW_SPRITES_ALL];
	unsigned char *spr_next [SW_SPRITES_ALL];
	unsigned char *spr_cur [SW_SPRITES_ALL];
#endif

unsigned char spr_on [SW_SPRITES_ALL];
unsigned char spr_x [SW_SPRITES_ALL], spr_y [SW_SPRITES_ALL];
unsigned char spr_idx;

// ----------------------------------------------------------
// General 
// ----------------------------------------------------------
unsigned char gpit, gpjt;
unsigned int gpint;
signed char rds;
signed int rdsint;
unsigned char rda, rdb, rdc, rdd, rde, rdf, rdi;
unsigned char rdx, rdy, rdt, rdct;
unsigned char *gp_gen;
unsigned char *gp_int;
unsigned char pad0, pad, pad_this_frame;

// ----------------------------------------------------------
// Collision 
// ----------------------------------------------------------
unsigned char cx1, cx2, cy1, cy2, at1, at2;

// ----------------------------------------------------------
// Current level, screen, etc
// ----------------------------------------------------------
unsigned char level;
unsigned char *c_level;
unsigned char n_pant, on_pant;
unsigned char half_life, frame_counter, hl_proc;
unsigned char do_game, first_time;

// ----------------------------------------------------------
// Map stuff
// ----------------------------------------------------------
unsigned char *gp_map;
#ifdef MODE_128K
	unsigned char scr_attr [160];
#else
	unsigned char *scr_attr = FREEPOOL+160;	
#endif
unsigned char *scr_buff = FREEPOOL;

// ----------------------------------------------------------
// Player
// ----------------------------------------------------------
#ifdef ENEMIES_CAN_DIE
unsigned char pbodycount, opbodycount;
#endif
unsigned char plife, oplife, pobjs, opobjs, pkeys, opkeys;
#ifdef AMMO_MAX
unsigned char pammo, opammo;
#endif
unsigned char evil_tile_hit;
unsigned char pkilled;
unsigned char pemmeralds;
unsigned char pinv;
unsigned char guay_ct, use_ct, no_ct;

unsigned char prx, pry;
signed int px, py;
signed char pvx;
signed int pvy;

#ifdef PLAYER_JUMPS
	unsigned char pj, pctj, pthrust, pjb;
	unsigned char pjustjumped;
#endif

#ifdef PLAYER_DOUBLE_JUMP
	unsigned char njumps;
#endif

#ifdef PLAYER_BUTT
	unsigned char pbutt;
#endif

unsigned char pfiring;
unsigned char phit, pflickering;
unsigned char pfacing, pgotten, ppossee, pregotten;
unsigned char pfixct;
unsigned char psprid; 
signed int pvylast;
signed char pgtmx, pgtmy;
unsigned char pcharacter;

#ifdef PLAYER_SPINS
	unsigned char pspin;
#endif	

#ifdef PLAYER_GENITAL
	unsigned char pfacingh, pfacingv, pfacinglast;
#endif

#if defined (EVIL_TILE_MULTI) || defined (EVIL_TILE_CENTER)
	signed int pcx, pcy;
#endif

#ifdef PLAYER_SAFE
	unsigned char safe_prx, safe_pry;
	unsigned char safe_n_pant;
#endif

#ifdef SHOOTING_DRAINS
	unsigned char pgauge;
#endif

unsigned char pwashit;
unsigned char pstatespradder;

#ifdef PLAYER_HIDES
	unsigned char phidden;
#endif

#ifdef ENABLE_HOLES
	unsigned char pholed;
#endif

#ifdef ENABLE_SLIPPERY
	unsigned char pslips;
#endif

#ifdef ENABLE_WATER
	unsigned char pwater;
	unsigned char pwaterthrustct;
#endif

#ifdef PLAYER_PUSH_BOXES
	unsigned char pbx1, pby1;
#endif

unsigned char tile_get_ctr;

// ----------------------------------------------------------
// Enemies
// ----------------------------------------------------------
unsigned char _en_t, _en_x, _en_y;
unsigned char _en_x1, _en_x2, _en_y1, _en_y2;
signed char _en_mx, _en_my;
unsigned char _en_state, _en_ct;

#ifdef ENEMS_UPSIDE_DOWN
	unsigned char _en_ud;
#endif

unsigned char en_hl [N_ENEMS];
unsigned char en_life [N_ENEMS];
unsigned char en_s [N_ENEMS];
unsigned char en_facing [N_ENEMS];
unsigned char en_dying [N_ENEMS]; 
unsigned char en_washit [N_ENEMS];

#ifdef ENABLE_TYPE_7
	unsigned char en_fishing [N_ENEMS];
	unsigned char en_v [N_ENEMS];
#endif

#ifdef TYPE7_WITH_GENERATOR
	unsigned char en_gen_washit [N_ENEMS];
	unsigned char en_gen_dying [N_ENEMS];
	unsigned char en_gen_life [N_ENEMS];
#endif

#ifdef ENEMIES_NEED_FP
	#if defined (ENABLE_FANTY) || defined (ENABLE_ESPECTROS) || defined (ENABLE_PRECALC_TIMED_FANTY)
	unsigned char fanty_timer [N_ENEMS];
	signed int enf_x [N_ENEMS];
	signed char enf_vx [N_ENEMS];
	signed int _enf_x;
	signed char _enf_vx;
	#endif
	signed int enf_y [N_ENEMS];
	signed char enf_vy [N_ENEMS];
	signed int _enf_y;
	signed char _enf_vy;
#endif

unsigned char en_t [N_ENEMS];
unsigned char en_x [N_ENEMS];
unsigned char en_y [N_ENEMS];
unsigned char en_x1 [N_ENEMS];
unsigned char en_y1 [N_ENEMS];
unsigned char en_x2 [N_ENEMS];
unsigned char en_y2 [N_ENEMS];
signed char en_mx [N_ENEMS];
signed char en_my [N_ENEMS];

unsigned char en_state [N_ENEMS];
unsigned char en_ct [N_ENEMS];

#ifdef PERSISTENT_ENEMIES
/*
	unsigned char ep_x [3 * MAX_PANTS];
	unsigned char ep_y [3 * MAX_PANTS];
	signed char ep_mx [3 * MAX_PANTS];
	signed char ep_my [3 * MAX_PANTS];
*/
	unsigned char *ep_x = BASE_EP;
	unsigned char *ep_y = BASE_EP + 3*MAX_PANTS;
	signed char *ep_mx = BASE_EP + 3*MAX_PANTS + 3*MAX_PANTS;
	signed char *ep_my = BASE_EP + 3*MAX_PANTS + 3*MAX_PANTS + 2 * 3*MAX_PANTS;
	unsigned int ep_it;
#endif

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)	
	unsigned char ep_killed [MAX_PANTS * N_ENEMS];
#endif

#ifdef ENEMS_UPSIDE_DOWN
	unsigned char en_ud [N_ENEMS];
#endif

unsigned char spr_id, en_fr;
unsigned char enoffs;
unsigned char genflipflop;
unsigned char is_platform;
unsigned char encelloffset;

#ifdef LINEAR_COLLIDES
	unsigned char en_collx, en_colly;
#endif

// ----------------------------------------------------------
// Hitter
// ----------------------------------------------------------
unsigned char hitter_hs_x;
unsigned char hitter_hs_y;
unsigned char hitter_x, hitter_y, hitter_frame;

// ----------------------------------------------------------
// Breakable walls
// ----------------------------------------------------------
#ifdef BREAKABLE_WALLS
	#ifdef MODE_128K
		unsigned char brk_ac [BREAKABLE_MAX], brk_slots [BREAKABLE_MAX];
		unsigned char brk_slot;
		unsigned char brk_x [BREAKABLE_MAX], brk_y [BREAKABLE_MAX];
	#else
		unsigned char *brk_ac = FREEPOOL+320;
		unsigned char *brk_slots = FREEPOOL+320 + BREAKABLE_MAX;
		unsigned char *brk_x = FREEPOOL+320 + 2*BREAKABLE_MAX;
		unsigned char *brk_y = FREEPOOL+320 + 3*BREAKABLE_MAX;
		unsigned char brk_slot;
	#endif
#ifdef BREAKABLE_TILE_SPECIAL
	#ifdef MODE_128K	
		unsigned char brk_sp [BREAKABLE_MAX];	
	#else	
		unsigned char *brk_sp = FREEPOOL+320 + 4*BREAKABLE_MAX;
	#endif	
#endif
	unsigned char process_breakable;
#endif

// ----------------------------------------------------------
// Hotspots
// ----------------------------------------------------------
#ifndef DEACTIVATE_HOTSPOTS
	unsigned char hrx, hry, hrt;
	unsigned char max_hotspots_type_1;
	unsigned char hact [MAX_PANTS];
	#ifdef HOTSPOTS_MAY_CHANGE
	unsigned char ht [MAX_PANTS];
	#endif
#endif

// ----------------------------------------------------------
// Cocos
// ----------------------------------------------------------
#ifdef ENABLE_COCOS
	signed int _coco_x, _coco_y;
	unsigned char coco_it;
	signed int coco_x [COCOS_MAX], coco_y [COCOS_MAX];
	signed int coco_vx [COCOS_MAX], coco_vy [COCOS_MAX];
	unsigned char coco_slots [COCOS_MAX], coco_slot;
#endif

// ----------------------------------------------------------
// ISR
// ----------------------------------------------------------
unsigned char isrc;

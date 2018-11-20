// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Sets up control

const unsigned int keyscancodes [] = {
	0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,		// WSADMN
	0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0x087f 		// QAOP_N
};

#ifdef SPECCY
void controls_setup (void) {
	switch (gpit) {
		case 1:
		case 2:
			joyfunc = sp_JoyKeyboard;
			gpjt = gpit == 2 ? 6 : 0;
			keys.up = keyscancodes [gpjt ++];
			keys.down = keyscancodes [gpjt ++];
			keys.left = keyscancodes [gpjt ++];
			keys.right = keyscancodes [gpjt ++];
			key_jump = keyscancodes [gpjt ++];
			keys.fire = keyscancodes [gpjt];
			break;
		case 3:
			joyfunc = sp_JoyKempston;
			break;
		case 4:
			joyfunc = sp_JoySinclair1;
			break;
	}
}
#endif

#ifdef CPC
	#define LASTKEY 5 
	
	unsigned char ktext_0 [] = "LEFT ";
	unsigned char ktext_1 [] = "RIGHT";
	unsigned char ktext_2 [] = "DOWN ";
	unsigned char ktext_3 [] = "UP   ";
	unsigned char ktext_4 [] = "ACTION";
	unsigned char *ktexts [] = {
		ktext_0, ktext_1, ktext_2, ktext_3, ktext_4 
	};

	void controls_setup (void) {
		// Redefinition code
		_x = 6; _y = 15; p_s ("                     /                     ");

		// First of all, clear up definitions so no collision is possible:
		for (gpit = 0; gpit <= KEY_BUTTON_B; gpit ++) cpc_AssignKey (gpit, 0);
		
		while (cpc_AnyKeyPressed ());
		_x = 8; _y = 15; p_s ("PRESS A KEY FOR:");
		for (gpit = 0; gpit < LASTKEY; gpit ++) {
			_x = 13; _y = 16; p_s (ktexts [gpit]);
			cpc_ShowTileMap (0);
			cpc_RedefineKey (gpit);
			//while (cpc_TestKey (gpit));			
		}
	}
#endif

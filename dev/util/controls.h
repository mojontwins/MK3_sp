// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

// Sets up control

const unsigned int keyscancodes [] = {
	0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,		// WSADMN
	0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0x087f 		// QAOP_N
};

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
			keys.fire = keyscancodes [gpjt ++];
			key_jump = keyscancodes [gpjt];
			/*
			gp_int = keyscancodes + (gpit == 2 ? 6 : 0);
			keys.up = *gp_int ++;
			keys.down = *gp_int ++;
			keys.left = *gp_int ++;
			keys.right = *gp_int ++;
			keys.fire = *gp_int ++;
			key_jump = *gp_int;
			*/
			break;
		case 3:
			joyfunc = sp_JoyKempston;
			break;
		case 4:
			joyfunc = sp_JoySinclair1;
			break;
	}
}

// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Collisions

void cm_two_points (void) {
	// Calculates at1 & at2 from cx1, cy1 & cx2, cy2
	if (cy1 > TY_MAX || cy2 > TY_MAX) { at1 = at2 = 0; return; }
	at1 = scr_attr [cx1 | ((cy1 ? cy1 - 1 : 0) << 4)];
	at2 = scr_attr [cx2 | ((cy2 ? cy2 - 1 : 0) << 4)];
}

unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	return (x1 + 7 >= x2 && x1 <= x2 + 15 && y1 + 7 >= y2 && y1 <= y2 + 15);
}

// MT MK3 ZX v0.1 [Ninjajar_M]
// Copyleft 2017 by The Mojon Twins

	// Monococo simple, as seen in Ninjajar!

	// After this, the mono may move as a linear enemy. That means that
	// the enemy sprite MUST be correctly set in the ponedor.

	if ((rand8 () & MONOCOCO_SIMPLE_SHOOTING_FREQ) == 1) {
		rdx = _en_x + 4; rdy = _en_y + 4; simplecoco_aimed_new ();
	}
	spr_id = en_s [gpit] + (prx > _en_x ? 1 : 0);
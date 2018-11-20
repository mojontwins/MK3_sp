// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Nube.

_en_x += ADD_SIGN2 (prx, _en_x, _en_mx); _en_y = _en_y1;
if ((rand8 () & NUBE_SIMPLE_SHOOTING_FREQ) == 1) {
	rdx = _en_x + 4; rdy = _en_y + 12; simplecoco_straight_down ();
}
spr_id = en_s [gpit] + ((frame_counter >> 3) & 1);

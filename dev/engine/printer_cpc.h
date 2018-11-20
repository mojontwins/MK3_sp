// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Printer

void draw_tile (void) {
	gp_aux = tsmaps + (_t << 2);
	#ifdef MAP_HEIGHT_12
		if (_y == SCR_Y + 22) {
			cpc_SetTile (_x    , _y    , *gp_aux ++);
			cpc_SetTile (_x + 1, _y    , *gp_aux ++);
		} else if (_y == SCR_Y) {
			gp_aux += 2;
			cpc_SetTile (_x    , _y + 1, *gp_aux ++);
			cpc_SetTile (_x + 1, _y + 1, *gp_aux);
		} else
	#endif			
	{
		cpc_SetTile (_x    , _y    , *gp_aux ++);
		cpc_SetTile (_x + 1, _y    , *gp_aux ++);
		cpc_SetTile (_x    , _y + 1, *gp_aux ++);
		cpc_SetTile (_x + 1, _y + 1, *gp_aux);
	}
}

void draw_tile_upd (void) {
	gp_aux = tsmaps + (_t << 2);
	#ifdef MAP_HEIGHT_12
		if (_y == SCR_Y + 22) {
			cpc_SetTouchTileXY (_x    , _y    , *gp_aux ++);
			cpc_SetTouchTileXY (_x + 1, _y    , *gp_aux ++);
		} else if (_y == SCR_Y) {
			cpc_SetTouchTileXY (_x    , _y + 1, *gp_aux ++);
			cpc_SetTouchTileXY (_x + 1, _y + 1, *gp_aux);
		} else
	#endif	
	{
		cpc_SetTouchTileXY (_x    , _y    , *gp_aux ++);
		cpc_SetTouchTileXY (_x + 1, _y    , *gp_aux ++);
		cpc_SetTouchTileXY (_x    , _y + 1, *gp_aux ++);
		cpc_SetTouchTileXY (_x + 1, _y + 1, *gp_aux);
	}
}

void all_sprites_out (void) {
	gpit = SW_SPRITES_ALL; while (gpit-- > rda) { if (spr_on [gpit]) SPRITE_OUT (gpit); }
}

void blackout (void) {

}

void unpack_scr (unsigned char res) {
	librarian_get_resource (res, (unsigned char *) (BASE_SUPERBUFF));
}

void cpc_clear_rect (unsigned char which) {
	if (which) {
		_y = 20; while (_y --) {
			_x = 30; while (_x --) {
				cpc_SetTile (SCR_X + _x, SCR_Y + _y, 0);
			}
		}
	} else {
		gpint = 768; while (gpint --) {
			nametable [gpint] = 0;
		}
	}
}

void cpc_screen_update (void) {

	// Custom handler for this game. 
	// Please rewrite as fit for new games.

	// HW sprite #1 is a character, which is always aligned & behaving
	cpc_PutSpTileMap8x24 ((int) (&sp_sw [1]));

	// Remaining:
	for (gpit = 2; gpit < 2+SW_SPRITES_16x16; gpit ++) {
		if (sp_sw [gpit].cy > 176) sp_sw [gpit].cy = 176;
		cpc_PutSpTileMap8x16 ((int) (&sp_sw [gpit]));
	}

	for (gpit = 2+SW_SPRITES_16x16; gpit < SW_SPRITES_ALL; gpit ++)
		cpc_PutSpTileMap4x8 ((int) (&sp_sw [gpit]));

	// HW sprite #0 is the player. Rendering it last renders it on top
	/*
	if (sp_sw [0].cy > 167) {
		//sp_sw [0].cy += 8; sp_sw [0].sp0 += 32;
		cpc_PutSpTileMap8x16 ((int) (&sp_sw [0]));
		if (sp_sw [0].cy > 176) sp_sw [0].cy = 176;
		rda = 1;
	} else {
		cpc_PutSpTileMap8x24 ((int) (&sp_sw [0]));
		rda = 0;
	}
	*/
	//if (sp_sw [0].cy > 168) sp_sw [0].cy = 168;
	cpc_PutSpTileMap8x24 ((int) (&sp_sw [0]));

	cpc_UpdScr ();

	cpc_PutTrSp8x24TileMap2b ((int) (&sp_sw [1])); 

	for (gpit = 2; gpit < 2+SW_SPRITES_16x16; gpit ++) 
		cpc_PutTrSp8x16TileMap2b ((int) (&sp_sw [gpit]));

	for (gpit = 2+SW_SPRITES_16x16; gpit < SW_SPRITES_ALL; gpit ++)
		cpc_PutTrSp4x8TileMap2b ((int) (&sp_sw [gpit]));

	// Same.
	/*if (rda) cpc_PutTrSp8x16TileMap2b ((int) (&sp_sw [0]));
	else*/ cpc_PutTrSp8x24TileMap2b ((int) (&sp_sw [0])); 

	cpc_ShowTouchedTiles ();
	cpc_ResetTouchedTiles ();
}

void cpc_show_updated (void) {
	cpc_UpdScr ();
	cpc_ShowTouchedTiles ();
	cpc_ResetTouchedTiles ();
}

void p_s_upd (unsigned char *s) {
	rdxx = _x; rdyy = _y;
	while (*s) {
		rdch = *s ++;
		if (rdch == '/') { rdxx = _x; rdyy ++; } else {
			cpc_SetTouchTileXY (rdxx ++, rdyy, rdch - 32);
		}
	}
}

void unrle_adv (void) {
	nametable [gpint ++] = rdb;
}

void unrle (void) {
	rdc = *gp_aux ++; 	// run code
	gpint = 0; while (gpint < 768) {
		rda = *gp_aux ++;
		if (rda == rdc) {
			rda = *gp_aux ++;
			if (rda == 0) break;
			while (rda --) unrle_adv ();
		} else {
			rdb = rda;
			unrle_adv ();
		}
	}
}

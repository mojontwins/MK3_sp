// MT MK3 OM v0.4 [Cheril in Otro Bosque]
// Copyleft 2017, 2018 by The Mojon Twins

// Texts

extern unsigned char text_pool [0];
#asm
	._text_pool
#ifdef SPECCY
		BINARY "../ports/zx/bin-b/texts.bin"
#endif		
#ifdef CPC
		BINARY "../ports/cpc/bin-b/texts.bin"
#endif

#endasm

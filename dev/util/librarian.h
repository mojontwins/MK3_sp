// MTEZX MK3
// Copyleft 2017 by The Mojon Twins

// librarian

void librarian_get_resource (unsigned char rn, unsigned char *dst) {
	unpack (library [rn], dst);
}


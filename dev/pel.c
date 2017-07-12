struct E {
	char a;
	char b;
} e;

char E_a, E_b;
char r1, r2;

void main (void) {
	e.a = 10; e.b = 20;
	r1 = e.a + e.b;

	E_a = 10; E_b = 20;
	r2 = E_a + E_b;

	while (1) {
	}
}

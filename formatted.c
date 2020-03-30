#include <stdio.h>
#include <stdint.h>

// Use a standard Linear congruental generator for random number.
// It use the Lehmer function with the minstd params.
uint64_t seed = 1;
uint32_t rand() {
	return (seed = ((seed*0x21a7) % 0x7fffffff));
}

// Diacritics in UTF-8 goes from point 0x0300 to 0x036F
// which give us a total of 112 diacritics
// See: https://unicode-table.com/en/blocks/combining-diacritical-marks/
// So we just take any number in this range.
uint32_t rand_diacritique() {
	uint32_t base = 0x0300;
	uint32_t acc = rand() % 112;
	return base+acc;
}

// Print 2 bytes utf-8 code point.
// An explanation of utf8 encoding: https://stackoverflow.com/a/43159143
// I used the LunaSorcery own zalgo implementation to understand it:
// https://github.com/lunasorcery/zalgo
void p2bc(uint32_t code) {
	const char utf8[3] = {
		0xc0 | 			// 110 prefix
		((code >> 6) & 0x1f), 	// we right shift by 6 to only keep the first 5 bits,
					// since the code point is made of 11 bits.
				      	// And we mask with 0x1f to keep the 110 prefix.
		0x80 | 			// 10 prefix
		(code & 0x3f), 		// Mask with 0x3f to keep the 10 prefix.
		0x00 			// EOF for fputs
	};
	fputs(utf8, stdout);
}

int main() {
	int c;
	while((c = getchar()) > 0) {	// Read a char has long has we don't reach EOF.
		putc(c,stdout);
		uint32_t n = rand()%6;  // To decide a number of diacritics to use for this char.
		while(n--) {		// n-- return n, then decrement it
			p2bc(rand_diacritique());
		}
	}
	return 0;
}

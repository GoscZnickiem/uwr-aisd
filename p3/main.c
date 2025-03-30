#include <stdint.h>
#include <stdio.h>

uint32_t validityTable[1 << 15];
uint32_t buff1[1 << 10];
uint32_t buff2[1 << 10];
uint32_t* patternCount = buff1;
uint32_t* patternCountBuffer = buff2;

void readInvalidPattern() {
	getchar();
	uint32_t ul = getchar() == 'x';
	uint32_t u = getchar() == 'x';
	uint32_t ur = getchar() == 'x';
	getchar();
	uint32_t ml = getchar() == 'x';
	uint32_t m = getchar() == 'x';
	uint32_t mr = getchar() == 'x';
	getchar();
	uint32_t ll = getchar() == 'x';
	uint32_t l = getchar() == 'x';
	uint32_t lr = getchar() == 'x';

	uint32_t left = ul | (ml << 1) | (ll << 2);
	uint32_t mid = u | (m << 1) | (l << 2);
	uint32_t right = ur | (mr << 1) | (lr << 2);

	uint32_t index = right | (mid << 5) | (left << 10);

	for(unsigned c = 0; c < 4; ++c)
		for(unsigned b = 0; b < 4; ++b)
			for(unsigned a = 0; a < 4; ++a)
				validityTable[index + (a << 3) + (b << 8) + (c << 13)] = 0;

	for(unsigned d = 0; d < 2; ++d)
		for(unsigned c = 0; c < 4; ++c)
			for(unsigned b = 0; b < 4; ++b)
				for(unsigned a = 0; a < 2; ++a)
					validityTable[(index << 1) + a + (b << 4) + (c << 9) + (d << 14)] = 0;

	for(unsigned c = 0; c < 4; ++c)
		for(unsigned b = 0; b < 4; ++b)
			for(unsigned a = 0; a < 4; ++a)
				validityTable[(index << 2) + a + (b << 5) + (c << 10)] = 0;
}

int main() {
	for(unsigned i = 0; i < 1 << 10; ++i)
		patternCount[i] = 1;
	for(unsigned i = 0; i < 1 << 15; ++i)
		validityTable[i] = UINT32_MAX;

	uint32_t n, p, m;
	scanf("%u %u %u", &n, &p, &m);

	for(unsigned i = 0; i < p; ++i) {
		readInvalidPattern();
	}

	for(unsigned length = 3; length <= n; ++length) {
		for(unsigned i = 0; i < 1 << 10; ++i) {
			patternCountBuffer[i] = 0;
			for(unsigned j = 0; j < 1 << 5; ++j) {
				patternCountBuffer[i] += validityTable[(i << 5) + j] & patternCount[(i << 5 & 0x3E0) + j];
			}
			patternCountBuffer[i] %= m;
		}
		uint32_t* tmp = patternCount;
		patternCount = patternCountBuffer;
		patternCountBuffer = tmp;
	}

	uint32_t res = 0;
	for(unsigned i = 0; i < 1 << 10; ++i)
		res += patternCount[i];

	printf("%u\n", res % m);
}

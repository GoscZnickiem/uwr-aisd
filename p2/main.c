#include <stdint.h>
#include <stdio.h>

typedef struct {
	uint32_t list;
	uint32_t index;
} Elem;

uint32_t M, K;
uint32_t n = 1;
Elem heap[3000];
uint64_t lastPrinted = 0;

#define VAL(i) ((uint64_t)heap[i].list * (uint64_t)heap[i].index)
#define SWAP(i, j) { Elem tmp = heap[i]; heap[i] = heap[j]; heap[j] = tmp; }

void moveDown(uint32_t i) {
	uint32_t k = i;
	uint32_t j;
	do {
		j = k;
		if(2 * j <= n && VAL(2*j)   > VAL(k)) k = 2 * j;
		if(2 * j < n  && VAL(2*j+1) > VAL(k)) k = 2 * j + 1;
		SWAP(j, k);
	} while(j != k);
}

void moveUp(uint32_t i) {
	uint32_t k = i;
	uint32_t j;
	do {
		j = k;
		if(j > 1 && VAL(j >> 1) < VAL(k)) k = j >> 1;
		SWAP(j, k);
	} while(j != k);
}

void push(uint32_t list) {
	n++;
	heap[n].list = list;
	heap[n].index = list;
	moveUp(n);
}

inline void popAndPushNext() {
	uint64_t v = VAL(1);
	if(v != lastPrinted) {
		printf("%zu\n", v);
		lastPrinted = v;
		K--;
	} 
	uint32_t index = --heap[1].index;
	moveDown(1);
	if(M - index >= n) push(index);
}

int main(void) {
	scanf("%u %u", &M, &K);

	heap[1].list = M; 
	heap[1].index = M; 

	setvbuf(stdout, NULL, _IOFBF, 64);
	while(K > 0) popAndPushNext();

	return 0;
}

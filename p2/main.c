#include <stdint.h>
#include <stdio.h>
#ifndef SPRAWDZACZKA
#include <time.h>
#endif

typedef struct {
	uint32_t list;
	uint32_t index;
} Elem;

static uint32_t M, K;
static uint32_t n;
static Elem* heap;

#define VAL(i) ((uint64_t)heap[i].list * (uint64_t)(heap[i].list - heap[i].index))
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
	heap[n].index = 0;
	moveUp(n);
}

void popAndPushNext() {
	static uint64_t last = 0;
	uint64_t v = VAL(1);
	if(v != last) {
		printf("%zu\n", v);
		last = v;
		K--;
	}
	uint32_t index = ++heap[1].index;
	moveDown(1);
	if(index >= n) push(M - n);
}

int main(void) {
#ifndef SPRAWDZACZKA
	clock_t start, end;
	double cpu_time_used;
	start = clock();
#endif
	scanf("%u %u", &M, &K);

	Elem heapi[(M < K ? M : K) + 1];
	heap = heapi;

	heap[1].list = M; 
	heap[1].index = 0; 
	n = 1;

	setvbuf(stdout, NULL, _IOFBF, 1<<20);
	while(K > 0) popAndPushNext();

#ifndef SPRAWDZACZKA
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time taken: %f seconds\n", cpu_time_used);
#endif

	return 0;
}

#include <stdint.h>
#include <stdio.h>

typedef uint32_t uint;

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

typedef struct {
	uint list;
	uint index;
} Elem;

static uint n;
static Elem* heap;

#define VAL(i) ((uint64_t)heap[i].list * (uint64_t)(heap[i].list - heap[i].index))
#define SWAP(i, j) { Elem tmp = heap[i]; heap[i] = heap[j]; heap[j] = tmp; }

void moveDown(uint i) {
	uint k = i;
	uint j;
	do {
		j = k;
		if(2 * j <= n && VAL(2*j)   < VAL(k)) k = 2 * j;
		if(2 * j < n  && VAL(2*j+1) < VAL(k)) k = 2 * j + 1;
		SWAP(j, k);
	} while(j == k);
}

void moveUp(uint i) {
	uint k = i;
	uint j;
	do {
		j = k;
		if(j > 1 && VAL(j >> 1) > VAL(k)) k = j >> 1;
		SWAP(j, k);
	} while(j == k);
}

void popAndPushNext() {
	heap[1].index--;
	moveDown(1);
}

void push(uint list) {
	heap[n].list = list;
	heap[n].index = 0;
	n++;
	moveUp(n - 1);
}

int main(void) {
	uint64_t M, k;
	scanf("%zu %zu", &M, &k);

	Elem heapi[MIN(M, k) + 1];
	heap = heapi;

	return 0;
}

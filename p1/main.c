#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#ifndef SPRAWDZACZKA
#include <time.h>
#endif

uint64_t* graph;
uint32_t dest[10001] = {0};

int DST(uint32_t entry, uint32_t depth) {
	if(!entry && depth) {
		printf("%u\n", depth);
		return 1;
	}
	if(!dest[entry]) return 0;

	uint32_t d = dest[entry];
	dest[entry] = 0;
	uint32_t i = d;
	do {
		if(DST(graph[i] & 0x3FFF, depth + 1)) {
			printf("%lu %lu %u\n", graph[i] & 0x3FFF, (graph[i] >> 14) & 0x3FFF, entry);
			return 1;
		}
		i = graph[i] >> 46;
	} while (i != d);

	return 0;
}

int main(void) {
#ifndef SPRAWDZACZKA
	clock_t start, end;
	double cpu_time_used;
	start = clock();
#endif

	size_t n = 0;
	scanf("%zu", &n);

	uint64_t graphi[n+1];
	graph = graphi;

	for (size_t i = 1; i <= n; i++) {
		uint64_t l, m, r;
		scanf("%lu %lu %lu", &l, &m, &r);
		uint64_t prev = dest[r] ? (graph[dest[r]] >> 28) & 0x3FFFF : i;
		dest[r] = dest[r] ? dest[r] : i;
		uint64_t next = dest[r];
		graph[prev] = (graph[prev] & 0x00003FFFFFFFFFFF) | (i << 46);
		graph[next] = (graph[next] & 0xFFFFC0000FFFFFFF) | (i << 28);
		graph[i] = l | (m << 14) | (prev << 28) | (next << 46);
	}

	if(!DST(0, 0)) printf("BRAK\n");

#ifndef SPRAWDZACZKA
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
#endif

	return 0;
}

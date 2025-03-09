#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t* graph;
static uint32_t outEdges[10001] = {0};

int DFS(uint32_t vert, uint32_t depth) {
	if(!vert && depth) {
		printf("%u\n", depth);
		return 1;
	}

	uint32_t i = outEdges[vert];
	outEdges[vert] = 0;
	while (i != 0) {
		if(DFS(graph[i] & 0xFFFF, depth + 1)) {
			printf("%lu %lu %u\n", graph[i] & 0xFFFF, (graph[i] >> 16) & 0xFFFF, vert);
			return 1;
		}
		i = graph[i] >> 32;
	}

	return 0;
}

int main(void) {
	size_t n = 0;
	scanf("%zu\n", &n);

	uint64_t graphi[n+1];
	graph = graphi;

	char line[64];
	for (size_t i = 1; i <= n; i++) {
		fgets(line, 64, stdin);
		char* ptr = line;
		uint64_t l = strtoul(ptr, &ptr, 10);
		uint64_t m = strtoul(ptr, &ptr, 10);
		uint64_t r = strtoul(ptr, &ptr, 10);
		uint64_t next = outEdges[r];
		graph[i] = l | (m << 16) | (next << 32);
		outEdges[r] = i;
	}

	if(!DFS(0, 0)) printf("BRAK\n");

	return 0;
}

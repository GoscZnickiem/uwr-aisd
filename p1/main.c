#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#ifndef SPRAWDZACZKA
#include <time.h>
#endif

static uint64_t* graph;
static uint32_t outEdges[10001] = {0};

static char* buffer;
static size_t pos = 0;

uint64_t readInt() {
	uint64_t num = 0;
	while (buffer[pos] < '0' || buffer[pos] > '9') pos++;
	while (buffer[pos] >= '0' && buffer[pos] <= '9') {
		num = num * 10 + (buffer[pos] - '0');
		pos++;
	}
	return num;
}

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

#ifndef SPRAWDZACZKA
	clock_t start, end;
	double cpu_time_used;
	start = clock();
#endif

	struct stat sb;
	fstat(STDIN_FILENO, &sb);
	buffer = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    if (buffer == MAP_FAILED) {
        return 1;
    }

	size_t n = readInt();

	uint64_t graphi[n+1];
	graph = graphi;

	for (size_t i = 1; i <= n; i++) {
		uint64_t l = readInt();
		uint64_t m = readInt();
		uint64_t r = readInt();
		uint64_t next = outEdges[r];
		graph[i] = l | (m << 16) | (next << 32);
		outEdges[r] = i;
	}

	if(!DFS(0, 0)) printf("BRAK\n");

#ifndef SPRAWDZACZKA
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time taken: %f seconds\n", cpu_time_used);
#endif

	return 0;
}

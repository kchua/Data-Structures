#include "DisjointSets.h"

using namespace std;

DisjointSets::DisjointSets(int N) {
	nodes = vector<int>(N);
	weights = vector<int>(N);
	for (int i = 0; i < N; i++) {
		nodes[i] = i;
		weights[i] = 1;
	}
	size = N;
}

int main() {
	// Example usage
	DisjointSets *sets = new DisjointSets(5);         // Creates a Disjoint Sets object
	delete sets;
	return 0;
}
#include <iostream>
#include "DisjointSets.h"

using namespace std;

typedef DisjointSets DS;

/* Constructs a Disjoint Sets object with N nodes.*/
DS::DisjointSets(int N) {
	parents = vector<int>(N);
	weights = vector<int>(N);
	for (int i = 0; i < N; i++) {
		parents[i] = i;
		weights[i] = 1;
	}
	size = N;
}

/* Finds the parent of Node A.*/
int DS::find(int a) {
	int curr = a;
	while (curr != parents[curr]) {
		curr = parents[curr];
	}
	return curr;
}

/* Connects Node A and Node B.*/
void DS::connect(int a, int b) {
	int aParent = find(a);
	int bParent = find(b);
	if (weights[a] > weights[b]) {
		parents[b] = a;
		weights[a] += weights[b];
	} else {
		parents[a] = b;
		weights[b] += weights[a];
	}
}

/* Checks if Node A and Node B are connected to each other.*/
bool DS::isConnected(int a, int b) {
	return find(a) == find(b);
}

int main() {
	// Example usage
	DisjointSets *sets = new DisjointSets(5);         // Creates a Disjoint Sets object
	sets->connect(1, 2);                              // Connects Node 1 and 2
    cout << sets->isConnected(1, 2) << "\n";          // Checks for connection between Node 1 and 2 - should return True
	cout << sets->isConnected(2, 3) << "\n";          // Checks for connections between Node 2 and 3 - should return False
	sets->connect(2, 3);
	cout << sets->isConnected(2, 3) << "\n";          // should return True now
	cout << sets->isConnected(1, 3) << "\n";          // should return True now
	cout << sets->isConnected(1, 2) << "\n";          // should still return True
	delete sets;
	return 0;
}
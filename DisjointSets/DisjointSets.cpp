#include <iostream>
#include <ctime>
#include "DisjointSets.h"

using namespace std;
typedef DisjointSets DS;

// Public member functions
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
	int root = a;
	while (root != parents[root]) {
		root = parents[root];
	}
	int curr = a;
	int next = parents[a];
	while (next != root) {
		parents[curr] = root;
		curr = next;
		next = parents[curr];
	}
	return root;
}

/* Checks if Node A and Node B are connected to each other.*/
bool DS::isConnected(int a, int b) {
	return find(a) == find(b);
}


// Private helper functions
/* Connects Node A and Node B.*/
void DS::connect(int a, int b) {
	int aParent = find(a);
	int bParent = find(b);
	if (weights[aParent] > weights[bParent]) {
		parents[bParent] = aParent;
		weights[aParent] += weights[bParent];
	} else {
		parents[aParent] = bParent;
		weights[bParent] += weights[aParent];
	}
}


// example usage
int main() {
	DisjointSets* sets = new DisjointSets(5);         // Creates a Disjoint Sets object

	sets->connect(1, 2);                              // Connects Node 1 and 2

	cout << sets->isConnected(1, 2) << "\n";          // Checks for connection between Node 1 and 2 - should return true
	cout << sets->isConnected(2, 3) << "\n";          // Checks for connections between Node 2 and 3 - should return false

	sets->connect(2, 3);

	cout << sets->isConnected(2, 3) << "\n";          // should return true now
	cout << sets->isConnected(1, 3) << "\n";          // should return true now
	cout << sets->isConnected(1, 2) << "\n";          // should still return true


	DisjointSets& sets2 = DisjointSets(5);            // Path compression check

	sets2.connect(2, 3);
	sets2.connect(1, 2);
	sets2.connect(1, 3);

	delete sets;


	cout << "\n\nStarting performance test. Performing 20 million union operations...\n";   // Performance test
	std::clock_t start;
	double duration;

	start = std::clock();
	DisjointSets sets3 = DisjointSets(20000000);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Construction completed in " << duration << " seconds.\n";
	start = std::clock();

	for (int i = 0; i < 2000000 - 100; i++) {
		sets3.connect(i, i + 100);
	}

	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	cout << "Operations completed in " << duration << " seconds.";

	return 0;
}
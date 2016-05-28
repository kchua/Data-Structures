#include "HashMap.h"
#include <iostream>

using namespace std;

template<class Hashable, class Value, class HashFunction>
HashMap<Hashable, Value, HashFunction>::HashMap() {
	numItems = 0;
	keys = new Hashable*[8];
	vals = new Value*[8];
	for (int i = 0; i < 8; i++) {
		*(keys + i) = nullptr;
		*(vals + i) = nullptr;
		numItems++;
	}
	numBuckets = 8;
}

template<class Hashable, class Value, class HashFunction>
HashMap<Hashable, Value, HashFunction>::~HashMap() {
	for (unsigned int i = 0; i < numBuckets; i++) {
		if (*(vals + i) != nullptr) {                             
			delete [] *(vals + i);
		}
	}
	delete[] keys;
	delete[] vals;
}

template<class Hashable, class Value, class HashFunction>
bool HashMap<Hashable, Value, HashFunction>::isEmpty() {
	return numItems == 0;
}

template<class Hashable, class Value, class HashFunction>
int HashMap<Hashable, Value, HashFunction>::size() {
	return numItems;
}

template<class Hashable, class Value, class HashFunction>
Value& HashMap<Hashable, Value, HashFunction>::operator[](Hashable key) {
	int probeStart = HashFunction()(key) % numBuckets;
	int curr = 0;
	while (*(keys + probeStart + curr) != nullptr && **(keys + probeStart + curr) != key) {
		curr++;								// TODO: replace with an increment function that loops around.
	}
	if (*(keys + probeStart + curr) == nullptr) {
		*(vals + probeStart + curr) = new Value[1];
		*(keys + probeStart + curr) = &key;
	}
	return **(vals + probeStart + curr);
}


int main() {
	HashMap<int, int> a = HashMap<int, int>();
	a[1] = 2;
	cout << a[1];
	a[1] = 3;
	std::cout << a[1];
	cout << a[2];
}
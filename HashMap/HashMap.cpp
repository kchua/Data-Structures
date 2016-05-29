#include "HashMap.h"
#include <iostream>

using namespace std;

template<class Hashable, class Value, class HashFunction>
HashMap<Hashable, Value, HashFunction>::HashMap() {
	numItems = 0;
	numBuckets = 8;
	resetBuckets(numBuckets);
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
		increment(curr);
	}
	if (*(keys + probeStart + curr) == nullptr) {
		*(vals + probeStart + curr) = new Value[1];
		*(keys + probeStart + curr) = &key;
		expand();
	}
	return **(vals + probeStart + curr);
}

// Private Helper Methods

/* Increments the index in such a way that it loops back to zero once it equals
   the number of buckets */
template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::increment(int& index) {
	index = 2(index + 1) % numBuckets;
}

/* Resets all arrays so that there are newNumBuckets buckets. */
template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::resetBuckets(int newNumBuckets) {
	keys = new Hashable*[newNumBuckets];
	vals = new Value*[newNumBuckets];
	for (int i = 0; i < newNumBuckets; i++) {
		*(keys + i) = nullptr;
		*(vals + i) = nullptr;
	}

}

/* Expands the number of buckets to twice the current size if the load factor is
   greater than 1/2. */
template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::expand() {
	if (numItems >= numBuckets / 2) {
		numBuckets *= 2;
		Hashable** oldKeys = keys;
		Value** oldVals = vals;
		numItems = 0;
		resetBuckets(newNumBuckets);
		for (int i = 0; i < numBuckets / 2; i++) {
			if (*(oldKeys + i) != nullptr) {
				put(**(oldKeys + i), **(oldVals + i));
			}
		}
	}
}

int main() {
	HashMap<int, int> a = HashMap<int, int>();
	a[1] = 2;
	cout << a[1];
	a[1] = 3;
	std::cout << a[1];
	cout << a[2];
}
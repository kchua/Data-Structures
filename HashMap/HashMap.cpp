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
HashMap<Hashable, Value, HashFunction>::HashMap(const HashMap& other) {
	numItems = other.numItems;
	numBuckets = other.numBuckets;
	resetBuckets(numBuckets);
	for (int i = 0; i < numBuckets; i++) {
		if (*(other.keys + i) != nullptr) {
			*(keys + i) = new Hashable[1];
			*(vals + i) = new Value[1];
			**(keys + i) = **(other.keys + i);
			**(vals + i) = **(other.vals + i);
		}
	}
}

template<class Hashable, class Value, class HashFunction>
HashMap<Hashable, Value, HashFunction>::~HashMap() {
	arrayDelete(keys, vals, numBuckets);
}

template<class Hashable, class Value, class HashFunction>
HashMap<Hashable, Value, HashFunction>& HashMap<Hashable, Value, HashFunction>::operator=(HashMap other) {
	other.swap(*this);
	return this;
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
	int probe = HashFunction()(key) % numBuckets;
	while (*(keys + probe) != nullptr && **(keys + probe) != key) {
		probe = (probe + 1) % numBuckets;
	}
	if (*(keys + probe) == nullptr) {
		*(vals + probe) = new Value[1];
		*(keys + probe) = new Hashable[1];
		**(keys + probe) = key;
		numItems++;
		this->expand();
		return (*this)[key];
	}
	else {
		return **(vals + probe);
	}
}

template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::put(Hashable key, Value val) {
	(*this)[key] = val;
}

// Private Helper Methods

/* Swaps the members of two HashMaps, used for the copy-swap idiom. */
template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::swap(HashMap<Hashable, Value, HashFunction> other) {
	using std::swap;

	swap(this->keys, other.keys);
	swap(this->vals, other.vals);
	swap(this->numBuckets, other.numBuckets);
	swap(this->numItems, other.numItems);
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
		resetBuckets(numBuckets);
		for (int i = 0; i < numBuckets / 2; i++) {
			if (*(oldKeys + i) != nullptr) {
				put(**(oldKeys + i), **(oldVals + i));
			}
		}
		arrayDelete(oldKeys, oldVals, numBuckets / 2);
	}
}

template<class Hashable, class Value, class HashFunction>
void HashMap<Hashable, Value, HashFunction>::arrayDelete(Hashable** k, Value** v, int size) {
	for (unsigned int i = 0; i < size; i++) {
		if (*(k + i) != nullptr) {
			delete[] * (k + i);
			delete[] * (v + i);
		}
	}
	delete[] k;
	delete[] v;
}

int main() {
	HashMap<int, int> a = HashMap<int, int>();
	a[1] = 2;
	cout << a[1]; cout << endl;
	a[1] = 3;
	cout << a[1]; cout << "\n";
	cout << a[2]; cout << "\n";
	HashMap<int, int> b = a;
	b[1] = 2;
	cout << a[1]; cout << "\n";
	cout << b[1]; cout << "\n";

	a[1] = 1;
	cout << a[1]; cout << "\n";
	a[2] = 2;
	cout << a[2]; cout << "\n";
	a[3] = 3;
	cout << a[3]; cout << "\n";
	a[4] = 4;
	cout << a[1]; cout << "\n";
	cout << a[2]; cout << "\n";
	cout << a[3]; cout << "\n";
	cout << a[4]; cout << "\n";
}
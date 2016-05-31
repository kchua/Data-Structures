#include "HashMap.h"
#include <iostream>

using namespace std;

template<class Hashable, class Value, class hashFunction>
HashMap<Hashable, Value, hashFunction>::HashMap() {
	numItems = 0;
	numBuckets = 8;
	resetBuckets(numBuckets);
}

template<class Hashable, class Value, class hashFunction>
HashMap<Hashable, Value, hashFunction>::HashMap(const HashMap& other) {
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

template<class Hashable, class Value, class hashFunction>
HashMap<Hashable, Value, hashFunction>::~HashMap() {
	arrayDelete(keys, vals, numBuckets);
}

template<class Hashable, class Value, class hashFunction>
HashMap<Hashable, Value, hashFunction>& HashMap<Hashable, Value, hashFunction>::operator=(HashMap other) {
	other.swap(*this);
	return this;
}

template<class Hashable, class Value, class hashFunction>
bool HashMap<Hashable, Value, hashFunction>::isEmpty() {
	return numItems == 0;
}

template<class Hashable, class Value, class hashFunction>
int HashMap<Hashable, Value, hashFunction>::size() {
	return numItems;
}

template<class Hashable, class Value, class hashFunction>
Value& HashMap<Hashable, Value, hashFunction>::operator[](Hashable key) {
	int hash = hashFunction()(key);
	int probe = hashFunction()(key) % numBuckets;
	while (*(keys + probe) != nullptr && **(keys + probe) != key) {
		probe = (probe + 1) % numBuckets;
	}
	if (*(keys + probe) == nullptr) {
		*(vals + probe) = new Value[1];
		*(keys + probe) = new Hashable[1];
		**(keys + probe) = key;
		**(vals + probe) = Value();
		numItems++;
		if (numItems >= numBuckets / 2) {
			expand();
			return (*this)[key];
		}
	}
	return **(vals + probe);
}

template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::put(Hashable key, Value val) {
	(*this)[key] = val;
}

template<class Hashable, class Value, class hashFunction>
Value& HashMap<Hashable, Value, hashFunction>::get(const Hashable& key) {
	return (*this)[key];
}

template<class Hashable, class Value, class hashFunction>
bool HashMap<Hashable, Value, hashFunction>::contains(const Hashable & key) {
	int probe = hashFunction()(key) % numBuckets;
	while (*(keys + probe) != nullptr && **(keys + probe) != key) {
		probe = (probe + 1) % numBuckets;
	}
	if (*(keys + probe) != nullptr) {
		return true;
	}
	return false;
}

template<class Hashable, class Value, class hashFunction>
Value HashMap<Hashable, Value, hashFunction>::remove(Hashable key)
{
	int probe = hashFunction()(key) % numBuckets;
	while (*(keys + probe) != nullptr && **(keys + probe) != key) {
		probe = (probe + 1) % numBuckets;
	}
	if (*(keys + probe) != nullptr) {
		Value temp = **(vals + probe);
		int curr = (probe + 1) % numBuckets;
		delete[] * (keys + probe);
		delete[] * (vals + probe);
		*(keys + probe) = nullptr;
		*(vals + probe) = nullptr;
		while (*(keys + curr) != nullptr) {
			Hashable tKey = **(keys + curr);
			Value tVal = **(vals + curr);
			delete[] * (keys + curr);
			delete[] * (vals + curr);
			*(keys + curr) = nullptr;
			*(vals + curr) = nullptr;
			(*this)[tKey] = tVal;
			curr = (curr + 1) % numBuckets;
		}
		numItems--;
		if (numBuckets > 8 && numItems < numBuckets / 8) {
			shrink();
		}
		return temp;
	}
	return Value();
}

// Private Helper Methods

/* Swaps the members of two HashMaps, used for the copy-swap idiom. */
template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::swap(HashMap<Hashable, Value, hashFunction> other) {
	using std::swap;

	swap(this->keys, other.keys);
	swap(this->vals, other.vals);
	swap(this->numBuckets, other.numBuckets);
	swap(this->numItems, other.numItems);
}

/* Resets all arrays so that there are newNumBuckets buckets. */
template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::resetBuckets(int newNumBuckets) {
	keys = new Hashable*[newNumBuckets];
	vals = new Value*[newNumBuckets];
	for (int i = 0; i < newNumBuckets; i++) {
		*(keys + i) = nullptr;
		*(vals + i) = nullptr;
	}
}

/* Expands the number of buckets to twice the current size */
template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::expand() {
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

template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::shrink() {
	numBuckets /= 2;
	Hashable** oldKeys = keys;
	Value** oldVals = vals;
	numItems = 0;
	resetBuckets(numBuckets);
	for (int i = 0; i < numBuckets * 2; i++) {
		if (*(oldKeys + i) != nullptr) {
			put(**(oldKeys + i), **(oldVals + i));
		}
	}
	arrayDelete(oldKeys, oldVals, numBuckets * 2);
}

template<class Hashable, class Value, class hashFunction>
void HashMap<Hashable, Value, hashFunction>::arrayDelete(Hashable** k, Value** v, int size) {
	for (unsigned int i = 0; i < size; i++) {
		if (*(k + i) != nullptr) {
			delete[] *(k + i);
			delete[] *(v + i);
		}
	}
	delete[] k;
	delete[] v;
}

/*
int main() {
	HashMap<int, int>* a = new HashMap<int, int>();
	for (int i = 0; i < 10000; i++) {
		(*a)[i];
	}
	int violationCount = 0;
	for (int j = 0; j < 10000; j++) {
		(*a).remove(j);
		for (int i = 0; i < j; i++) {
			if (!(*a).contains(i)) {
				violationCount++;
			}
		}
		if ((*a).contains(j)) {
			violationCount++;
		}
		for (int i = j + 1; i < 10000; i++) {
			if (!(*a).contains(i)) {
				violationCount++;
			}
		}
		(*a)[j];
	}
	delete a;
	cout << violationCount << " violation(s)";
}
*/
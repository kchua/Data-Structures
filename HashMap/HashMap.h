#ifndef HASHMAP_H
#define HASHMAP_H

#include<functional>

template<class Hashable, class Value, class hashFunction = std::hash<Hashable>>
class HashMap {
public:
	HashMap();
	~HashMap();
	bool isEmpty();
	int size();
	Value& operator[] (Hashable key);
	void put(Hashable key, Hashable value);
	Value& get(const& Hashable& key);
	bool contains(const Hashable& key);
private:
	unsigned int numItems;
	unsigned int numBuckets;
	Hashable** keys;
	Value** vals;
};

#endif
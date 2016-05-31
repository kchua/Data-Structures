#ifndef HASHMAP_H
#define HASHMAP_H

#include<functional>

template<class Hashable, class Value, class hashFunction = std::hash<Hashable>>
class HashMap {
public:
	HashMap();
	HashMap(const HashMap& other);
	~HashMap();
	HashMap& operator=(HashMap other);
	bool isEmpty();
	int size();
	Value& operator[] (Hashable key);
	void put(Hashable key, Value val);
	Value& get(const Hashable& key);
	bool contains(const Hashable& key);
	Value remove(Hashable key);
private:
	unsigned int numItems;
	unsigned int numBuckets;
	Hashable** keys;
	Value** vals;
	
	void swap(HashMap other);
	void resetBuckets(int newNumBuckets);
	void expand();
	void shrink();
	void arrayDelete(Hashable** k, Value** v, int size);
};

#endif
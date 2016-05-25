#ifndef LLRBTMAP_H
#define	LLRBTMAP_H

#include "LLRBT.h"

template<typename Key, typename Value>
class LLRBTMap 
{
	friend class Container;
public:
	LLRBTMap();
	~LLRBTMap();
	bool isEmpty();
	int size();
	void put(Key k, Value v);
	Value get(Key k);
	bool contains(Key k);
	void clear();
private:
	struct Container {
		Key k;
		Value v;
		friend bool operator==(const Container &c1, const Container &c2);
		friend bool operator<(const Container &c1, const Container &c2);
		friend bool operator>(const Container &c1, const Container &c2);
	};
	LLRBT<Container> map;
};

#endif
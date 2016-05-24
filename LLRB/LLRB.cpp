#include <iostream>
#include "LLRB.h"

using namespace std;

template<typename Comparable>
struct LLRB<Comparable>::Node 
{
	Comparable item;
	Node lChild;
	Node rChild;
};

template<typename Comparable>
LLRB<Comparable>::LLRB() {
	root = nullptr;
	numItems = 0;
}

template<typename Comparable>
LLRB<Comparable>::~LLRB() {}

template<typename Comparable>
bool LLRB<Comparable>::isEmpty() {
	return root == NULL;
}

template<typename Comparable>
int LLRB<Comparable>::size() {
	return numItems;
}

int main() {
	LLRB<int> test = LLRB<int>();
	cout << test.isEmpty();
	cout << test.size();
	return 0;
}
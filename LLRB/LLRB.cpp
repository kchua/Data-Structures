#include "LLRB.h"

using namespace std;

template<typename Comparable>
LLRB<Comparable>::struct Node 
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

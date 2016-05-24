#include <iostream>
#include "LLRBT.h"

using namespace std;

template<typename Comparable>
LLRBT<Comparable>::Node::Node(Comparable item, Node* lChild, Node* rChild) {
	this->item = item;
	this->lChild = lChild;
	this->rChild = rChild;
}

template<typename Comparable>
LLRBT<Comparable>::Node::~Node() {
	if (lChild == NULL) { delete lChild; }
	if (rChild == NULL) { delete rChild; }
}

template<typename Comparable>
typename LLRBT<Comparable>::Node* LLRBT<Comparable>::Node::insert(Comparable item, Node* nd) {
	if (nd == NULL) {
		return new Node(item, nullptr, nullptr);
	} else {
		if (item > nd->item) {
			nd->rChild = insert(item, nd->rChild);
		}
		else {
			nd->lChild = insert(item, nd->lChild);
		}
		return nd;
	}
}

template<typename Comparable>
bool LLRBT<Comparable>::Node::contains(Comparable item, Node* nd) {
	if (nd == NULL) {
		return false;
	}
	else if (nd->item == item) {
		return true;
	}
	else {
		if (item > nd->item) {
			return contains(item, nd->rChild);
		}
		else {
			return contains(item, nd->lChild);
		}
	}
}

template<typename Comparable>
LLRBT<Comparable>::LLRBT() {
	root = nullptr;
	numItems = 0;
}

template<typename Comparable>
LLRBT<Comparable>::~LLRBT() {}

template<typename Comparable>
bool LLRBT<Comparable>::isEmpty() {
	return root == NULL;
}

template<typename Comparable>
int LLRBT<Comparable>::size() {
	return numItems;
}

template<typename Comparable>
void LLRBT<Comparable>::insert(Comparable item) {
	root = Node::insert(item, root);
	numItems++;
}

template<typename Comparable>
bool LLRBT<Comparable>::contains(Comparable item) {
	return Node::contains(item, root);
}
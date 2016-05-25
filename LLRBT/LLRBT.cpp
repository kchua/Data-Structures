#include <iostream>
#include "LLRBT.h"

using namespace std;

// Node helper class definitions

/* Constructor for the Node class. */
template<typename Comparable>
LLRBT<Comparable>::Node::Node(Comparable item, Node* lChild, Node* rChild) {
	this->item = item;
	this->lChild = lChild;
	this->rChild = rChild;
}

/* Destructor for the Node class. */
template<typename Comparable>
LLRBT<Comparable>::Node::~Node() {
	if (lChild != NULL) { delete lChild; }
	if (rChild != NULL) { delete rChild; }
	lChild = nullptr;
	rChild = nullptr;
}

/* Recursive insertion method. */
template<typename Comparable>
typename LLRBT<Comparable>::Node* LLRBT<Comparable>::Node::insert(Comparable item, Node* nd) {
	if (nd == NULL) {
		return new Node(item, nullptr, nullptr);
	} else {
		if (item > nd->item) {
			nd->rChild = insert(item, nd->rChild);
		} else if (item < nd->item) {
			nd->lChild = insert(item, nd->lChild);
		}
		// Balancing
		if (nd->rChild != NULL && nd->rChild->isRed 
			&& (nd->lChild == NULL || !nd->lChild->isRed)) {
			return leftRotation(nd);
		} else if (nd->lChild != NULL && nd->lChild->isRed 
			&& nd->lChild->lChild != NULL && nd->lChild->lChild->isRed) {
			return flipColors(rightRotation(nd));
		} else if (nd->lChild != NULL && nd->lChild->isRed 
			&& nd->rChild != NULL && nd->rChild->isRed) {
			return flipColors(nd);
		} else {
			return nd;
		}
	}
}

/* Recursive method for checking whether something is contained within the tree. */
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

/* Left rotation operation used in balancing the tree. */
template<typename Comparable>
typename LLRBT<Comparable>::Node* LLRBT<Comparable>::Node::leftRotation(Node* nd) {
	Node* temp = nd->rChild;
	bool tempColor = temp->isRed;
	nd->rChild = temp->lChild;
	temp->lChild = nd;
	temp->isRed = nd->isRed;
	nd->isRed = tempColor;
	return temp;
}

/* Right rotation operation used in balancing the tree. */
template<typename Comparable>
typename LLRBT<Comparable>::Node* LLRBT<Comparable>::Node::rightRotation(Node* nd) {
	Node* temp = nd->lChild;
	bool tempColor = temp->isRed;
	nd->lChild = temp->rChild;
	temp->rChild = nd;
	temp->isRed = nd->isRed;
	nd->isRed = tempColor;
	return temp;
}

/* Color flip, used to balance the tree. */
template<typename Comparable>
typename LLRBT<Comparable>::Node* LLRBT<Comparable>::Node::flipColors(Node* nd) {
	nd->lChild->isRed = false;
	nd->rChild->isRed = false;
	nd->isRed = true;
	return nd;
}

// Left-leaning red-black tree function definitions

template<typename Comparable>
LLRBT<Comparable>::LLRBT() {
	root = nullptr;
	numItems = 0;
}

template<typename Comparable>
LLRBT<Comparable>::~LLRBT() {
	delete root;
	root = nullptr;
}

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
	root->isRed = false;
	numItems++;
}

template<typename Comparable>
bool LLRBT<Comparable>::contains(Comparable item) {
	return Node::contains(item, root);
}
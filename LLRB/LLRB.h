#ifndef LLRB_H
#define LLRB_H

template<typename Comparable>
class LLRB {
	friend class Node;
public:
	LLRB();
	~LLRB();
	bool isEmpty();
	int size();
	void insert(Comparable item);
	bool contains(Comparable item);
	Comparable remove(Comparable item);
private:
	int numItems;
	Node* root;
	struct Node;
	Node insert(Comparable item, Node node);
	Node remove(Comparable item, Node node);
	Node leftRotation(Node node);
	Node rightRotation(Node node);
	Node flipColors(Node node);
};

#endif
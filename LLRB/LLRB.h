#ifndef LLRB_H
#define LLRB_H

template<typename Comparable>
class LLRB {
	friend class Node;
public:
	using valueType = Comparable;
	LLRB();
	~LLRB();
	int size();
	boolean isEmpty();
	void insert(valueType item);
	bool contains(valueType item);
	valueType remove(valueType item);
private:
	int numItems;
	Node* root;
	friend LLRB struct Node;
	Node insert(valueType item, Node node);
	Node remove(valueType item, Node node);
	Node leftRotation(Node node);
	Node rightRotation(Node node);
	Node flipColors(Node node);
};

#endif
#ifndef LLRBT_H
#define LLRBT_H

template<typename Comparable>
class LLRBT {
	friend class Node;
public:
	LLRBT();
	~LLRBT();
	bool isEmpty();
	int size();
	void insert(Comparable item);
	bool contains(Comparable item);
	void clear();
private:
	int numItems;
	struct Node {
		Comparable item;
		Node* lChild;
		Node* rChild;
		bool isRed = true;
		Node(Comparable item, Node* lChild, Node* rChild);
		~Node();
		static Node* insert(Comparable item, Node* nd);
		static bool contains(Comparable item, Node* nd);
		static Node* leftRotation(Node* nd);
		static Node* rightRotation(Node* nd);
		static Node* flipColors(Node* nd);
	};
	Node* root;
};

#endif
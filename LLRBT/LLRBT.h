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
	void insert(const Comparable& item);
	bool contains(const Comparable& item);
	void clear();
private:
	int numItems;
	struct Node {
		Comparable item;
		Node* lChild;
		Node* rChild;
		bool isRed = true;
		Node(const Comparable& item);
		~Node();
		static Node* insert(const Comparable& item, Node* nd);
		static bool contains(const Comparable& item, Node* nd);
		static Node* leftRotation(Node* nd);
		static Node* rightRotation(Node* nd);
		static Node* flipColors(Node* nd);
	};
	Node* root;
};

#endif
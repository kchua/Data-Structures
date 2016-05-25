# Data Structures

As part of my introduction to the C++ language, I decided to implement some of the data structures that
I had learned in my CS class to learn the intricacies of the language.

## Disjoint Sets

The disjoint sets abstract data type allows one to make nodes, establish connectivity between those nodes,
and check connections between those nodes. *Connectivity* in this context is, formally, an equivalence
relation. That is, beyond symmetric and reflexive properties, connectivity is a transitive relation; if
Node A is connected to Node B, and Node B is connected to Node C, then Node A is connected to Node C.

Note, however, that the data structure does not answer the question, "How are two nodes connected to each 
other?" It merely determines whether there *is* a connnection. As a result, there is no way to delete 
connections between nodes once they are made. These limitations result in various optimizations that all 
stem from treating the connections as forming several disjoint sets, the namesake of the data structure.

### Usage

The `DisjointSets` class has the following API:
```cpp
DisjointSets(int N);
void connect(int a, int b);
bool isConnected(int a, int b);
```

1. Construction
    ```cpp
    // Creates a pointer to a new DisjointSets object with 10 nodes
    DisjointSets* sets = new DisjointSets(10);                                            
    ```

2. Making Connections
    ```cpp
    DisjointSets* sets = new DisjointSets(10);
    sets->connect(1, 2);     // connects Node 1 and Node 2 together                                         
    ```

3. Checking for connections
    ```cpp
    DisjointSets* sets = new DisjointSets(5);

	sets->connect(1, 2);

    sets->isConnected(1, 2);    // checks for connection between Node 1 and 2 - should return true
	sets->isConnected(2, 3);    // checks for connections between Node 2 and 3 - should return false

	sets->connect(2, 3);

	sets->isConnected(2, 3);    // should return true now
	sets->isConnected(1, 3);    // should return true now
	sets->isConnected(1, 2);    // should still return true
    ```

## Left-Leaning Red-Black Trees (Set/Map)

Binary search trees are decent data structures to represent sets of ordered items, since
operations on the set can be usually done in logarithmic time. However, such behavior
is dependent on the order in which items are inserted. Unfortunately, in the worst case,
operations can run in quadratic time if items are inserted in order.

Therefore, in an attempt to ensure logarithmic time performance, red-black tree data 
structures were invented. This is done by making a variant of the binary search tree
with colored links which, with the help of tree rotation operations used to restore
invariants, is self-balancing.

This specific variant is *left-leaning* since red links are always on the left, simplifying
implementation.

### Usage

The set version of the LLRB tree, `LLRBT<Comparable>`, has the following API:
```cpp
LLRBT();
~LLRBT();
bool isEmpty();
int size();
void insert(Comparable item);
bool contains(Comparable item);
void clear();
```

The map version of the tree, `LLRBTMap<Key, Value>`, has the following API:
```cpp
LLRBTMap();
~LLRBTMap();
bool isEmpty();
int size();
void put(Key k, Value v);
Value get(Key k);
bool contains(Key k);
void clear();
```

*NOTE: The LLRBTMap class is dependent on the LLRBT class.*
# Data Structures

As part of my introduction to the C++ language, I decided to implement some of the data structures that
I had learned in my CS class to learn the intricacies of the language.

## Disjoint Sets

### The Disjoint Sets Abstract Data Type

The disjoint sets abstract data type allows one to make nodes, establish connectivity between those nodes,
and check interconnectivity of those nodes. *Connectivity* in this context is, formally, an equivalence
relation. That is, beyond symmetric and reflexive properties, connectivity is a transitive relation; if
Node A is connected to Node B, and Node B is connected to Node C, then Node A is connected to Node C.

Note, however, that the data structure does not answer the question, "How are two nodes connected to each 
other?" It merely determines whether there *is* a connnection. As a result, there is no way to delete 
connections between nodes once they are made. These limitations result in various optimizations that all 
stem from treating the connections as forming several disjoint sets, the source of the data structure.

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


# Disjoint Sets

As part of my introduction to the C++ language, I decided to implement one of the data structures that
I had learned in my CS class to learn the constructs of the language.

## Usage

1. Construction
    ```cpp
    // Creates a pointer to a DisjointSets object with 10 nodes
    DisjointSets *sets = new DisjointSets(10);                                            
    ```

2. Making Connections


*More examples will be supplied later as more of the data structure is written and tested.*

## The Disjoint Sets Abstract Data Type

The disjoint sets abstract data type allows one to make nodes, establish connectivity between those nodes,
and check interconnectivity of those nodes. *Connectivity* in this context is, formally, an equivalence
relation. That is, beyond symmetric and reflexive properties, connectivity is a transitive relation; if
Node A is connected to Node B, and Node B is connected to Node C, the Node A is connected to Node C.

Note, however, that the data structure does not answer the question, "How are two nodes connected to each other?"
It merely determines whether there *is* a connnection. As a result, there is no way to delete connections between
nodes once they are made. These limitations result in various optimizations that all stem from treating 
the connections as forming several disjoint sets, the source of the data structure.

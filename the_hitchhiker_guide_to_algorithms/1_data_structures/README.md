# Data Structures

Data structures are not so much algorithms as they are the fundamental constructs around which you build your application. Becoming fluent in what the standard data structures can do for you is essential to get full value from them.

## Dictionaries

**Input description**: A set of $n$ records, each identified by one or more key fields.
**Problem description**: Build and maintain a data structure to efficiently locate, insert, and delete the record associated with any query key $q$.

## Priority Queues

**Input description**: A set of records with numerically or otherwise totally-ordered keys.
**Problem description**: Build and maintain a data structure for providing quick access to the smallest or largest key in the set.

## Suffix Trees and Arrays

**Input description**: A reference string $S$.
**Problem description**: Build a data structure to quickly find all places where an arbitrary query string $q$ occurs in $S$.

## Graph Data Structures

**Input description**: A graph $G$.
**Problem description**: Represent the graph $G$ using a flexible, efficient data structure.

## Set Data Structures

**Input description**: A universe of items $U = \lbrace u_1,...,u_n \rbrace$ on which is defined a collection of subsets $S = \lbrace S_1,...,S_m \rbrace$.
**Problem description**: Represent each subset so as to efficiently (1) test whether $u_i \in S_j$, (2) compute the union or intersection of $S_i$ and $S_j$, and (3) insert or delete members of $S$.

## Kd-Trees

**Input description**: A set $S$ of $n$ points or more complicated geometric objects in $k$ dimensions.
**Problem description**: Construct a tree that partitions space by half-planes such that each object is contained in its own box-shaped region.

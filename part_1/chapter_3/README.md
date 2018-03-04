# Data Structures

## Contiguous vs. Linked Data Structures

Data structures can be neatly classified as either _contiguous_ or _linked_ depending or whether they are based on arrays or pointers.
* _Contiguous-allocated structures_, single slabs of memory, arrays, matrices, heaps and hash tables.
* _Linked Data structures_ distinct chunks of memory glued by pointers, lists, trees and graph adjacency lists.

__Arrays__  
The fundamental contiguously-allocated data structure.

Advantages:
* _Constant-time access given the index_
* _Space efficiency_
* _Memory locality_

Downside: fixed size.

__Pointers and Linked Structures__

_Pointers_ represent the address of a location in memory.

_Simple Linked Structure_
```c
typedef struct list {
    item_type item;     // data item
    struct list *next;  // pointer to successor
} list;
```
__Comparison__:  
Linked lists have it at:
* Overflow occurs only when memory is full.
* Insertions and deletions are _simpler_ for contiguous lists.
* With large records, moving pointer is easier and faster.

Arrays have it at:
* More pointer space for linked structures.
* Linked lists do not allow efficient random access to items.
* Better memory locality and cache performance.

Both structures are recursive objects, good for divide-and-conquer.

## Stacks and Queues

* _Stacks_, LIFO push and pop.
* _Queues_, FIFO enqueue and dequeue.

## Dictionaries

* _Search(D,k)_
* _Insert(D,x)_
* _Delete(D,x)_

_Some implements_:
* _Max(D)_ or _Min(D)_
* _Predecessor(D,x)_

Dictionary operation | Unsorted Array | Sorted Array 
-                   | -     | -
Search(L,k)         | O(n)  | O(log(n))
Insert(L,x)         | O(1)  | O(n)
Delete(L,x)         | O(1)* | O(n)
Successor(L,x)      | O(n)  | O(1)
Predecessor(L,x)    | O(n)  | O(1)
Minimum(L)          | O(n)  | O(1)
Maximum(L)          | O(n)  | O(1)



Dictionary operation | Singly-linked unsorted List | Doubly-linked unsorted List | Singly-linked sorted List | Doubly-linked sorted List 
-                   | -     | -     | -     | - 
Search(L,k)         | O(n)  | O(n)  | O(n)  | O(n)
Insert(L,x)         | O(1)  | O(1)  | O(n)  | O(n)
Delete(L,x)         | O(n)* | O(1)  | O(n)* | O(1)
Successor(L,x)      | O(n)  | O(n)  | O(1)  | O(1)
Predecessor(L,x)    | O(n)  | O(n)  | O(n)* | O(1)
Minimum(L)          | O(n)  | O(n)  | O(1)  | O(1)
Maximum(L)          | O(n)  | O(n)  | O(1)* | O(1)

## Binary Search Trees

_Binary search_ requires that we have fast access to _two elements_--specifically the median elements above and below the given node.

A _binary search tree_ labels each node in a binary tree with a single key such that for any node labeled x, all nodes in the left subtree of x have keys < x while all nodes in the right subtree of x have keys > x.

```c
typedef struct tree {
    item_type item;         // data item
    struct tree *parent;    // pointer to parent
    struct tree *left;      // pointer to left child
    struct tree *right;     // pointer to right child
} tree;
```
__Basic operations:__
* Searching, O(h) where h denotes the height of the tree
* Finding Minimum and Maximum Elements, Minimum the leftmost element and Maximum is the rightmost element O(h)
* Traversal, O(n)
* Insertion, O(h)
* Deletion, O(h)

__How good Are Binary Search Tree ?__  
When the tree is perfectly balanced _h = ceil(log(n))_.  
Trees depends on insertion order, and bad things can happen (i.e adding sorted items will build a skinny linear height tree populating only right pointers and _h = n_).

On _average_ when we average over the _n!_ possible insertion orderings, we have a high probability of O(log(n)) height.  
The power of _randomization_ can produce algorithms with good performance with high probability. Quicksort is a child of such a thought.

__Balanced Search Trees__  
Sophisticated _balanced_ binary search tree data structures have been deployed that guarantee the height of the tree always to be _O(log(n))_, therefore all dictionary operations (insert, delete, query) take _O(log(n))_ time each.

Picking the wrong data structure for the job can be disastrous in terms of performance. identifying the very best data structure is usually not as critical, because there can be several choices that perform similarly.

## Priority Queues

_Priority queues_ are data structures that provide more flexibility than simple sorting, because they allow new elements to enter a system at arbitrary intervals.
* _Insert(Q,x)_
* _Find-Minimum/Maximum(Q)_
* _Delete-Minimum/Maximum(Q)_

Building algorithms around around data structures such as dictionaries and priorities queues leads to both clean structure and good performance.

Priority queue operation | Unsorted Array | Sorted Array | Balanced Binary Search tree
-                   | -     | -     | -
Insert(Q,x)         | O(1)  | O(n)  | O(log(n))
Find-Minimum(Q)     | O(1)  | O(1)  | O(1)
Delete-Minimum(Q)   | O(n)  | O(1)  | O(log(n))

The trick for a constant time Find-Minimum is using an extra variable to store a pointer/index to the minimum entry.

## Hashing and Strings

A hash function is a mathematical function that maps keys to integers. Using it we can map dictionary keys to integers indexes of an array and enjoy the instantness of constant times operations.

H(S) = sum(0, length(S), i => α^(length(S) - (i+1)).char(Si));  
_where_  
__α__ is the the size of the alphabet on which a given string _S_ is written.  
__char(c)__ a function that maps each symbol of the alphabet to a unique integer from 0 to _α_ - 1.

H(S) maps each string to a unique (but large) integer by treating the characters of the string as "digits" in a base-_α_ number system.  
By selecting a good m number (ideally a large prime number not too close to 2^i - 1) we could produce uniformly distributed hash values with ___H(S)_ mod _m___.

__Collision Resolution__  
_Chaining_ is the easiest approach to collision resolution. Which is an array of _m_ linked lists. the _ith_ list will contain all the items that hash to the value of _i_. Chaining is natural but has a lot of pointer memory.  
_Open Addressing_ maintains an array of elements (not buckets) and inserts elements of similar hash into contiguous places.


Chaining with doubly linked lists | Hash table (expected) | Hash table (worst case)
-                   | -         | -
Search(L, k)        | O(n/m)    | O(n)
Insert(L, x)        | O(1)      | O(1)
Delete(L, x)        | O(1)      | O(1)
Successor(L, x)     | O(n+m)    | O(n+m)
Predecessor(L, x)   | O(n+m)    | O(n+m)
Minimum(L)          | O(n+m)    | O(n+m)
Maximum(L)          | O(n+m)    | O(n+m)

Hashing is a fundamental idea in randomized algorithms, yielding linear expected-time algorithms for problems otherwise _θ(n.log(n))_, or _θ(n^2)_ in the worst case.

## Specialized Data Structures

* _String data structures_, most likely array of characters.
* _Geometric data structures_, collections of data points and regions.
* _Graph data structures_, typically represented with either adjacency matrices or adjacency lists.
* _Set data structures_,  typically represented with dictionaries, or _bit vectors_ for subsets holding ones for _i_ in the subsets.   
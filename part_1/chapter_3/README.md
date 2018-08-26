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

list* search_list(list *l, item_type x)
{
    if(l == NULL) return NULL;

    if(l->item == x) return l;
    else return search_list(l->next, x));
}

void insert_list(list **l, item_type x)
{
    list *p;

    p = malloc(sizeof(list));
    p->item = x;
    p->next = *l;
    *l = p;
}

list* predecessor_list(list *l, item_type x)
{
    if(l == NULL || l->next == NULL)
        return NULL;

    if((l->next)->item == x) return l;
    else return predecessor_list(l->next, x);
}

void delete_list(list **l, item_type x)
{
    list *p;    // item pointer
    list *pred; // predecessor pointer
    list *search_list(), *predecessor_list();

    p = search_list(*l, x);
    if(p != NULL)
    {
        pred = predecessor_list(*l, x);
        if(pred == NULL) *l = p->next;
        else pred->next = p->next;

        free(p) // free memory used by node
    }
}
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

* _Search(D, k)_
* _Insert(D, x)_
* _Delete(D, x)_

_Some implements_:
* _Max(D)_ or _Min(D)_
* _Predecessor(D, x)_


Dictionary operation    | Unsorted Array   | Sorted Array
---                     | ---              | ---
_Search(L, k)_          | $O(n)$           | $O(\log{n})$
_Insert(L, x)_          | $O(1)$           | $O(n)$
_Delete(L, x)_          | $O(1)*$          | $O(n)$
_Successor(L, x)_       | $O(n)$           | $O(1)$
_Predecessor(L, x)_     | $O(n)$           | $O(1)$
_Minimum(L)_            | $O(n)$           | $O(1)$
_Maximum(L)_            | $O(n)$           | $O(1)$
$

Dictionary operation | Singly-linked unsorted List | Doubly-linked unsorted List | Singly-linked sorted List | Doubly-linked sorted List
---                 | ---       | ---       | ---       | ---
_Search(L, k)_      | $O(n)$    | $O(n)$    | $O(n)$    | $O(n)$
_Insert(L, x)_      | $O(1)$    | $O(1)$    | $O(n)$    | $O(n)$
_Delete(L, x)_      | $O(n)*$   | $O(1)$    | $O(n)*$   | $O(1)$
_Successor(L, x)_   | $O(n)$    | $O(n)$    | $O(1)$    | $O(1)$
_Predecessor(L, x)_ | $O(n)$    | $O(n)$    | $O(n)*$   | $O(1)$
_Minimum(L)_        | $O(n)$    | $O(n)$    | $O(1)$    | $O(1)$
_Maximum(L)_        | $O(n)$    | $O(n)$    | $O(1)*$   | $O(1)$

## Binary Search Trees

_Binary search_ requires that we have fast access to _two elements_--specifically the median elements above and below the given node.

A _binary search tree_ labels each node in a binary tree with a single key such that for any node labeled $x$, all nodes in the left subtree of $x$ have keys < $x$ while all nodes in the right subtree of $x$ have keys > $x$.

```c
typedef struct tree {
    item_type item;         // data item
    struct tree *parent;    // pointer to parent
    struct tree *left;      // pointer to left child
    struct tree *right;     // pointer to right child
} tree;

tree* search_tree(tree *l, item_type x)
{
    if(l == NULL) return NULL;

    if(l->item == x) return l;

    if(x < l->item) return search_tree(l->left; x);
    else return search_tree(l->right, x);
}

tree* find_minimum(tree *t)
{
    tree *min;

    if(t == NULL) return NULL;

    min = t;
    while(min->left != NULL)
        min = min->left;
    return min;
}

void traverse_tree(tree *l)
{
    if(l != NULL)
    {
        traverse_tree(l->left);
        process_item(l->item);
        traverse_tree(l->right);
    }
}

void insert_tree(tree **l, item_type x, tree *parent)
{
    tree *p; // temporary pointer

    if(*l == NULL)
    {
        p = malloc(sizeof(tree)); // allocate new node
        p->item = x;
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p; // link into parent's record
        return;
    }

    if(x < (*l)->item)
        insert_tree(&((*l)->left), x, *l);
    else
        insert_tree(&((*l)->right), x, *l);
}
```
__Basic operations:__
* _Searching_, $O(h)$ where _h_ denotes the height of the tree.
* _Finding Minimum and Maximum Elements_, Minimum the leftmost element and Maximum is the rightmost element $O(h)$.
* _Traversal_, $O(n)$
* _Insertion_, $O(h)$
* _Deletion_, $O(h)$

__How good Are Binary Search Tree ?__

When the tree is perfectly balanced $h = \lceil \log{n}\rceil$.
Trees depends on insertion order, and bad things can happen (i.e adding sorted items will build a skinny linear height tree populating only right pointers and $h = n$).

On _average_ when we average over the $n!$ possible insertion orderings, we have a high probability of $O(\log{n})$ height.
The power of _randomization_ can produce algorithms with good performance with high probability. Quicksort is a child of such a thought.

__Balanced Search Trees__

Sophisticated _balanced_ binary search tree data structures have been deployed that guarantee the height of the tree always to be $O(\log{n})$, therefore all dictionary operations (insert, delete, query) take $O(\log{n})$ time each.

Picking the wrong data structure for the job can be disastrous in terms of performance. identifying the very best data structure is usually not as critical, because there can be several choices that perform similarly.

## Priority Queues

_Priority queues_ are data structures that provide more flexibility than simple sorting, because they allow new elements to enter a system at arbitrary intervals.
* _Insert(Q, x)_
* _Find-Minimum/Maximum(Q)_
* _Delete-Minimum/Maximum(Q)_

Building algorithms around around data structures such as dictionaries and priorities queues leads to both clean structure and good performance.

Priority queue operation | Unsorted Array | Sorted Array | Balanced Binary Search tree
---                 | ---     | ---     | ---
_Insert(Q, x)_      | $O(1)$  | $O(n)$  | $O(\log{n})$
_Find-Minimum(Q)_   | $O(1)$  | $O(1)$  | $O(1)$
_Delete-Minimum(Q)_ | $O(n)$  | $O(1)$  | $O(\log{n})$

The trick for a constant time Find-Minimum is using an extra variable to store a pointer/index to the minimum entry.

## Hashing and Strings

A hash function is a mathematical function that maps keys to integers. Using it we can map dictionary keys to integers indexes of an array and enjoy the instantness of constant times operations.

$H(S) = \sum_{i=0}^{|S|} α^{|S| - (i+1)}char(S_i)$
_where_
$α$ is the the size of the alphabet on which a given string $S$ is written.
```char(c)``` a function that maps each symbol of the alphabet to a unique integer from $0$ to $α - 1$.

$H(S)$ maps each string to a unique (but large) integer by treating the characters of the string as "digits" in a base-_α_ number system.
By selecting a good m number (ideally a large prime number not too close to $2^{i-1}$) we could produce uniformly distributed hash values with $H(S)\bmod m$.

__Collision Resolution__

_Chaining_ is the easiest approach to collision resolution. Which is an array of $m$ linked lists. the _ith_ list will contain all the items that hash to the value of $i$. Chaining is natural but has a lot of pointer memory.
_Open Addressing_ maintains an array of elements (not buckets) and inserts elements of similar hash into contiguous places.


Chaining with doubly linked lists | Hash table (expected) | Hash table (worst case)
---                 | ---       | ---
_Search(L, k)_      | $O(n/m)$  | $O(n)$
_Insert(L, x)_      | $O(1)$    | $O(1)$
_Delete(L, x)_      | $O(1)$    | $O(1)$
_Successor(L, x)_   | $O(n+m)$  | $O(n+m)$
_Predecessor(L, x)_ | $O(n+m)$  | $O(n+m)$
_Minimum(L)_        | $O(n+m)$  | $O(n+m)$
_Maximum(L)_        | $O(n+m)$  | $O(n+m)$

Hashing is a fundamental idea in randomized algorithms, yielding linear expected-time algorithms for problems otherwise $\Theta(n\log{n})$, or $\Theta(n^2)$ in the worst case.

## Specialized Data Structures

* _String data structures_, most likely array of characters.
* _Geometric data structures_, collections of data points and regions.
* _Graph data structures_, typically represented with either adjacency matrices or adjacency lists.
* _Set data structures_,  typically represented with dictionaries, or _bit vectors_ for subsets holding ones for $i$ in the subsets.

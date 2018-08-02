# Sorting and Searching

* Sorting is the basic building block that many other algorithms are built around.
* Most of the interesting ideas used in the design of algorithms appear in the context of sorting, such as divide-and-conquer, data structures and randomized algorithms.
* Sorting is the most thoroughly studied problem in computer science. Literally dozens of different algorithms are known, most of which possess some particular advantage over all other algorithms in certain situations.

In this sense, sorting behaves more like a data structure than a problem in its own right.

## Applications of Sorting 
Several algorithms along with different complexities exist but the punch-line is this: clever algorithms exist in $O(log(n))$. This is a big improvement over naive $O(n^2)$.   
Many important problems can be reduced to sorting, so we can use our clever $O(log(n))$ algorithms to do work that might otherwise seem to a quadratic algorithm. _Searching, closest pair, element uniqueness, selection, convex hulls._   
Sorting lies at the heart of many algorithms. Sorting the data is one of the first things any algorithms designer should try in the quest for efficiency.

## Pragmatics of Sorting
* _Increasing or decreasing order?_ Subject to the application.
* _Sorting just the key or an entire record?_ Specify the key field.
* _What should we do with equal keys?_ Resort to secondary keys. Stable algorithms preserve the initial relative order(by adding the initial position as a secondary key), most of the time at the cost of performance. Ignoring ties can be costly for some unaware algorithms.
* _What about non-numerical data?_ Alphabetizing for text strings requires explicit conjectural decisions for _collating  sequence_ of characters and punctuation.

The right way to specify such matters to your sorting algorithm is with application-specific pairwise-element _comparison function_. Such a comparison function takes pointers to record items _a_ and _b_ and returns “<“ if _a < b_, “>” if _a > b_, or “=” if _a = b_.   
By abstracting the pairwise ordering decision to such a comparison function, we can implement sorting algorithms independently of such criteria.

## Heapsort: Fast Sorting via Data Structures

The name typically given to this algorithm, _heapsort_, obscures  the relationship between them, but heapsort is nothing but an implementation of selection sort using the right data structure,  a _heap_. 

__Heaps__   
Heaps are a simple and elegant data structure for efficiently supporting the priority queue operations insert and extract-min. They work by maintaining a partial order on the set of elements which is weaker than the sorted order (so it can be efficient to maintain) yet stronger than random order (so the minimum element can be quickly identified).   
Power in any hierarchically-structured organization is reflected  by a tree where each node in the tree represent a person, and edge _(x, y)_ implies that _x_ directly supervises (or dominates) _y_. The fellow at the root sits at the “top of the heap”.   
In this spirit, a _heap-labeled tree_ is defined to be a binary tree such that the key labeling of each node _dominates_ the key labeling of each of its children. In a _min-heap_, a node dominates its children by containing a smaller key than they do, while in a _max-heap_ parents node dominate by being bigger.   
The heap is a slick data structure that enables us to represent binary trees without using any pointers. We will store data as an array of keys, and use the position of the keys to _implicitly_ satisfy the role of pointers. In general, we store the $2^{l-1}$ keys of the _l_th level of a complete binary tree from left-to-right in positions $2^{l-1}$ to $2^l-1$. We assume that the array starts with 1 to simplify matters.

```c
pq_parent(int n)
{
    if(n == 1) return(-1);
    else return((int) n/2); // implicitly take floor(n/2)
}

pq_young_child(int n)
{
    return(2 * n);
}
```

What is the catch? Suppose our height _h_ tree was sparse, meaning that the number of nodes $n < 2^h$. All missing internal nodes still take up space in our structure, since we must represent a full binary tree to maintain the positional mapping between parents and children.   
Space efficiency thus demands that we not allow holes in our tree—i.e., that each level be packed as much as it can be. If so, only the last level may be incomplete.    
We sacrifice flexibility (arbitrary tree topologies, displacement of subtree and mostly the ability to represent binary search tree) to gain efficiency (_n_ length array for _n_ elements tree and constant time operations for the priority-queue needs).

__Constructing Heaps__   
We place the new element at the _n+1_ position. We then keep swapping it with its parent and thus bubbling it up to the top of the tree as long as it’s breaking the label classification of the heap.   
$O(log(n))$ for insertion and $O(n.log(n))$ for initial construction.

__Extracting the Minimum__    
We identify the root of the heap as the minimum, extract it and fill it with the right most element. We then keep swapping it with the smallest dominant of its children and thus bubbling it down to the bottom of the tree as long as it’s breaking the label classification of the heap.   
This percolate-down operation is also called _heapify_, because it merges two heaps (the subtrees below the original root) with a new key.   
The extract-min operation costs $O(log(n))$. Exchanging the maximum element with the last element and calling heapify repeatedly gives an $O(n.log(n))$ sorting algorithm, named _Heapsort_.   
Heapsort is a great and simple to program sorting algorithm. It runs in worst-case $O(n.log(n))$ time, which is the best that can be expected from any sorting algorithm. It is an _inplace_ sort, using no extra memory. Although other algorithms prove slightly faster in practice, you won’t go wrong using Heapsort for sorting data that sits in the computer’s main memory.   





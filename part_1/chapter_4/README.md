# Sorting and Searching

* Sorting is the basic building block that many other algorithms are built around.
* Most of the interesting ideas used in the design of algorithms appear in the context of sorting, such as divide-and-conquer, data structures, and randomized algorithms.
* Sorting is the most thoroughly studied problem in computer science. Literally dozens of different algorithms are known, most of which possess some particular advantage over all other algorithms in certain situations.

In this sense, sorting behaves more like a data structure than a problem in its own right.

## Applications of Sorting

Several algorithms along with different complexities exist but the punch-line is this: clever algorithms exist in $O(n\log{n})$. This is a big improvement over naive $O(n^2)$.
Many important problems can be reduced to sorting, so we can use our clever $O(n\log{n})$ algorithms to do work that might otherwise seems to be the destined to a quadratic algorithm. _Searching, closest pair, element uniqueness, selection_, and _convex hulls._
Sorting lies at the heart of many algorithms. Sorting the data is one of the first things any algorithms designer should try in the quest for efficiency.

## Pragmatics of Sorting

* _Increasing or decreasing order?_ Subject to the application.
* _Sorting just the key or an entire record?_ Specify the key field.
* _What should we do with equal keys?_ Resort to secondary keys. Stable algorithms preserve the initial relative order (by adding the initial position as a secondary key), most of the time at the cost of performance. Ignoring ties can be costly for some unaware algorithms.
* _What about non-numerical data?_ Alphabetizing for text strings requires explicit conjectural decisions for _collating  sequence_ of characters and punctuation.

The right way to specify such matters to your sorting algorithm is with application-specific pairwise-element _comparison function_. Such a comparison function takes pointers to record items $a$ and $b$ and returns $“<“$ if $a < b$, $“>”$ if $a > b$, or $“=”$ if $a = b$.   
By abstracting the pairwise ordering decision to such a comparison function, we can implement sorting algorithms independently of such criteria.

```c
#include <stdlib.h>

void qsort(void *base, size_t nel, size_t width, int (*compare) (const void *, const void *));

int intcompare(int *i, int *j)
{
    if(*i > *j) return (1);
    if(*i < *j) return (-1);
    return (0);
}

qsort(a, n, sizeof(int), intcompare);

```

## Heapsort: Fast Sorting via Data Structures

The name typically given to this algorithm, _heapsort_, obscures  the relationship between them, but heapsort is nothing but an implementation of selection sort using the right data structure,  a _heap_.

__Heaps__

Heaps are a simple and elegant data structure for efficiently supporting the priority queue operations _insert_ and _extract-min_. They work by maintaining a partial order on the set of elements which is weaker than the sorted order (so it can be efficient to maintain) yet stronger than random order (so the minimum element can be quickly identified).   
Power in any hierarchically-structured organization is reflected  by a tree where each node in the tree represent a person, and edge $(x, y)$ implies that $x$ directly supervises (or dominates) $y$. The fellow at the root sits at the “top of the heap”.
In this spirit, a _heap-labeled tree_ is defined to be a binary tree such that the key labeling of each node _dominates_ the key labeling of each of its children. In a _min-heap_, a node dominates its children by containing a smaller key than they do, while in a _max-heap_ parents node dominate by being bigger.
The heap is a slick data structure that enables us to represent binary trees without using any pointers. We will store data as an array of keys, and use the position of the keys to _implicitly_ satisfy the role of pointers. In general, we store the $2^{l-1}$ keys of the _lth_ level of a complete binary tree from left-to-right in positions $2^{l-1}$ to $2^l-1$. We assume that the array starts with 1 to simplify matters.

```c
typedef struct {
    item_type q[PQ_SIZE+1]; // body of queue
    int n;                  // number of queue elements
} priority_queue;

int pq_parent(int n)
{
    if(n == 1) return(-1);
    else return((int) n/2); // implicitly take floor(n/2)
}

int pq_young_child(int n)
{
    return(2 * n);
}
```

What is the catch? Suppose our height _h_ tree was sparse, meaning that the number of nodes $n < 2^h$. All missing internal nodes still take up space in our structure, since we must represent a full binary tree to maintain the positional mapping between parents and children.   
Space efficiency thus demands that we not allow holes in our tree—i.e., that each level be packed as much as it can be. If so, only the last level may be incomplete.
We sacrifice flexibility (arbitrary tree topologies, displacement of subtree and mostly the ability to represent binary search tree) to gain efficiency (_n_ length array for _n_ elements tree and constant time operations for the priority-queue needs).

__Constructing Heaps__

We place the new element at the $n+1$ position. We then keep swapping it with its parent and thus bubbling it up to the top of the tree as long as it’s breaking the label classification of the heap.
$O(\log{n})$ for insertion and $O(n\log{n})$ for initial construction.

```c
void pq_insert(priority_queue *q, item_type x)
{
    if(q->n >= PQ_SIZE)
        printf("Warning; priority queue overflow insert x=%d\n", x);
    else
    {
        q->n = (q->n) +1;
        q->q[q->n] = x;
        bubble_up(q, q->n);
    }
}

void bubble_up(priority_queue *q, int p)
{
    if(pq_parent(p) == -1) return; // at root of heap, no parent

    if(q->q[pq_parent(p)] > q->q[p])
    {
        pq_swap(q, p, pq_parent(p));
        bubble_up(q, pq_parent(p));
    }
}

void pq_init(priority_queue *q)
{
    q->n = 0;
}

void make_heap(priority_queue *q, item_type s[], int n)
{
    int i; // counter

    pq_init(q);
    for(i=0; i<n; i++)
        pq_insert(q, s[i]);
}
```

__Extracting the Minimum__

We identify the root of the heap as the minimum, extract it and fill it with the right most element. We then keep swapping it with the smallest dominant of its children and thus bubbling it down to the bottom of the tree as long as it’s breaking the label classification of the heap.
This percolate-down operation is also called _heapify_, because it merges two heaps (the subtrees below the original root) with a new key.   
The extract-min operation costs $O(\log{n})$. Exchanging the maximum element with the last element and calling heapify repeatedly gives an $O(n\log{n})$ sorting algorithm, named _Heapsort_.   
Heapsort is a great and simple way to program sorting algorithm. It runs in worst-case $O(n\log{n})$ time, which is the best that can be expected from any sorting algorithm. It is an _inplace_ sort, using no extra memory. Although other algorithms prove slightly faster in practice, you won’t go wrong using Heapsort for sorting data that sits in the computer’s main memory.

```c
item_type extract_min(priority_queue *q)
{
    int min = -1; // minimum value

    if( q->n <= 0) printf("Warning: empty priority queue.\n");
    else
    {
        min = q->q[1];

        q->q[1] = q->q[q->n];
        q->n = q->n - 1;
        bubble_down(q, 1);
    }

    return min;
}

void bubble_down(priority_queue *q, int p)
{
    int c;          // child index
    int i;          // counter
    int min_index;  // index of lightest child

    c = pq_young_child(p);
    min_index = p;

    for(i=0; i<=1, i++)
    {
        if((c+i) <= q->n)
        {
            if(q->q[min_index] > q->q[c+i]) min_index = c+i;
        }
    }

    if(min_index != p)
    {
        pq_swap(q, p, min_index);
        bubble_down(q, min_index);
    }
}

void heapsort(item_type s[], int n)
{
    int i;              // counters
    priority_queue q;   // heap for heapsort

    make_heap(&q, s, n);

    for(i=0; i<n; i++)
        s[i] = extract_min(&q);
}
```

__Faster Heap Construction__

Surprisingly, heaps can be constructed even faster by using our ```bubble_down``` procedure and some clever analysis.
Suppose we pack the $n$ keys destined for our heap into the first $n$ elements of our priority_queue array. The shape of our heap will be right, but the dominance order will be all messed up. ```bubble_down``` will restore the heap order of arbitrary root element sitting on two of two sub-heaps. We recursively execute it from the elements at position $n/2$ down to the first element i.e. the most bottom down elements that are non leaves to the root, the leaves already dominating their non existing elements.
```c
void make_heap(priority_queue *q, item_type s[], int n)
{
    int i;  // counter

    q->n = n;
    for(i=0; i<n; i++) q->q[i+1] = s[i];

    for(i=q->n/2; i>=1; i--) bubble_down(q,i);
}
```

__Sorting by incremental Insertion__

Insertion is perhaps the simplest example of the _incremental insertion_ technique, where we build up a complicated data structure on $n$ items by first building it on $n-1$ items and then making the necessary changes to add the last item. Incremental insertion proves a particularly useful technique in geometric algorithms.

## Mergesort: Sorting by Divide-and-Conquer
Recursive algorithms reduce large problems into smaller ones. A recursive approach to sorting involves partitioning the elements  into two groups sorting each of the smaller problems recursively, and then interleaving the two sorted lists to totally order the elements. The algorithm is called _mergesort_. It is important to recognize the importance of the interleaving operation.

```c
void mergesort(item_type s[], int low, int high)
{
    int middle; // index of middle element

    if (low < high)
    {
        middle = (low + high)/2;
        mergesort(s, low, middle);
        mergesort(s, middle+1, high);
        merge(s, low, middle, high);
    }
}

void merge(item_type s[], int low, int middle, int high)
{
    int i;                  // counter;
    queue buffer1, buffer2; // buffers to hold elements for merging

    init_queue(&buffer1);
    init_queue(&buffer2);

    for (i=low; i<=middle; i++) enqueue(&buffer1, s[i]);
    for (i=middle+1; i<=high; i++) enqueue(&buffer2, s[i]);

    i = low;
    while(!(empty_queue(&buffer1) || empty_queue(&buffer2)))
    {
        if(headq(&buffer1) <= headq(&buffer2))
            s[i++] = dequeue(&buffer1);
        else
            s[i++] = dequeue(&buffer2);
    }

    while(!empty_queue(&buffer1)) s[i++] = dequeue(&buffer1);
    while(!empty_queue(&buffer2)) s[i++] = dequeue(&buffer2);
}
```

Mergesort is a classic divide-and-conquer algorithm. We are ahead of the game whenever we can break one large problem into two smaller problems, because the smaller problems are easier to solve. The trick is taking advantage of the two partial solutions to construct a solution of the full problem.



## Quicksort: Sorting by Randomization

Selecting a random item $p$ _the pivot_ from the $n$ items we seek to sort allows _Quicksort_ the separate the $n-1$ items into two piles: a low pile containing all the elements that appear before $p$ in sorted order an a high pile containing all the elements that appear after $p$ in sorted order. This gives us a recursive sorting algorithm.
```c
void quicksort(item_type s[], int l, int h)
{
    int p;  // index partition

    if(h-l > 0)
    {
        p = partition(s, l, h);
        quicksort(s, l, p-1);
        quicksort(s, p+1, h);
    }
}

int partition(item_type s[], int l, int h)
{
    int i;          // counter
    int p;          // pivot element index
    int first_high;  // divider position for pivot element

    p = h;
    first_high = l;
    for(i=l; i<h; i++)
    {
        if(s[i] < s[p])
        {
            swap(&s[i], &s[first_high]);
            first_high++;
        }
    }
    swap(&s[p], &s[first_high]);

    return first_high;
}
```

We then use $randomization$ to improve algorithms with bad worst-case but good average-case complexity. It can be used to make algorithms more robust to boundary cases and more efficient on highly structured input instances that confound heuristic decisions (such as sorted input to quicksort). It often lends itself to simple algorithms that provide randomized performance guarantees which are otherwise obtainable only using complicated deterministic algorithms.
Some of the approaches to designing efficient randomized algorithms are readily explainable:
* _Random sampling_ — selects a small random sample of the input and study those, for the results should be representative.
* _Randomized hashing_ — we can randomly select our hash function from a large family of good ones to get lesser a chance to match an input with its weak hashing function.
* _Randomized search_ — can be used to drive search techniques such as simulated annealing.

Quicksort provides a search performance of $\Theta(n\log{n})$ which is a clear asymptotic difference from an $\Theta(n^2)$ algorithm. When comparing it with other $\Theta(n\log{n})$ search algorithms, the RAM model and Big Oh analysis provide too coarse a set of tools to make that type of distinction. Implementation details and system quirks such as cache performance and memory size may well prove to be the decisive factor.
It can be said that quicksort, when implemented well is typically 2-3 times faster than mergesort or heapsort. The primary reason is that the operations in the innermost loop are simpler.

## Distribution Sort: Sorting via Bucketing

Sorting names for the telephone book by partitioning them according to the first letter of the last name, ordering those partitions and then recursively apply the same technique to each partition until we end up with partitions of one is a good example of _bucketsort_ or _distribution sort_.
Bucketing is a very effective idea whenever we are confident that the distribution of data will be roughly uniform. It is the idea that underlies hash tables, _kd_-trees, and variety of other practical data structures. The downside of such techniques is that the performance can be terrible when the data distribution is not what we expected.

__Lower Bounds for sorting__

Sorting algorithms run in worst-case $O(n\log{n})$ time and we can say that there is a $Ω(n\log{n})$ lower bound for them. Just think of all the $n!$ permutations of $n$ keys as all the possible pair comparisons for a set of $n$ elements. We now know that we clearly don't have to assess all of them but this tree of $n!$ leaves has a minimum height of $\lg{n!}$ which happens to be $\Theta(n\log{n})$.
This lower bound is important for several reasons, First, the idea can be extended to give lower bounds for many applications of sorting, including element uniqueness, finding the mode, and constructing convex hulls. Sorting has one of the few nontrivial lower bounds among algorithmic problems. We will present an alternate approach to arguing that faster algorithms are unlikely to exist.

__Sorting can be used to illustrate most algorithm design paradigms. Data structure techniques, divide-and-conquer, randomization, and incremental construction all lead to efficient sorting algorithms.__

## Binary Search and Related Algorithms

Binary search is a fast algorithm for searching in a sorted array of keys $S$. To search for a key $q$, we compare $q$ to the middle key $S[n/2]$. If $q$ appears before $S[n/2]$, it must reside in the top half of $S$; if not, it must reside in the bottom half of $S$. By repeating this process recursively on the correct half, we locate the key in a total of $\lceil \lg{n}\rceil$ comparisons— a big win over the $n/2$ comparisons expected from using sequential search.

```c
int binary_search(item_type s[], item_type key, int low, int high)
{
    int middle; // index of middle element

    if(low > high) return -1;

    middle = (low+high)/2;

    if(s[middle] == key) return middle;

    if(s[middle] > key)
        return binary_search(s; key, low, middle-1);
    else
        return binary_search(s; key, middle+1, high);
}
```

What is important is to have a sense of just how fast binary search is. The popular children's game _Twenty questions_ can be solved under 20 questions if we just try to find the looked for word by using the binary search technique on a dictionary.

Several interesting algorithms follow from simple variants of binary search. Like _counting the occurrences_ of a key in a sorted array. Using _binary search_ by looking for the low bound while not stopping at a matching equality will give us the starting index of such keys. Repeating the procedure in the opposite direction gives the end index of those. Finally a simple subtraction gives the solution away.  
_One-sided binary search_ is most useful whenever we are looking for a key that lies close to our current position, in a run of many similar keys that are arranged sequentially by likeness. Looking for a pivot point always points us toward the correct portion where we should keep directing our search.   
_Square and other roots_ are also more easily obtained using _binary_search_ knowing that testing the median of the distribution will also tells more precisely in which portion to look next, reducing drastically the size of the problem.

__Binary search and its variants are the quintessential divide-and-conquer algorithms.__

## Divide-and-Conquer

One of the most powerful techniques for solving problems is to break them down into smaller, more easily solved pieces. Smaller problems are less overwhelming, and they permit us to focus on details that are lost when we are studying the entire problem. A recursive algorithm starts to become apparent when we can break the problem into smaller instances of the same type of problem. Effective parallel processing requires decomposing jobs into a least as many tasks as processors, and is becoming more important with the advent of cluster computing and multicore processors.   
Two important algorithm design paradigms are based on breaking problems down into smaller problems. _Dynamic programming_ typically removes one element from the problem, solves the smaller problem, and then uses the solution to this smaller problem to add back the element in the proper way. _Divide-and-conquer_ instead splits the problem in (say) halves, solves each half, then stitches the pieces back together to form a full solution.   
To use divide-and-conquer as an algorithm design techniques, we must divide the problem into two smaller subproblems, solve each of them recursively, and then meld the two partial solutions into one solution to the full problem. Whenever the merging takes less time than solving the two subproblems, we get and efficient algorithm.    
Divide-and-conquer is a design technique with many important algorithms to its credit, including mergesort, the fast Fourier transform, and Strassen's matrix multiplication algorithm.

__Recurrence Relations__

Many divide-and-conquer algorithms have time complexities that are naturally modeled by recurrence relations. Evaluating such recurrences is important to understanding when divide-and-conquer algorithms perform well, and provide and important tool for analysis in general.   
A recurrence relation is an equation that is defined in terms of itself. The Fibonacci numbers are described by the recurrence relation $F_n = F_{n-1} + F_{n-2}$.

__Divide-and-conquer Recurrences__

Divide-and-conquer algorithms tend to break a given problem into some number of smaller pieces (say $a$), each of which is of size $n/b$. Further they spend $f(n)$ time to combine these subproblem solutions into a complete result. Let $T(n)$ denote the worst-case time the algorithm takes to solve a problem of size $n$. Then $T(n)$ is given by the following recurrence relation: $T(n) = aT(n/b) + f(n)$

* _Sorting_ — $T(n) = 2T(n/2) + O(1)$ as we spend linear time merging two equally divided halves. $T(n) = O(n\lg{n})$
* _Binary Search_ — $T(n) = T(n/2) + O(1)$ as we spend constant time reducing the problem into half and not even bother ourself about merging. $T(n) = O(\lg{n})$
* _Fast Heap Construction_ — the $T(n) = 2T(n/2) + O(\lg{n})$ as we use the ```bubble_down``` method of heap construction to merge in logarithm time two equally divided halves of the tree. $T(n) = O(n)$
* _Matrix Multiplication_ — usually multiplying $n*n$ matrices takes $O(n^3)$. Strassen  divide-and-conquer method algorithm manipulates the product of seven $n/2*n/2$ matrix products to yield the product of two $n*n$ matrices thus $T(n) = 7T(n/2) + O(n^2)$ which by solving the recurrence evaluates to $O(n^{2.81})$.

__Solving Divide-and-Conquer Recurrences__

$T(n) = aT(n/b) + f(n)$ usually falls into three distinct cases:

* if $f(n) = O(n^{\log_b{a-e}})$ for some constant $e > 0$, then $T(n) = \Theta(n^{\log_b{a}})$
* if $f(n) = \Theta(n^{\log_b{a}})$, then $T(n) = \Theta(n^{\log_b{a}}\lg{n})$
* if $f(n) = \Omega(n^{\log_b{a+e}})$ for some constant $e > 0$, then if $af(n/b) \leq cf(n)$ for some $c<1$, then $T(n) = \Theta(n^{\log_b{a}})$

This _master theorem_ has Case 1 holding for heap construction and matrix multiplication, while Case 2 holds for mergesort and binary search. Case 3 generally arises for clumsier algorithms, where the cost of combining the subproblems dominates everything.

To understand the _master theorem_ we need to understand that a problem of size $n$ is decomposed into $a$ problems of size $n/b$. Each subproblem of size $k$ tales $O(f(k))$ time to deal with internally, between partitioning and merging. The total time for the algorithm is the sum of these internal costs, plus the overhead of building the recursion tree. The height of this tree is $h = \log_b{n}$ and the number of leaf nodes $a^h = a^{\log_b{n}}$, which simplifies to $n^{\log_b{a}}$.

* _Case 1: Too many leaves_ — if the number of leaf nodes outweighs the sum of the internal evaluation cost, the total running time is $O(n^{\log_b{a}})$.
* _Case 2: Equal work per level_ — as we move down the tree, each problem gets smaller but there are more of them to solve. If the sum of the internal evaluation costs at each level are equal, the total running time is the cost per level ($n^{\log_b{a}}$) time the number of levels ($\log_b{n}$), for a total running time of $O(n^{\log_b{a}}\lg{n})$.
* _Case 3: Too expensive a root_ — if the internal evaluation costs grow rapidly enough with $n$, then the most of the root evaluation may dominate. If so, the total running time is $O(f(n))$.

__The most interesting sorting algorithms that have not been discussed in this section include _shellsort_, which is a substantially more efficient version of insertion sort, and _radix sort_, an efficient algorithm for sorting strings.__



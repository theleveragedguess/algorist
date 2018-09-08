# Weighted Graph Algorithms

There is an alternate universe of problems for _weighted graphs_. Identifying the shortest path in such graphs proves more complicated thant breadth-first search in unweighted graphs, but opens the door to a wide range of applications.

## Minimum Spanning Trees

A _spanning tree_ of a graph $G=(V,E)$ is a subset of edges from $E$ forming a tree connecting all vertices of $V$. For edge-weighted graphs, we are particularly interested in the _minimum spanning tree_—the spanning tree whose sum of edge weights is a small as possible.   
Two different algorithms are presented below. Both demonstrate the optimality of certain greedy heuristics.

__Prim's Algorithm__   

Prim's minimum spanning tree algorithm starts from one vertex and grows the rest of the tree one edge at a time until all vertices are included.   
Greedy algorithms make the decision of what to do next by selecting the best local option from all available choices without regards to the global structure. Since we seek the tree of minimum weight, the natural greedy algorithm for minimum spanning tree repeatedly selects the smallest weight edge that will enlarge the number of vertices int the tree.   
Prim's algorithm clearly creates a spanning tree, because no cycle can be introduced by adding edges between tree and non-tree vertices. However, why should it be of minimum weight over all spanning trees?   
We use proof by contradiction. Suppose that there existed a graph $G$ for which Prim's algorithm did not return a minimum spanning tree. Since we are building the tree incrementally, this means that there must have been some particular instant where we went wrong. Before we inserted edge $(x,y)$, $T_{prim}$ consisted of a set of edges that was a subtree of some minimum spanning tree $T_{min}$, but choosing edge $(x,y)$ fatally took us away from a minimum spanning tree.   
But how could we have gone wrong? There must be a path $p$ from $x$ to $y$ in $T_{min}$. This path must use an edge $(v_1, v_2)$, where $v_1$ is in $T_{prim}$, but $v_2$ is not. This edge $(v_1, v_2)$ must have weight at least that of $(x,y)$, or Prim's algorithm would have selected it before $(x,y)$ when it had the chance. Inserting $(x,y)$ and deleting $(v_1, v_2)$ from $T_{min}$ leaves a spanning tree no larger than before, meaning that Prim's algorithm did not make a fatal mistake in selecting edge $(x,y)$. Therefore, by contradiction, Prim's algorithm must construct a minimum spanning tree.

Prim's algorithm grows the minimum spanning tree in stages, starting from a given vertex. At each iteration, we add one new vertex into the spanning tree. A greedy algorithm suffices for correctness: we always add the lowest-weight edge linking a vertex in the tree to a vertex on the outside.   
Our implementation keeps track of the cheapest edge linking every non-tree vertex in the tree. The cheapest such edge over all remaining non-tree vertices gets added in each iteration.

```c
void prim(graph *g, int start)
{
    int i;                  // counter
    edgenode *p;            // temporary pointer
    bool intree[MAXV+1];    // is the vertex in the tree yet
    int distance[MAXV+1];   // cost of adding to tree
    int v;                  // current vertex to process
    int w;                  // candidate next vertex
    int weight;             // edge weight
    int dist;               // best current distance from start

    for(i=1; i<=g->nvertices; i++)
    {
        intree[i] = FALSE;
        distance[i] = MAXINT;
        parent[i]= -1;
    }

    distance[start] = 0;
    v = start;

    while( intree[v] == FALSE
    {
        intree[v] = TRUE;
        p = v->edges[v];
        while(p != NULL) 
        {
            w = p->y;
            weight = p->weight;
            if ((distance[w] > weight) && (intree[w] == FALSE))
            {
                distance[w] = weight;
                parent[w] = v;
            }
            p = p->next;
        }

        v = 1;
        dist = MAXINT;
        for(i=1; i<=g->nvertices; i++){
            if((intree[i] == FALSE) && (dist > distance[i]))
            {
                dist = distance[i];
                v = i;
            }
        }
    }
}
```

Our implementation avoids the need to test all $m$ edges on each pass. It only considers the $\le n$ cheapest known edges represented in the ```parent``` array and the $\le n$ edges out of the new tree vertex $v$ to update ```parent```. By maintaining a Boolean flag along with each vertex to denote whether it is in the tree or not, we test whether the current edge joins a tree with a non-tree vertex in constant time.   
The result is an $O(n^2)$ implementation of Prim's algorithm, and a good illustration of the power of data structures to speed up algorithms. In fact, more sophisticated priority-queue data structures lead to an $O(m+n\lg{n})$ implementation, by making it faster to find the minimum cost edge to expand the tree at each iteration.   
The minimum spanning tree itself or its cost can be reconstructed in two different ways. The simplest method would be to augment this procedure with statements that print the edges as they are found or totals the weight of all selected edges. Alternately, the tree topology is encoded by the ```parent``` array, so it plus the original graph describe everything about the minimum spanning tree.


__Kruskal's Algorithm__    

Kruskal's algorithm is an alternate approach to finding minimum spanning trees that proves more efficient on sparse graphs. Like Prim's, Kruskal's algorithm is greedy. Unlike Prim's, it does not start with a particular vertex.   
Kruskal's algorithm builds up connected components of vertices, culminating in the minimum spanning tree. Initially, each vertex forms its own separate component in the tree-to-be. The algorithm repeatedly considers the lightest remaining edge and tests whether its two endpoints lie within the same connected component. If so, this edge will be discarded, because adding it would create a cycle in the tree-to-be. If the endpoint are in different components, we insert the edge and merge the two components into one.   
This algorithm adds $n-1$ edges without creating a cycle, so it clearly creates a spanning tree for any connected graph. But why must this be a _minimum_ spanning tree? Suppose it wasn't. As with the correctness proof of Prim's algorithm, there must be some graph on which it fails. In particular, there must be a single edge $(x,y)$ whose insertion first prevented the tree $T_{kruskal}$ from being a minimum spanning tree $T_{min}$. Inserting this edge $(x,y)$ into $T_{min}$ will create a cycle with the path from $x$ to $y$. Since $x$ and $y$ were in different components at the time of inserting $(x,y)$, at least one edge (say $(v_1, v_2)$) on this path would have been evaluated by Kruskal's algorithm later than $(x,y)$. But this means that $w(v_1, v_2) \ge w(x,y)$, so exchanging the two edges yields a tree of weight at most $T_{min}$. Therefore, we could not have made a fatal mistake in selecting $(x,y)$, and the correctness follows.    
A fast implementation of Kruskal's algorithm runs in $O(m\lg{m})$ time, which is faster than Prim's for sparse graphs. A clever data structure called _union-find_ allows to reach that time by making the component test in $O(\lg{n})$.

```c
void kruskal(graph *g)
{
    int i;                  // counter
    set_union s;            // set union data structure
    edge_pair e[MAXV+1];    // array of edges data structure
    bool weight_compare();

    set_union_init($s, g->nvertices);

    to_edge_array(g, e);    // sort edges by increasing cost
    qsort(&e, g->nedges, sizeof(edge_pair), weight_compare);

    for(i=0; i<(g->nedges); i++)
    {
        if( !same_component(s, e[i].x, e[i].y))
        {
            printf("edge (%d, %d) in MST\n", e[i].x, e[i].y);
            union_sets(&s, e[i].x, e[i].y);
        }
    }
}
```

__The Union_Find Data Structure__   

A _set partition_ is a partitioning of the elements of some universal set (say the integers $1$ to $n$) into a collection of disjointed subsets. Thus, each element must be in exactly one subset.   
The connected components in a graph can be represented as a set partition. For Kruskal's algorithm to run efficiently, we need a data structure that efficiently supports the following operations:
* _Same component$(v_1,v_2)$_
* _Merge component$(C_1,C_2)$_

The union-find data structure represents each subset as a "backwards" tree, with pointers from a node to its parent. 

```c
typedef struct  {
    int p[SET_SIZE+1];      // parent element
    int size[SET_SIZE+1];   // number of elements in subtree i
    int n;                  // number of elements in set
} set_union;
```

We implement our desired component operations in terms of two simpler operations, _union_ and _find_.
* _Find($i$)_— Find the root of the tree containing element $i$, by walking up the parent pointers until there is nowhere to go. Return the label of the root.
* _Union($i,j$)_— Link the root of one of the trees (say containing $i$) to the root of the tree containing the other (say $j$) so _find($i$)_ now equals _find($j$)_.

We seek to minimize the time it takes to execute _any_ sequence of unions and finds. Tree structure can be very unbalanced, so we must limit the height of our trees. To achieve that it is better to always merge the smaller tree to the bigger one when doing an _union_. Thus we augment the height of the smallest one by $1$ while preserving the height of the biggest one.

```c
void set_union_init(set_union $s, n)
{
    int i;  // counter

    for(i=1; i<=n; i++)
    {
        s->p[i] = i;
        s->size[i] = 1;
    }

    s->n = n;
}

int find(set_union *s, int x)
{
    if (s->p[x] == x)
        return x;
    else
        return find(s, s->p[x]);
}

int union_sets(set_union *s, int s1, int s2)
{
    int r1, r2; // root of sets
    
    r1 = find(s, s1);
    r2 = find(s, s2);

    if(r1 == r2) return;    // already in same set

    if(s->size[r1] >= s->size[r2])
    {
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[r2] = r1;
    }
    else
    {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[r1] = r2;  
    }
}

bool same_component(set_union *s, int s1, int s2)
{
    return find(s, s1) == find(s, s2);
}
```

We must double the number of nodes in the tree to get an extra unit of height, at most $\lg_{2}{n}$ doublings. Thus, we can do both unions and finds in $O(\log{n})$, good enough for Kruskal's algorithm. In fact, union_find can be done even faster...

__Variations on Minimum Spanning Tree__   

This minimum spanning tree algorithm has several interesting properties that help solves several closely related problems:
* _Maximum Spanning Trees_— It can be found by simply negating the weights of all edges and running Prim's algorithm. Not all algorithms adapt so easily to negative numbers.
* _Minimum Product Spanning Trees_— Assuming all edge weights are positive, we can replace the edge weight with their logarithms since $\lg{a*b} = \lg{a} + \lg{b}$.
* _Minimum Bottleneck Spanning Tree_— When we don't want an edge in the spanning tree to be greater than a certain value, we can just use the minimum spanning tree because the proof follows directly from the correctness of Kruskal's algorithm.

The minimum spanning tree of a graph is unique if all $m$ edges weights in the graph are distinct.   

There are two important variants of a minimum spanning tree that are not solvable with these techniques.
* _Steiner Tree_— When we can add extra intermediate vertices to serve as a shared junction.
* _Low-degree Spanning Tree_— Alternately, what if we want to find the minimum spanning tree where the highest degree node in the tree is small? The lowest max-degree tree possible would be a simple path, and have $n-2$ nodes of degree 2 with two endpoints of degree $1$. A path that visits each vertex once is called a _Hamiltonian path_.

## Shortest Paths


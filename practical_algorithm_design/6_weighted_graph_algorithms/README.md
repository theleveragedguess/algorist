# Weighted Graph Algorithms

There is an alternate universe of problems for _weighted graphs_. Identifying the shortest path in such graphs proves more complicated thant breadth-first search in unweighted graphs, but opens the door to a wide range of applications.

## Minimum Spanning Trees

A _spanning tree_ of a graph $G=(V,E)$ is a subset of edges from $E$ forming a tree connecting all vertices of $V$. For edge-weighted graphs, we are particularly interested in the _minimum spanning tree_—the spanning tree whose sum of edge weights is a small as possible.

Two different algorithms are presented below. Both demonstrate the optimality of certain greedy heuristics.

### Prim's Algorithm

Prim's minimum spanning tree algorithm starts from one vertex and grows the rest of the tree one edge at a time until all vertices are included.

Greedy algorithms make the decision of what to do next by selecting the best local option from all available choices without regards to the global structure. Since we seek the tree of minimum weight, the natural greedy algorithm for minimum spanning tree repeatedly selects the smallest weight edge that will enlarge the number of vertices in the tree.

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

Our implementation avoids the need to test all $m$ edges on each pass. It only considers the $\le n$ cheapest known edges represented in the `parent` array and the $\le n$ edges out of the new tree vertex $v$ to update `parent`. By maintaining a Boolean flag along with each vertex to denote whether it is in the tree or not, we test whether the current edge joins a tree with a non-tree vertex in constant time.

The result is an $O(n^2)$ implementation of Prim's algorithm, and a good illustration of the power of data structures to speed up algorithms. In fact, more sophisticated priority-queue data structures lead to an $O(m+n\lg{n})$ implementation, by making it faster to find the minimum cost edge to expand the tree at each iteration.

The minimum spanning tree itself or its cost can be reconstructed in two different ways. The simplest method would be to augment this procedure with statements that print the edges as they are found or totals the weight of all selected edges. Alternately, the tree topology is encoded by the `parent` array, so it plus the original graph describe everything about the minimum spanning tree.

### Kruskal's Algorithm

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

### The Union_Find Data Structure

A _set partition_ is a partitioning of the elements of some universal set (say the integers $1$ to $n$) into a collection of disjointed subsets. Thus, each element must be in exactly one subset.

The connected components in a graph can be represented as a set partition. For Kruskal's algorithm to run efficiently, we need a data structure that efficiently supports the following operations:

- _Same component$(v_1,v_2)$_
- _Merge component$(C_1,C_2)$_

The union-find data structure represents each subset as a "backwards" tree, with pointers from a node to its parent.

```c
typedef struct  {
    int p[SET_SIZE+1];      // parent element
    int size[SET_SIZE+1];   // number of elements in subtree i
    int n;                  // number of elements in set
} set_union;
```

We implement our desired component operations in terms of two simpler operations, _union_ and _find_.

- _Find($i$)_— Find the root of the tree containing element $i$, by walking up the parent pointers until there is nowhere to go. Return the label of the root.
- _Union($i,j$)_— Link the root of one of the trees (say containing $i$) to the root of the tree containing the other (say $j$) so _find($i$)_ now equals _find($j$)_.

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

We must double the number of nodes in the tree to get an extra unit of height, at most $\lg\_{2}{n}$ doublings. Thus, we can do both unions and finds in $O(\log{n})$, good enough for Kruskal's algorithm. In fact, union_find can be done even faster...

### Variations on Minimum Spanning Tree

This minimum spanning tree algorithm has several interesting properties that help solves several closely related problems:

- _Maximum Spanning Trees_— It can be found by simply negating the weights of all edges and running Prim's algorithm. Not all algorithms adapt so easily to negative numbers.
- _Minimum Product Spanning Trees_— Assuming all edge weights are positive, we can replace the edge weight with their logarithms since $\lg{a\*b} = \lg{a} + \lg{b}$.
- _Minimum Bottleneck Spanning Tree_— When we don't want an edge in the spanning tree to be greater than a certain value, we can just use the minimum spanning tree because the proof follows directly from the correctness of Kruskal's algorithm.

The minimum spanning tree of a graph is unique if all $m$ edges weights in the graph are distinct.

There are two important variants of a minimum spanning tree that are not solvable with these techniques.

- _Steiner Tree_— When we can add extra intermediate vertices to serve as a shared junction.
- _Low-degree Spanning Tree_— Alternately, what if we want to find the minimum spanning tree where the highest degree node in the tree is small? The lowest max-degree tree possible would be a simple path, and have $n-2$ nodes of degree 2 with two endpoints of degree $1$. A path that visits each vertex once is called a _Hamiltonian path_.

## Shortest Paths

A _path_ is a sequence of edges connecting two vertices and their multiplicity hints at why finding the _shortest path_ between two nodes is important and instructive, even in non-transportation application.

In a weighted graph, the shortest path is not necessarily the one with the fewer edges, as a faster and more complicated path can be constructed with more edges that have a minimal sum of weights.

We will present two distinct algorithms for finding the shortest paths in weighted graphs.

### Dijkstra’s Algorithm

Dijkstra’s algorithm is the method of choice for finding shortest paths in an edge—and/or vertex-weighted graph. Given a particular start vertex, it finds the shortest path from $s$ to every other vertex in the graph, including your desired destination $t$.

Suppose the shortest path from $s$ to $t$ in graph $G$ passes through a particular intermediate vertex $x$. Clearly, this path must contain the shortest path from $s$ to $x$ as its prefix, because if not, we could shorten our $s-to-t$ path by using the shorter $s-to-x$ prefix. Thus, we must compute the shortest path from $s$ to $x$ before we ﬁnd the path from $s$ to $t$.

Dijkstra’s algorithm proceeds in a series of rounds, where each round establishes the shortest path from $s$ to $some$ new vertex. Specifically, $x$ is the vertex that minimizes $dist(s,v_i)+w(v_i,x)$ over all unfinished $1 \leq i \leq n$, where $w(i,j)$ is the length of the edge from $i$ to $j$, and $dist(i,j)$ is the length of the shortest path between them.

This suggests a dynamic programming-like strategy. The shortest path from $s$ to itself is trivial unless there are negative weight edges, so $dist(s,s) = 0$. If $(s,y)$ is the lightest edge incident to $s$, then this implies that $dist(s,y)=w(s,y)$. Once we determine the shortest path to a node $x$, we check all the outgoing edges of $x$ to see whether there is a better path from $s$ to some unknown vertex through $x$.

The basic idea is very similar to Prim’s algorithm, the difference between both algorithms is how they rate the desirability of each outside vertex. In the minimum spanning tree problem, all we cared about was the weight of the next potential tree edge. In shortest path, we want to include the closest outside vertex (in shortest-path distance) to $s$. This is a function of both the new edge weight and the distance from $s$ to the tree vertex it is adjacent to.

```c
void dijkstra(graph *g, int start) // WAS prim(g,start)
{
    int i;                  // counter
    edgenode *p;            // temporary pointer
    bool intree[MAXV + 1];  // is the vertex in the tree yet?
    int distance[MAXV + 1]; // distance vertex is from start
    int v;                  // current vertex to process
    int w;                  // candidate next vertex
    int weight;             // edge weight
    int dist;               // best current distance from start

    for (i = 1; i <= g->nvertices; i++)
    {
        intree[i] = FALSE;
        distance[i] = MAXINT;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    while (intree[v] == FALSE)
    {
        intree[v] = TRUE;
        p = g->edges[v];
        while (p != NULL)
        {
            w = p->y;
            weight = p->weight;
            /* CHANGED */ if (distance[w] > (distance[v] + weight))
            {
                /* CHANGED */ distance[w] = distance[v] + weight;
                /* CHANGED */ parent[w] = v;
            }
            p = p->next;
        }
        v = 1;
        dist = MAXINT;
        for (i = 1; i <= g->nvertices; i++)
            if ((intree[i] == FALSE) && (dist > distance[i]))
            {
                dist = distance[i];
                v = i;
            }
    }
}
```

This algorithm finds more than just the shortest path from $s$ to $t$. It finds the shortest path from $s$ to all other vertices. This defines a shortest path spanning tree rooted in $s$. For undirected graphs, this would be the breadth-first search tree, but in general it provides the shortest path from s to all other vertices.

Dijkstra's algorithm then yields a complexity of $O(n^2)$.

Dijkstra works correctly only on graphs without negative-cost edge, however most applications do not feature negative-weight edges, making this discussion academic.

### All-Pairs Shortest Path

We could solve _all-pairs shortest path_ by calling Dijkstra’s algorithm from each of the $n$ possible starting vertices. But Floyd’s all-pairs shortest-path algorithm is a slick way to construct this $n\*n$ distance matrix from the original weight matrix of the graph.

Floyd’s algorithm is best employed on an adjacency matrix data structure, which is no extravagance since we must store all $n^2$ pairwise distances anyway.

```c
typedef struct
{
    int weight[MAXV + 1][MAXV + 1]; // adjacency/weight info
    int nvertices;                  // number of vertices in graph
} adjacency_matrix;
```

We should initialize each non-edge to `MAXINT`. This way we can both test whether it is present and automatically ignore it in shortest-path computations, since only real edges will be used.

The Floyd-Warshall algorithm starts by numbering the vertices of the graph from $1$ to $n$. We use these numbers not to label the vertices, but to order them. Define $W[i,j]^k$ to be the length of the shortest path from $i$ to $j$ using only vertices numbered from $1,2,...,k$ as possible intermediate vertices.

We will perform $n$ iterations, where the $k$th iteration allows only the first $k$ vertices as possible intermediate steps on the path between each pair of vertices $x$ and $y$.

At each iteration, allowing the $kth$ vertex as a stop helps only if there is a short path that goes through $k$, so
$W[i,j]^k = min(W[i,j]^{k−1},W[i,k]^{k−1} + W[k,j]^{k−1})$

```c
void floyd(adjacency_matrix *g)
{
    int i, j;      // dimension counters
    int k;         // intermediate vertex counter
    int through_k; // distance through vertex k

    for (k = 1; k <= g->nvertices; k++)
        for (i = 1; i <= g->nvertices; i++)
            for (j = 1; j <= g->nvertices; j++)
            {
                through_k = g->weight[i][k] + g->weight[k][j];
                if (through_k < g->weight[i][j])
                    g->weight[i][j] = through_k;
            }
}
```

The Floyd-Warshall all-pairs shortest path runs in $O(n^3)$ time, which is asymptotically no better than $n$ calls to Dijkstra’s algorithm. However, the loops are so tight and the program so short that it runs better in practice. It is notable as one of the rare graph algorithms that work better on adjacency matrices than adjacency lists.

#### Transitive Closure

Floyd’s algorithm has another important application, that of computing _transitive closure_. In analyzing a directed graph, we are often interested in which vertices are reachable from a given node.

The vertices reachable from any single node can be computed using breadth-first or depth-first searches. But the whole batch can be computed using an all-pairs shortest-path. If the shortest path from $i$ to $j$ remains `MAXINT` after running Floyd’s algorithm, you can be sure no directed path exists from $i$ to $j$.

## Network Flows and Bipartite Matching

Edge-weighted graphs can be interpreted as a network of pipes, where the weight of edge $(i,j)$ determines the capacity of the pipe. The _network flow problem_ asks for the maximum amount of flow which can be sent from vertices $s$ to $t$ in a given weighted graph $G$ while respecting the maximum capacities of each pipe.

### Bipartite Matching

While the network flow problem is of independent interest, its primary importance is in to solving other important graph problems. A classic example is bipartite matching. A _matching_ in a graph $G =(V,E)$ is a subset of edges $E' \subset E$ such that no two edges of $E'$ share a vertex. A matching pairs oﬀ certain vertices such that every vertex is in, at most, one such pair.

Graph $G$ is _bipartite_ or _two-colorable_ if the vertices can be divided into two sets, $L$ and $R$, such that all edges in $G$ have one vertex in $L$ and one vertex in $R$.

The largest bipartite matching can be readily found using network flow. Create a _source_ node $s$ that is connected to every vertex in $L$ by an edge of weight $1$. Create a _sink_ node $t$ and connect it to every vertex in $R$ by an edge of weight $1$. Finally, assign each edge in the bipartite graph $G$ a weight of $1$. Now, the maximum possible flow from $s$ to $t$ defines the largest matching in $G$. Certainly we can find a flow as large as the matching by using only the matching edges and their source-to-sink connections. Further, there can be no greater possible flow. How can we ever hope to get more than one flow unit through any vertex?

#### Computing Network Flows

Traditional network flow algorithms are based on the idea of _augmenting paths_, and repeatedly finding a path of positive capacity from _s_ to _t_ and adding it to the flow. It can be shown that the flow through a network is optimal if and only if it contains no augmenting path. Since each augmentation adds to the flow, we must eventually find the global maximum.
The key structure is the _residual flow graph_, denoted as $R(G,f)$, where $G$ is the input graph and $f$ is the current flow through $G$. This directed, edge-weighted $R(G,f)$ contains the same vertices as $G$. For each edge $(i,j)$ in $G$ with capacity $c(i,j)$ and ﬂow $f(i,j)$, $R(G,f)$ may contain two edges:

- $(i)$ an edge $(i,j)$ with weight $c(i,j)−f(i,j)$, if $c(i,j)−f(i,j) > 0$
- $(ii)$ an edge $(j,i)$ with weight $f(i,j)$, if $f(i,j) > 0$

The presence of edge $(i,j)$ in the residual graph indicates that positive flow can be pushed from $i$ to $j$. The weight of the edge gives the exact amount that can be pushed. A path in the residual flow graph from $s$ to $t$ implies that more flow can be pushed from $s$ to $t$ and the minimum edge weight on this path defines the amount of extra flow that can be pushed.

**The maximum ﬂow from s to t always equals the weight of the minimum s-t cut. Thus, flow algorithms can be used to solve general edge and vertex connectivity problems in graphs.**

For each edge in the residual flow graph, we must keep track of both the amount of ﬂow currently going through the edge, as well as its remaining residual capacity. Thus, we must modify our edge structure to accommodate the extra fields:

```c
typedef struct
{
    int v;                 // neighboring vertex
    int capacity;          // capacity of edge
    int flow;              // flow through edge
    int residual;          // residual capacity of edge
    struct edgenode *next; // next edge in list
} edgenode;

void netflow(flow_graph *g, int source, int sink)
{
    int volume; // weight of the augmenting path

    add_residual_edges(g);

    initialize_search(g);
    bfs(g, source);
    volume = path_volume(g, source, sink, parent);

    while (volume > 0)
    {
        augment_path(g, source, sink, parent, volume);
        initialize_search(g);
        bfs(g, source);
        volume = path_volume(g, source, sink, parent);
    }
}

bool valid_edge(edgenode *e)
{
    if (e->residual > 0)
        return TRUE;
    else
        return FALSE;
}

int path_volume(flow_graph *g, int start, int end, int parents[])
{
    edgenode *e; // edge in question
    edgenode *find_edge();

    if (parents[end] == -1)
        return 0;

    e = find_edge(g, parents[end], end);

    if (start == parents[end])
        return e->residual;
    else
        return min(
            path_volume(g, start, parents[end], parents),
            e->residual
        );
}

edgenode *find_edge(flow_graph *g, int x, int y)
{
    edgenode *p;  // temporary pointer

    p = g->edges[x];
    while (p != NULL)
    {
        if (p->v == y)
            return p;
        p = p->next;
    }

    return NULL;
}


augment_path(flow_graph *g, int start, int end, int parents[], int volume)
{
    edgenode *e; // edge in question
    edgenode *find_edge();

    if (start == end)
        return;

    e = find_edge(g, parents[end], end);
    e->flow += volume;
    e->residual -= volume;

    e = find_edge(g, end, parents[end]);
    e->residual += volume;

    augment_path(g, start, parents[end], parents, volume);
}
```

The augmenting path algorithm above eventually converges on the the optimal solution. However each augmenting path may add only a little to the total ﬂow, so, in principle, the algorithm might take an arbitrarily long time to converge.

However, always selecting a shortest unweighted augmenting path guarantees that $O(n^3)$ augmentations suffice for optimization. In fact, this is what is implemented above, since a breadth-first search from the source is used to ﬁnd the next augmenting path.

## Design Graphs not Algorithms

Proper modeling is the key to making effective use of graph algorithms. We have defined several graph properties, and developed algorithms for computing them.

These classical graph problems provide a framework for modeling most applications. The secret is learning to design graphs, not algorithms. We have already seen a few instances of this idea:

- The maximum spanning tree can be found by negating the edge weights of the input graph $G$ and using a minimum spanning tree algorithm on the result. The most negative weight spanning tree will define the maximum weight tree in $G$.
- To solve bipartite matching, we constructed a special network ﬂow graph such that the maximum flow corresponds to a maximum cardinality matching.

**Designing novel graph algorithms is very hard, so don’t do it. Instead, try to design graphs that enable you to use classical algorithms to model your problem.**

# Graph Traversal

Graph are one of the unifying themes of computer science--an abstract representation that describes the organization of transportation systems, human interactions, and telecommunication networks. That so many different structures can be modeled using a single formalism is a source of great power to the educated programmer.   
More precisely, a graph $G=(V,E)$ consists of a set of _vertices $V$_ together with a set $E$ of vertex pairs or $edges$. Graphs are important because they can be used to represent essentially _any_ relationship.

The key to solving many algorithmic problems is to think of them in terms of graphs. Graph theory provides a language for talking about the properties of relationships, and it is amazing how often messy applied problems have a simple description and solution in terms of classical graph properties.   
Designing truly novel graph algorithms is a very difficult tasks. The key to using graph algorithms effectively in applications lies in correctly modeling your problem so you can take advantage of existing algorithms.

## Flavors of Graphs

A graph $G=(V,E)$ is defined on a set of _vertices $V$_, and contains a set of _edges $E$_.

* _Undirected vs. Directed_, a $G=(V,E)$ is _undirected_ if _edge_ $(x,y) \in E$ implies that $(y,x)$ is also in $E$. If not we say that the graph is _directed_.
* _Weighted vs. Unweighted_, each edge (or vertex) in a _weighted_ graph $G$ is assigned a numerical value, or weight. In _unweighted_ graphs, there is not cost distinction between various edges and vertices.
* _Simple vs. Non_simple_, certain types of edges complicate the task of working with graphs. A _self-loop_ is an edge $(x,x)$ involving only one vertex. An $(x,y)$ is a _multiedge_ if it occurs more thant once in the graph. _Simple_ graphs have none of those, while _non-simple_ graphs won't shy away in boasting some or many of them.
* _Sparse vs Dense_, Graphs are _sparse_ when only a small fraction of the possible vertex paris actually have edges defined between them. Graphs where a large fraction of the vertex pairs define edges are called _dense_. Typically dense graphs have a quadratic number of edges, while sparse graphs are linear in size.
* _Cyclic vs. Acyclic_, an _acyclic_ graph does not contain any cycles, while _cyclic_ graphs will do.
* _Embedded vs. Topological_, a graph is _embedded_ if the vertices and edges are assigned geometric positions. Thus, any drawing of a graph is an _embedding, which may or may not have algorithmic significance. _Topological_ graphs are built and dependant of one embedding.
* Implicit vs. Explicit_, certain graphs are not explicitly constructed and then traversed, but built as we use them, by querying each vertex to construct what he needs to construct so that we proceed. Those are called _implicit_ graphs, as opposite to _Explicit_ graphs that are well built and fully known and stored.
* Labeled vs. Unlabeled_, each vertex is assigned a unique name or identifier in a _labeled_ graph to distinguish it from all other vertices. In _unlabeled_ graphs, no such distinctions have been made.

__Graphs can be used to model a wide variety of structures and relationships. Graph-theoretic terminology gives us a language to talk about them.__

## Data Structures for Graphs

Selecting the right graph data structure can have an enormous impact on performance. Your two basic choices are adjacency matrices and adjacency lists. We assume the graph $G=(V,E)$ contains $n$ vertices and $m$ edges.

* _Adjacency Matrix_: We can represent $G$ using $n * n$ matrix $M$, where element $M[i,i] = 1$ if $(i,j)$ is an edge of $G$, and $0$ if it isn't. It uses excessive space for graphs with many vertices but allows a fast answer for the question "is $(i,i)$ in $G$?", and rapid updates for edge insertion and deletion.
* _Adjacency Lists_: We can more efficiently represent sparse graphs by using linked lists to store the neighbors adjacent to each vertex. Adjacency lists make it harder to verify whether a given edge $(i,j)$ is in $G$. However, it is surprisingly easy to design graph algorithms that avoid any need for such queries.

__Adjacency Lists are the right data structures for most applications of graphs.__

```c
#define MAXV 1000 // maximum number of vertices

typedef struct {
    int y;                  // adjacency info
    int weight;             // edge of weight, if any
    struct edgenode *next;  // next edge in the list
} edgenode

typedef struct {
    edgenode *edges[MAXV+1];    // adjacency info
    int degree[MAXV+1];          // outdegree of each vertex
    int nvertices;              // number of vertices in graph
    int nedges                  // number of edges in graph
    bool directed               // is the graph directed
} graph;

void initialize_graph(graph *g, bool directed)
{
    int i; // counter
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for(i=1; i<=MAXV; i++) g->degree[i] = 0;
    for(i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void read_graph(graph *g, bool directed)
{
    int i;      // counter
    int m;      // number of edges
    int x,y;    // vertices in edge (x,y)

    initialize_graph(g, directed);

    scanf("%d %d", &(g->nvertices), &m);

    for(i=1; i<=m; i++)
    {
        scanf("%d %d", &x, &y);
        insert_edge(g, x, y, directed);
    }
}

void insert_edge(graph *g, int x, int y, bool directed)
{
    edgenode *p;  // temporary pointer

    p = malloc(sizeof(edgenode));  // allocate edgenode storage

    p->weight = NULL;
    p->y = y;
    p->next = g->edge[x];

    g->edges[x] = p;  // insert at head of list

    g->degree[x] ++;

    if(directed == FALSE)
        insert_edge(g, y, x, TRUE);
    else
        g->nedges ++;
}

void print_graph(graph *g)
{
    int i;
    edgenode *p;  // counter
    
    for(i=1; i<=g->nvertices; i++)
    {
        printf("%d: ", i);
        p = g->edges[i];
        while(p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}
```

It is a good idea to use a well-designed graph data type as a model for building your own, or even better as the foundation of your application. LEDA or Boost are recommended choices as the best-designed general-purpose graph data structures available.

## Traversing a Graph

Perhaps the most fundamental graph problem is to visit every edge and vertex in a graph in a systematic way. Indeed, all the basic bookkeeping operations on graphs are applications of graph traversal.   
The key idea behind graph traversal is to mark each vertex when we first visit it and keep track of what we have not yet completely explored. Although bread crumbs or unraveled threads have been used to mark visited places in fairy-tale mazes, we will rely on Boolean flags or enumerated types.   
Each vertex will exist in one of three ordered states: from _undiscovered_, then _discovered_, to _processed_.   
Initially only the start vertex $v$ is considered to be discovered. To completely explore a vertex $v$, we must evaluate each edge leaving $v$. If an edge goes to an undiscovered vertex $x$, we mark $x$ _discovered_ and add it to the list of work to do. We ignore an edge that goes to a _processed_ vertex, because further contemplation will tell us nothing of the graph. We can also ignore any edge going to a _discovered_ but not _processed_ vertex, because the destination already resides on the list of vertices to process.    
Each undirected edge will be considered exactly twice, once when each of its endpoint is explored. Directed edges will be considered only once, when exploring the source vertex. Every edge and vertex in the connected component must eventually be visited.

## Breadth-First Search

In a breadth-first search of an undirected graph, we assign a direction to each edge, from the discoverer $u$ to the discovered $v$. We thus denote $u$ to be the parent of $v$. Since each node has exactly one parent, except for the root, this defines a tree on the vertices of the graph. This property makes breadth-first search very useful in shortest path problems.   
The graph edges that do not appear in the breadth-first search tree also have special properties. For undirected graphs, nontree edges can point only to vertices on the same level as the parent vertex, or to vertices on the level directly below the parent. These properties follow easily from the fact that each path in the tree must be the shortest path in the graph. For a directed graph, a back-pointing edge $(u,v)$ can exist whenever $v$ lies closer to the root than $u$ does.

__Implementation__   

```c
bool processed[MAXV+1];     // Which vertices have been processed
bool discovered[MAXV+1];    // Which vertices have been found
int parent[MAXV+1];         // discovery relation
void initialize_search(graph *g)
{
    int i; // counter
    for(i=1; i<=g->nvertices; i++)
    {
        processed[i] = discovered[i] = FALSE;
        parent[i] = -1;
    }
}

void bfs(graph *g, int start)
{
    queue q;        // queue of vertices to visit
    int v;          // current vertex
    int y;          // successor vertex
    edgenode *p;    // temporary pointer

    init_queue(&q);
    enqueue(&q, start);
    discovered[start] = TRUE;

    while(empty_queue(&q) == FALSE)
    {
        v = dequeue(&q);
        process_vertex_early(v);
        processed[v]= TRUE;
        p = g->edges[v];
        while(p != NULL)
        {
            y = p->y;
            if((processed[y] == FALSE) || g->directed)
                process_edge(v, y);
            if(discovered[y] == FALSE) 
            {
                enqueue(&q, y);
                discovered[y] = TRUE;
                parent[y] = v;
            }
            p = p->next;
        }
        process_vertex_late(v);
    }
}
```

__Exploiting Traversal__   

The exact behavior of ```bfs``` depends upon the functions ```process_vertex_early()```, ```process_vertex_late()``` and ```process_edge()```. Through these functions, we can customize what the traversal does as it makes its official visit to each edge and each vertex.

```c
void process_vertex_late(int v)
{
}

void process_vertex_early(int v)
{
    printf("processed vertex %d\n", v);
}

void process_edge(int x, int y)
{
    printf("processed edge (%d, %d)\n", x, y);
}
```

Different algorithms perform different actions on vertices or edges as they are encountered. These functions give us the freedom to easily customize our response.

__Finding Paths__   

Every vertex is discovered during the course of traversal, so except for the root every node has a parent. The parent relation defines a tree of discovery with the initial search node as the root of the tree.   
Because vertices are discovered in order of increasing distance from the root, this tree has a very important property. The unique tree path from the root to each node $x \in V$ uses the smallest number of edges possible on any root-to-$x$ path in the graph.   
We can reconstruct this path by following the chain of ancestors from $x$ to the root. Note that we have to work backward. Since this is the reverse of how we normally want the path, we can let recursion reverse it for us.

```c
void find_path(int start, int end, int parents[])
{
    if((start == end) || (end == -1))
        printf("\n%d", start);
    else 
    {
        find_path(start, parents[end], parents);
        printf(" %d", end);
    }
}
```

There are two points to remember when using breadth-first search to find a shortest path from $x$ to $y$: First, the shortest path tree is only useful if BFS was performed with x as the root of the search. Second, BFS gives the shortest path only if the graph is unweighted.

## Applications of Breadth-First Search

Most elementary graphs algorithms make one or two traversals of the graph while we update our knowledge of the graph. Properly implemented using adjacency lists, any such algorithm is destined to be linear, since BFS runs in $O(n=m)$ time on both directed and undirected graphs.   

__Connected Components__   

The "six degrees of separation" theory argues that there is always a short path linking every two people in the world. We say that a graph is _connected_ if there is a path between any two vertices.   
A _connected component_ of an undirected graph is a maximal set of vertices such that there is a path between every pair of vertices.   
Connected components can be found using breadth-first search, since the vertex order does not matter. We start from the first vertex. Anything we discover during this search must be part of the same connected component. We then repeat the search from any undiscovered vertex to define the next component, and so on until all vertices have been found.

```c
void connected_components(graph *g)
{
    int c;  // component number
    int i;  // counter

    initialize_search(g);

    c = 0;
    for(i=1; i<=g->nvertices; i++)
    {
        if(discovered[i] == FALSE){
            c = c+1;
            printf("Component %d:", c);
            bfs(g, i);
            printf("\n");
        }
    }
}

void process_vertex_early(int v)
{
    printf(" %d", v);
}

void process_edge(int x, int y)
{
}
```

__Two-Coloring Graphs__   

The _vertex-coloring_ problem seeks to assign a label (or color) to each vertex of a graph such that no edge links any two vertices of the same color. The goal is to use as few colors as possible.   
A graph is _bipartite_ if it can be colored without conflicts while using only two colors. Bipartite graphs are important because they arise naturally in many applications. Consider the "had-sex-with" graph in a heterosexual world.   
We can augment breadth-first search so that whenever we discover a new vertex, we color it the opposite of its parent. We check whether any nondiscovery edge links two vertices of the same color. Such a conflict means that the graph cannot be two-colored. Otherwise, we will have constructed a proper two-coloring whenever we terminate without conflitct.

```c
void twocolor(graph *g)
{
    int i;  // counter
    for(i=1; i<=(g->nvertices); i++)
        color[i] = UNCOLORED;

    bipartite = TRUE;

    initialize_search(&g);

    for(i=1; i<=(g->nvertices); i++)
    {
        if(discovered[i] == FALSE
        {
            color[i] = WHITE;
            bfs(g, i);
        }
    }
}

void process_edge(int x, int y)
{
    if(color[x] == color[y])
    {
        bipartite = FALSE;
        printf("Warning: not bipartite due to (%d, %d)\n", x, y);
    }

    color[y] = complement(color[x]);
}

int complement(int color)
{
    if(color == WHITE) return BLACK;
    if(color == BLACK) return WHITE;

    return UNCOLORED;
}
```

__Breadth-first and depth-first searches provide mechanisms to visit each edge and vertex of the graph. They prove the basis of most simple, efficient graph algorithms.__   

## Depth-First Search

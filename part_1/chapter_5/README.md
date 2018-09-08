# Graph Traversal

Graphs are one of the unifying themes of computer science— an abstract representation that describes the organization of transportation systems, human interactions, and telecommunication networks. That so many different structures can be modeled using a single formalism is a source of great power to the educated programmer.   
More precisely, a graph $G=(V,E)$ consists of a set of _vertices $V$_ together with a set $E$ of vertex pairs or _edges_. Graphs are important because they can be used to represent essentially _any_ relationship.   
The key to solving many algorithmic problems is to think of them in terms of graphs. Graph theory provides a language for talking about the properties of relationships, and it is amazing how often messy applied problems have a simple description and solution in terms of classical graph properties.   
Designing truly novel graph algorithms is a very difficult tasks. The key to using graph algorithms effectively in applications lies in correctly modeling your problem so you can take advantage of existing algorithms.

## Flavors of Graphs

A graph $G=(V,E)$ is defined on a set of _vertices $V$_, and contains a set of _edges $E$_.

* _Undirected vs. Directed_—  A $G=(V,E)$ is _undirected_ if _edge_ $(x,y) \in E$ implies that $(y,x)$ is also in $E$. If not we say that the graph is _directed_.
* _Weighted vs. Unweighted_—  Each edge (or vertex) in a _weighted_ graph $G$ is assigned a numerical value, or weight. In _unweighted_ graphs, there is not cost distinction between various edges and vertices.
* _Simple vs. Non-simple_—  Certain types of edges complicate the task of working with graphs. A _self-loop_ is an edge $(x,x)$ involving only one vertex. An $(x,y)$ is a _multiedge_ if it occurs more thant once in the graph. _Simple_ graphs have none of those, while _non-simple_ graphs won't shy away in boasting some or many of them.
* _Sparse vs Dense_—  Graphs are _sparse_ when only a small fraction of the possible vertex pairs actually have edges defined between them. Graphs where a large fraction of the vertex pairs define edges are called _dense_. Typically dense graphs have a quadratic number of edges, while sparse graphs are linear in size.
* _Cyclic vs. Acyclic_—  An _acyclic_ graph does not contain any cycles, while _cyclic_ graphs will do.
* _Embedded vs. Topological_, a graph is _embedded_ if the vertices and edges are assigned geometric positions. Thus, any drawing of a graph is an _embedding_, which may or may not have algorithmic significance. _Topological_ graphs are built and dependant of one embedding.
* _Implicit vs. Explicit_—  Certain graphs are not explicitly constructed and then traversed, but built as we use them, by querying each vertex to construct what he needs to construct so that we proceed. Those are called _implicit_ graphs, as opposite to _explicit_ graphs that are well built and fully known and stored.
* _Labeled vs. Unlabeled_—  Each vertex is assigned a unique name or identifier in a _labeled_ graph to distinguish it from all other vertices. In _unlabeled_ graphs, no such distinctions have been made.

__Graphs can be used to model a wide variety of structures and relationships. Graph-theoretic terminology gives us a language to talk about them.__

## Data Structures for Graphs

Selecting the right graph data structure can have an enormous impact on performance. Your two basic choices are adjacency matrices and adjacency lists. We assume the graph $G=(V,E)$ contains $n$ vertices and $m$ edges.

* _Adjacency Matrix_—  We can represent $G$ using $n * n$ matrix $M$, where element $M[i,i] = 1$ if $(i,j)$ is an edge of $G$, and $0$ if it isn't. It uses excessive space for graphs with many vertices but allows a fast answer for the question "is $(i,j)$ in $G$ ?", and rapid updates for edge insertion and deletion.
* _Adjacency Lists_—  We can more efficiently represent sparse graphs by using linked lists to store the neighbors adjacent to each vertex. Adjacency lists make it harder to verify whether a given edge $(i,j)$ is in $G$. However, it is surprisingly easy to design graph algorithms that avoid any need for such queries.

__Adjacency Lists are the right data structures for most applications of graphs.__

```c
#define MAXV 1000 // maximum number of vertices

typedef struct {
    int y;                  // adjacency info
    int weight;             // weight of edge, if any
    struct edgenode *next;  // next edge in the list
} edgenode

typedef struct {
    edgenode *edges[MAXV+1];    // adjacency info
    int degree[MAXV+1];         // outdegree of each vertex
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
    int x, y;    // vertices in edge (x,y)

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
The graph edges that do not appear in the breadth-first search tree also have special properties. For undirected graphs, non-tree edges can point only to vertices on the same level as the parent vertex, or to vertices on the level directly below the parent. These properties follow easily from the fact that each path in the tree must be the shortest path in the graph. For a directed graph, a back-pointing edge $(u,v)$ can exist whenever $v$ lies closer to the root than $u$ does.

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
We can reconstruct this path by following the chain of ancestors from $x$ to the root. Note that we have to work backward. Since this is the reverse of how we normally want the path, we can let recursion reverses it for us.

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

There are two points to remember when using breadth-first search to find a shortest path from $x$ to $y$. Firstly, the shortest path tree is only useful if BFS was performed with x as the root of the search. Secondly, BFS gives the shortest path only if the graph is unweighted.

## Applications of Breadth-First Search

Most elementary graphs algorithms make one or two traversals of the graph while we update our knowledge of the graph. Properly implemented using adjacency lists, any such algorithm is destined to be linear, since BFS runs in $O(n+m)$ time on both directed and undirected graphs.   

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

The _vertex-coloring_ problem seeks to assign a label (or color) to each vertex of a graph such that no edge links any two vertices of the same label. The goal is to use as few labels as possible.   
A graph is _bipartite_ if it can be colored without conflicts while using only two colors. Bipartite graphs are important because they arise naturally in many applications. Consider the "had-sex-with" graph in a heterosexual world.   
We can augment breadth-first search so that whenever we discover a new vertex, we color it the opposite of its parent. We check whether any nondiscovery edge links two vertices of the same color. Such a conflict means that the graph cannot be two-colored. Otherwise, we will have constructed a proper two-coloring whenever we terminate without conflict.

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
        if(discovered[i] == FALSE)
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

After _breadth-first search_ (BFS), _depth-first search_ (DFS) is the other primary graph traversal algorithm. For certain problems, their difference is crucial.   
The difference between BFS and DFS results is in the order in which they explore vertices. This order depends completely upon the container data structure used to store the _discovered_ but not _processed_ vertices.   
* _Queue_ — FIFO let's us explore the oldest vertices first thus defining a breadth-first search.
* _Stack_ — LIFO let's us explore the vertices by lurching a path, prioritizing the newest _undiscovered_ vertices first, thus defining a depth-first search.

Our implementation of ```dfs``` maintains a notion of traversal _time_ for each vertex. Our ```time``` clock ticks each time we enter or exit any vertex. We keep track of the _entry_ and _exit_ times for each vertex. Depth-first search has a neat recursive implementation, which eliminates the need to explicitly use a stack.   
The time intervals have an interesting and useful properties with respect to depth-first search:
* _Who is an ancestor?_ — An ancestor $x$ can't be born after one of its descendants. We enter such descendant $y$ after entering $x$ and leave it before leaving $x$. Thus the time interval of $y$ must be properly nested withing ancestor $x$.
* _How many descendants?_ — The difference between the exit and entry times for $v$ tells us how many descendants $v$ has in the DFS tree. The clocks gets incremented on each vertex entry and vertex exit, so half the time difference denotes the number of descendants of $v$.

The other important property of a depth-first search is that it partitions the edges of an undirected graph into exactly two classes: _tree edges_ and _back edges_. The tree edges discover new vertices. Back edges are those whose other endpoint is an ancestor of the vertex being expanded. Why can't edges go to a brother or cousin node instead of an ancestor? All nodes reachable from a given vertex $v$ are expanded before we finish the traversal from $v$, such topologies are impossible for undirected graphs.

__Implementation__    

```c
void dfs(graph *g, int v)
{
    edgenode *p;    // temporary pointer
    int y;          // successor vertex

    if(finished) return; // allow for search termination

    discovered[v] = TRUE;
    time = time + 1;
    entry_time[v] = time;

    process_vertex_early(v);

    p = p->edges[v];
    while(p != NULL)
    {
        y = p->y;
        if(discovered[y] == FALSE)
        {
            parent[y] = v;
            process_edge(v, y);
            dfs(g, y);
        }
        else if((!processed[y] && (parent[y] != y)) || (g->directed))
            process_edge(v, y);

        if(finished) return;

        p = p->next;
    }

    process_vertex_late(v);

    time = time + 1;
    exit_time[v] = time;

    processed[v] = TRUE;
}
```

Depth-first search use essentially the same idea as _backtracking_. Both involve exhaustively searching all possibilities by advancing if it is possible, and backing up as soon as there is no unexplored possibility for further advancement. Both are most easily understood as recursive algorithms.   

__DFS organizes vertices by entry/exit times, and edges into tree and back edges. This organization is what gives DFS its real power.__


## Applications of Depth-first Search

The correctness of a DFS-based algorithm depends upon specifics of exactly _when_ we process the edges and vertices.

__Finding Cycles__   

Back edges are the key to finding a cycle in an undirected graph. If there is no back edge, all edges are tree edges, and no cycle exists in a tree. But _any_ back edge going from $x$ to an ancestor $y$ creates a cycle with the tree path from $y$ to $x$. Such a cycle is easy to find using ```dfs```:

```c
void process_edge(int x, int y)
{
    if(discovered[y] && (parent[x] != y)) // found back edge
    {
        printf("Cycle from %d to %d:", y, x);
        find_path(y, x, parent);
        printf("\n\b");
        finished = TRUE;
    }
}
```

The correctness of this cycle detection algorithm depends upon processing each undirected edge exactly once. Otherwise, a spurious two-vertex cycle $(x, y, x)$ could be composed from the two traversals of any single undirected edges.

__Articulation Vertices__    

An _articulation vertex_ or _cut-node_ is a single vertex whose deletion disconnects a connected component of the graph. Any Graph that contains an articulation vertex is inherently fragile.   
In general, the _connectivity_ of a graph is the smallest number of vertices whose deletion will disconnect the graph. The connectivity is $1$ if the graph has an articulation vertex. More robust graphs without such a vertex are said to be _biconnected_.   
Testing for articulation vertices by brute force is easy, however there is a clever linear-time algorithm that tests all the vertices of a connected graph using a single depth-first search.   
If a DFS tree represented the entirety of the graph, all internal (nonleaf) nodes would be articulation vertices. If the root has only one child it will behave as a leaf in this procedure.   
General graphs are more complex than trees. But a depth-first search of a general graph partitions the edges into tree edges and back edges. The back edge from $x$ to $y$ ensures that none of the vertices on the tree path between $x$ and $y$ can be articulation vertices.    
Finding articulation vertices requires maintaining the extent to which back edges link chunks of the DFS tree bck to ancestor nodes.    
```c
int reachable_ancestor[MAXV+1]; // earliest reachable ancestor of v
int tree_out_degree[MAXV+1];    // DFS tree outdegree of v

void process_vertex_early(int v)
{
    reachable_ancestor[v] = v;
}

void process_edge(int x, int y)
{
    int class; // edge class

    class = edge_classification(x, y);

    if(class == TREE)
        tree_out_degree[x] = tree_out_degree[x] + 1;
    
    if(     class == BACK 
        &&  parent[x] != y
        &&  entry_time[y] < entry_time[ reachable_ancestor[x] ])
        reachable_ancestor[x] = y;
}
```

The key issue is determining how the reachability relation impacts whether vertex $v$ is an articulation vertex. There are three cases:
* _Root cut-nodes_ — If the root of the DFS tree has two or more children, it must be an articulation vertex.
* _Bridge cut-nodes_ — If the earliest reachable vertex from $v$ is $v$, then deleting the single edge $(parent[v], v)$ disconnects the graph. Vertex $v$ is also an articulation vertex unless it is a leaf of the DFS tree.
* _Parent cut-nodes_ — If the earliest reachable vertex from $v$ is the parent of $v$, then deleting the parent must sever $v$ from the tree unless the parent is the root.

```c
void process_vertex_late(int v)
{
    bool root;          // is the vertex the root of the DFS tree?
    int time_v;         // earliest reachable time for an ancestor of v
    int time_parent;    // earliest reachable time for an ancestor of parent[v]

    if(parent[v] < 1) // test if v is the root
    {
        if(tree_out_degree > 1)
            printf("root articulation vertex: %d \n", v);
        return;
    }

    root = (parent[parent[v]] < 1) // test if parent is root

    if(!root) 
    {
        if(reachable_ancestor[v] == parent[v])
            printf("parent articulation vertex: %d \n", parent[v]);

        if(reachable_ancestor[v] == v)
        {
            printf("bridge articulation vertex: %d \n", parent[v]);

            if(tree_out_degree[v] > 0)
                printf("bridge articulation vertex: %d \n", v);
        }
    }

    time_v = entry_time[reachable_ancestor[v]];
    time_parent = entry_time[ reachable_ancestor[parent[v]] ];

    if(time_v < time_parent)
        reachable_ancestor[parent[v]] =  reachable_ancestor[v];
}
```

We can Alternately talk about reliability in terms of edge failures instead of vertex failures.   
Identifying whether a given edge $(x,y)$ is a bridge is easily done in linear time by deleting the edge and testing whether the resulting graph is connected. In fact all bridges can be identified in the same $O(n+m)$ time. Edge $(x,y)$ is a bridge if $(1)$ it is a tree edge, and $(2)$ no back edge connects from $y$ or below to $x$ and above. This can be computed with an appropriate modification of the ```process_vertex_late``` function.

## Depth-First Search on Directed Graphs

Depth-first search on an undirected graph proves useful because it organizes the edges of the graph in a very precise way.    
For directed graphs, depth-first search labelings can take a wider range of possibilities, because a "cross edge" $(x,y)$ can exists and is not necessary a tree edge as for undirected graphs. In total, four edge can occur in traversing directed graphs.    
The correct labeling of each edge can be readily determined from the state, discovery time, and parent of each vertex, as encoded in the following function:

```c
int edge_classification(int x, int y)
{
    if(parent[y] == x) return TREE;
    if(discovered[y] && !processed[y]) return BACK;
    if(processed[y] && (entry_time[y] > entry_time[x])) return FORWARD;
    if(processed[y] && (entry_time[y] < entry_time[x])) return CROSS;

    printf("Warning: unclassified edge (%d, %d)\n", x, y);
}
```

__Topological Sorting__    

Topological sorting is the most important operation on directed acyclic graphs (DAGs). It orders the vertices on a line such that all directed edges go from left to right. Such an ordering cannot exist if the graph contains a directed cycle, because there is no way you can keep going right on a line and still return back to where you started from!   
Each DAG has at least one topological sorting and they let us find the shortest (or longest) path from a vertex as well as ordering vertices. Topological sorting proves very useful in essentially any algorithmic problem on directed graphs.    
Topological sorting can be performed efficiently using depth-first searching. A directed graph is a DAG if and only if no back edges are encountered. Labeling the vertices in the reverse order that they are marked _processed_ finds a topological sort of a DAG. Consider what happens to each directed edge $(x,y)$ as we encounter it exploring vertex $x$:
* If $y$ is currently _undiscovered_, then we start a DFS of $y$ before we can continue with $x$. Thus $y$ is marked _completed_ before $x$ is, and $x$ appears before $y$ in the topological order, as it must.
* If $y$ is _discovered_ but not _completed_, then $(x,y)$ is a back edge, which is forbidden in a DAG.
* If $y$ is _processed_, then it will have been so labeled before $x$. Therefore, $x$ appears before $y$ in the topological order, as it must.

```c
void process_vertex_late(int v)
{
    push(&sorted, v);
}

void process_edge(int x, int y)
{
    int class;  // edge class

    class = edge_classification(x, y);

    if(class == BACK)
        printf("Warning: directed cycle found, not a DAG\n");
}

void topsort(graph *g)
{
    int it;  // counter

    init_stack(&sorted);

    for(i=1; i<=g->nvertices; i++)
        if(discovered[i] == FALSE)
            dfs(g,i);

    print_stack(&sorted);  // report topological order

}
```

__Strongly Connected Components__    

We are often concerned with _strongly connected components_ — that is, partitioning a graphs into chunks such that directed paths exist between all pairs of vertices withing a given chunk. A directed graph is _strongly connected_ if there is a directed path between any two vertices.    
It is straightforward to use graph traversal to test whether a graph $G = (V,E)$ is strongly connected in linear time. First, do a traversal from some arbitrary vertex $v$. Every vertex in the graph had better be reachable from $v$, otherwise $G$ cannot be strongly connected. Now construct a graph $G' = (V,E')$ with the same vertex and edge set as $G$ but with all edges reversed. Thus any path from $v$ to $z$ in $G'$ corresponds to a path from $z$ to $v$ in $G$. By doing a DFS for $v$ in $G'$, we find all vertices with paths to $v$ in $G$. The graph is strongly connected if all vertices in $G$ can $(1)$ reach $v$ and $(2)$ are reachable from $v$.    
Graphs that are not strongly connected can be partitioned into strongly connected components. The set of such components and the weakly-connecting edges that link them can be determined using DFS. The algorithm is based on the observation that it is easy to find a directed cycle using depth-first search, since any back edge plus the down path in the DFS tree gives such a cycle.    
Our approach to implement this idea is reminiscent of finding biconnected components. We update our notion of the oldest reachable vertex in response to $(1)$ nontree edges and $(2)$ backing up from a vertex. We must also take notice of forward and cross edges. Our algorithm will peel one strong component off the tree at a time, and assign each of its vertices the number of the component it is in: 
```c
int low[MAXV+1];    // oldest vertex surely in component of v
int scc[MAXV+1];    // strong component number for each vertex

void strong_components(graph *g)
{
    int i;  // counter

    for(i=1; i<=(g->nvertices); i++)
    {
        low[i] = i;
        scc[i] = -1;
    }

    components_found = 0;
    init_stack(&active);
    initialize_search(&g);

    for(i=1; i<=(g->nvertices); i++)
    {
        if(discovered[i] == FALSE)
            dfs(g, i);
    }
}

void process_edge(int x, int y)
{
    int class;  // edge class
    
    class = edge_classification(x,y);

    if(class == BACK && entry_time[y] < entry_time[low[x]])
        low[x] = y;

    if(class == CROSS && scc[y] == -1 && entry_time[y] < entry_time[low[x]])
        low[x] = y;
    // We can count a cross edge if only it points to a vertex of a non assigned scc.
    // Otherwise it means there's no back edge to it, and it can be helped.
}

// A new strongly connected component is found whenever the lowest reachable vertex from v is v.
// If so we can clear the stack of this component. 
// Otherwise, we give our parent the benefit of the oldest ancestor we can reach and backtrack.

void process_vertex_early(int v)
{
    push(&active, v);
}

void process_vertex_late(int v)
{
    if(low[v] == v)
        pop_component(v);

    if(parent[v] > 0 && entry_time[low[v]] < entry_time[low[parent[v]]])
        low[parent[v]] = low[v];
}

void pop_component(inv v)
{
    int t;  // vertex placeholder

    components_found = components_found + 1;

    scc[v] = components_found;
    while((t = pop(&active)) != v)
        scc[t] = components_found;
}
```



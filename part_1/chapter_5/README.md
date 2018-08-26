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

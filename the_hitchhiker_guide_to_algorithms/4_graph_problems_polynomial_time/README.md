# Graph Problems: Polynomial-Time

## Connected Components

**Input description**: A directed or undirected graph $G$.
**Problem description**: Identify the different pieces or components of $G$, where vertices $x$ and $y$ are members of different components if no path exists from $x$ to $y$ in $G$.

## Topological Sorting

**Input description**: A directed acyclic graph $G =(V,E)$, also known as a _partial order_ or _poset_.
**Problem description**: Find a linear ordering of the vertices of $V$ such that for each edge $(i,j) \in E$, vertex $i$ is to the left of vertex $j$.

## Minimum Spanning Tree

**Input description**: A graph $G =(V,E)$ with weighted edges.
**Problem description**: The minimum weight subset of edges $E' \subset E$ that form a tree on V.

## Shortest Path

**Input description**: An edge-weighted graph $G$, with vertices $s$ and $t$.
**Problem description**: Find the shortest path from $s$ to $t$ in $G$.

## Transitive Closure and Reduction

**Input description**: A directed graph $G =(V,E)$.
**Problem description**: For _transitive closure_, construct a graph $G' =(V,E')$ with edge $(i,j) \in E'$ iff there is a directed path from $i$ to $j$ in $G$. For _transitive reduction_, construct a small graph $G' =(V,E')$ with a directed path from $i$ to $j$ in G' iﬀ there is a directed path from $i$ to $j$ in $G$.

## Matching

**Input description**: A (weighted) graph $G =(V,E)$.
**Problem description**: Find the largest set of edges $E'$ from $E$ such that each vertex in $V$ is incident to at most one edge of E'.

## Eulerian Cycle/Chinese Postman

**Input description**: A graph $G =(V,E)$.
**Problem description**: Find the shortest tour visiting each edge of $G$ at least once.

## Edge and Vertex Connectivity

**Input description**: A graph $G$. Optionally, a pair of vertices $s$ and $t$.
**Problem description**: What is the smallest subset of vertices (or edges) whose deletion will disconnect $G$? Or which will separate $s$ from $t$?

## Network Flow

**Input description**: A directed graph $G$, where each edge $e =(i,j)$ has a capacity $c_e$. A source node $s$ and sink node $t$.
**Problem description**: What is the maximum flow you can route from $s$ to $t$ while respecting the capacity constraint of each edge?

## Drawing Graphs Nicely

**Input description**: A graph $G$.
**Problem description**: Draw a graph $G$ so as to accurately reflect its structure.

## Drawing Trees

**Input description**: A tree $T$, which is a graph without any cycles.
**Problem description**: Create a nice drawing of the tree $T$.

## Planarity Detection and Embedding

**Input description**: A graph $G$.
**Problem description**: Can $G$ be drawn in the plane such that no two edges cross? If so, produce such a drawing.

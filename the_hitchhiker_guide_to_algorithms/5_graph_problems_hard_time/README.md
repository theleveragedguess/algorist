# Graph Problems: Hard Problems

## Clique

__Input description__: A graph $G =(V,E)$.  
__Problem description__: What is the largest $S \subset V$ such that for all $x,y \in S, (x,y) \in E$?

## Independent Set

__Input description__: A graph $G =(V,E)$.  
__Problem description__: What is the largest subset $S$ of vertices of $V$ such that for each edge $(x,y) \in E$, either $x \notin E$ or $y \notin E$?

## Vertex Cover

__Input description__: A graph $G =(V,E)$.  
__Problem description__: What is the smallest subset of $S \subset V$ such that each edge $(x,y) \in E$ contains at least one vertex of $S$?

## Traveling Salesman Problem

__Input description__: A weighted graph $G$.  
__Problem description__: Find the cycle of minimum cost, visiting each vertex of $G$ exactly once.

## Hamiltonian Cycle

__Input description__: A graph $G =(V,E)$.  
__Problem description__: Find a tour of the vertices using only edges from $G$, such that each vertex is visited exactly once.

## Graph Partition

__Input description__: A (weighted) graph $G =(V,E)$ and integers $k$ and $m$.  
__Problem description__: Partition the vertices into $m$ roughly equal-sized subsets such that the total edge cost spanning the subsets is at most $k$.

## Vertex Coloring

__Input description__: A graph $G =(V,E)$.  
__Problem description__: Color the vertices of $V$ using the minimum number of colors such that $i$ and $j$ have different colors for all $(i,j) \in E$.

## Edge Coloring

__Input description__: A graph $G =(V,E)$.  
__Problem description__: What is the smallest set of colors needed to color the edges of $G$ such that no two same-color edges share a common vertex?

## Graph Isomorphism

__Input description__: Two graphs, $G$ and $H$.  
__Problem description__: Find a (or all) mapping $f$ from the vertices of $G$ to the vertices of $H$ such that $G$ and $H$ are identical; i.e. , $(x,y)$ is an edge of $G$ iff $(f(x),f(y))$ is an edge of $H$.

## Steiner Tree

__Input description__: A graph $G =(V,E)$. A subset of vertices $T \in V$ .  
__Problem description__: Find the smallest tree connecting all the vertices of $T$.

## Feedback Edge/Vertex Set

__Input description__: A (directed) graph $G =(V,E)$.  
__Problem description__: What is the smallest set of edges $E'$ or vertices $V'$ whose deletion leaves an acyclic graph?

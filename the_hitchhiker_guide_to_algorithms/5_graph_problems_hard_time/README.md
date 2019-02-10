# Graph Problems: Hard Problems

## Clique

**Input description**: A graph $G =(V,E)$.  
**Problem description**: What is the largest $S \subset V$ such that for all $x,y \in S, (x,y) \in E$?

## Independent Set

**Input description**: A graph $G =(V,E)$.  
**Problem description**: What is the largest subset $S$ of vertices of $V$ such that for each edge $(x,y) \in E$, either $x \notin E$ or $y \notin E$?

## Vertex Cover

**Input description**: A graph $G =(V,E)$.  
**Problem description**: What is the smallest subset of $S \subset V$ such that each edge $(x,y) \in E$ contains at least one vertex of $S$?

## Traveling Salesman Problem

**Input description**: A weighted graph $G$.  
**Problem description**: Find the cycle of minimum cost, visiting each vertex of $G$ exactly once.

## Hamiltonian Cycle

**Input description**: A graph $G =(V,E)$.  
**Problem description**: Find a tour of the vertices using only edges from $G$, such that each vertex is visited exactly once.

## Graph Partition

**Input description**: A (weighted) graph $G =(V,E)$ and integers $k$ and $m$.  
**Problem description**: Partition the vertices into $m$ roughly equal-sized subsets such that the total edge cost spanning the subsets is at most $k$.

## Vertex Coloring

**Input description**: A graph $G =(V,E)$.  
**Problem description**: Color the vertices of $V$ using the minimum number of colors such that $i$ and $j$ have different colors for all $(i,j) \in E$.

## Edge Coloring

**Input description**: A graph $G =(V,E)$.  
**Problem description**: What is the smallest set of colors needed to color the edges of $G$ such that no two same-color edges share a common vertex?

## Graph Isomorphism

**Input description**: Two graphs, $G$ and $H$.  
**Problem description**: Find a (or all) mapping $f$ from the vertices of $G$ to the vertices of $H$ such that $G$ and $H$ are identical; i.e. , $(x,y)$ is an edge of $G$ iff $(f(x),f(y))$ is an edge of $H$.

## Steiner Tree

**Input description**: A graph $G =(V,E)$. A subset of vertices $T \in V$ .  
**Problem description**: Find the smallest tree connecting all the vertices of $T$.

## Feedback Edge/Vertex Set

**Input description**: A (directed) graph $G =(V,E)$.  
**Problem description**: What is the smallest set of edges $E'$ or vertices $V'$ whose deletion leaves an acyclic graph?

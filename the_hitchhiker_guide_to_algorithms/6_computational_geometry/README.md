# Computational Geometry

## Robust Geometric Primitives

**Input description**: A point $p$ and line segment $l$, or two line segments $l_1, l_2$.  
**Problem description**: Does $p$ lie over, under, or on $l$? Does $l_1$ intersect $l_2$?

## Convex Hull

**Input description**: A set $S$ of $n$ points in d-dimensional space.  
**Problem description**: Find the smallest convex polygon (or polyhedron) containing all the points of $S$.

## Triangulation

**Input description**: A set of points or a polyhedron.  
**Problem description**: Partition the interior of the point set or polyhedron into triangles.

## Voronoi Diagrams

**Input description**: A set $S$ of points $p_1,...,p_n$.  
**Problem description**: Decompose space into regions around each point such that all points in the region around $p_i$ are closer to $p_i$ than any other point in $S$.

## Nearest Neighbor Search

**Input description**: A set $S$ of $n$ points in $d$ dimensions; a query point $q$.  
**Problem description**: Which point in $S$ is closest to $q$?

## Range Search

**Input description**: A set $S$ of $n$ points in $E^d$ and a query region $Q$.  
**Problem description**: What points in $S$ lie within $Q$?

## Point Location

**Input description**: A decomposition of the plane into polygonal regions and a query point $q$.  
**Problem description**: Which region contains the query point $q$?

## Intersection Detection

**Input description**: A set $S$ of lines and line segments $l_1,...,l_n$ or a pair of polygons or polyhedra $P_1$ and $P_2$.  
**Problem description**: Which pairs of line segments intersect each other? What is the intersection of $P_1$ and $P_2$?

## Bin Packing

**Input description**: A set of $n$ items with sizes $d_1,...,d_n$. A set of $m$ bins with capacity $c_1,...,c_m$.  
**Problem description**: Store all the items using the smallest number of bins.

## Medial-Axis Transform

**Input description**: A polygon or polyhedron $P$.  
**Problem description**: What are the set of points within $P$ that have more than one closest point on the boundary of $P$?

## Polygon Partitioning

**Input description**: A polygon or polyhedron $P$.  
**Problem description**: Partition $P$ into a small number of simple (typically convex) pieces.

## Simplifying Polygons

**Input description**: A polygon or polyhedron $p$, with $n$ vertices.  
**Problem description**: Find a polygon or polyhedron $p'$ containing only $n'$ vertices, such that the shape of $p'$ is as close as possible to $p$.

## Shape Similarity

**Input description**: Two polygonal shapes, $P_1$ and $P_2$.  
**Problem description**: How similar are $P_1$ and $P_2$?

## Motion Planning

**Input description**: A polygonal-shaped robot starting in a given position $s$ in a room containing polygonal obstacles, and a goal position $t$.  
**Problem description**: Find the shortest route taking $s$ to $t$ without intersecting any obstacles.

## Maintaining Line Arrangements

**Input description**: A set of lines and line segments $l_1,...,l_n$.  
**Problem description**: What is the decomposition of the plane defined by $l_1,...,l_n$?

## Minkowski Sum

**Input description**: Point sets or polygons $A$ and $B$, containing $n$ and $m$ vertices respectively.  
**Problem description**: What is the convolution of $A$ and $B$—i.e. , the Minkowski $\sum{A + B = \lbrace x + y | x \in A,y \in B\rbrace}$?

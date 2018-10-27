# Computational Geometry

## Robust Geometric Primitives

__Input description__: A point $p$ and line segment $l$, or two line segments $l_1, l_2$.  
__Problem description__: Does $p$ lie over, under, or on $l$? Does $l_1$ intersect $l_2$?

## Convex Hull

__Input description__: A set $S$ of $n$ points in d-dimensional space.  
__Problem description__: Find the smallest convex polygon (or polyhedron) containing all the points of $S$.

## Triangulation

__Input description__: A set of points or a polyhedron.  
__Problem description__: Partition the interior of the point set or polyhedron into triangles.

## Voronoi Diagrams

__Input description__: A set $S$ of points $p_1,...,p_n$.  
__Problem description__: Decompose space into regions around each point such that all points in the region around $p_i$ are closer to $p_i$ than any other point in $S$.

## Nearest Neighbor Search

__Input description__: A set $S$ of $n$ points in $d$ dimensions; a query point $q$.  
__Problem description__: Which point in $S$ is closest to $q$?

## Range Search

__Input description__: A set $S$ of $n$ points in $E^d$ and a query region $Q$.  
__Problem description__: What points in $S$ lie within $Q$?

## Point Location

__Input description__: A decomposition of the plane into polygonal regions and a query point $q$.  
__Problem description__: Which region contains the query point $q$?

## Intersection Detection

__Input description__: A set $S$ of lines and line segments $l_1,...,l_n$ or a pair of polygons or polyhedra $P_1$ and $P_2$.  
__Problem description__: Which pairs of line segments intersect each other? What is the intersection of $P_1$ and $P_2$?

## Bin Packing

__Input description__: A set of $n$ items with sizes $d_1,...,d_n$. A set of $m$ bins with capacity $c_1,...,c_m$.  
__Problem description__: Store all the items using the smallest number of bins.

## Medial-Axis Transform

__Input description__: A polygon or polyhedron $P$.  
__Problem description__: What are the set of points within $P$ that have more than one closest point on the boundary of $P$?

## Polygon Partitioning

__Input description__: A polygon or polyhedron $P$.  
__Problem description__: Partition $P$ into a small number of simple (typically convex) pieces.

## Simplifying Polygons

__Input description__: A polygon or polyhedron $p$, with $n$ vertices.  
__Problem description__: Find a polygon or polyhedron $p'$ containing only $n'$ vertices, such that the shape of $p'$ is as close as possible to $p$.

## Shape Similarity

__Input description__: Two polygonal shapes, $P_1$ and $P_2$.  
__Problem description__: How similar are $P_1$ and $P_2$?

## Motion Planning

__Input description__: A polygonal-shaped robot starting in a given position $s$ in a room containing polygonal obstacles, and a goal position $t$.  
__Problem description__: Find the shortest route taking $s$ to $t$ without intersecting any obstacles.

## Maintaining Line Arrangements

__Input description__: A set of lines and line segments $l_1,...,l_n$.  
__Problem description__: What is the decomposition of the plane defined by $l_1,...,l_n$?

## Minkowski Sum

__Input description__: Point sets or polygons $A$ and $B$, containing $n$ and $m$ vertices respectively.  
__Problem description__: What is the convolution of $A$ and $B$—i.e. , the Minkowski $\sum{A + B = \lbrace x + y | x \in A,y \in B\rbrace}$?

# Numerical Problems

Numerical algorithms tend to be different beasts than combinatorial algorithms for at least two reasons:

* _Issues of Precision and Error_ – Numerical algorithms typically perform repeated floating-point computations, which accumulate error at each operation until, eventually, the results are meaningless.
* _Extensive Libraries of Codes_ – Large, high-quality libraries of numerical routines have existed since the 1960s, which is still not yet the case for combinatorial algorithms.

## Solving Linear Equations

__Input description__: An $m×n$ matrix $A$ and an $m×1$ vector $b$, together representing $m$ linear equations on $n$ variables.  
__Problem description__: What is the vector $x$ such that $A·x = b$?

## Bandwidth Reduction

__Input description__: A graph $G =(V,E)$, representing an $n×n$ matrix $M$ of zero and non-zero elements.  
__Problem description__: Which permutation $p$ of the vertices minimizes the length of the longest edge when the vertices are ordered on a line—i.e. , minimizes $max_{(i,j) \in E} |p(i)−p(j)|$?

## Matrix Multiplication

__Input description__: An  $x×y$ matrix $A$ and a $y×z$ matrix $B$.  
__Problem description__: Compute the $x×z$ matrix $A×B$.

## Determinants and Permanents

__Input description__: An $n×n$ matrix $M$.  
__Problem description__: What is the determinant $|M|$ or permanent $perm(M)$ of the matrix $m$?

## Constrained and Unconstrained Optimization

__Input description__: A function $f(x_1,...,x_n)$.  
__Problem description__: What point $p =( p_1,...,p_n)$ maximizes (or minimizes) the function $f$?

## Linear Programming

__Input description__: A set $S$ of $n$ linear inequalities on $m$ variables  
$S_i \coloneqq \sum_{j=1}^mc_{ij}.x_j \ge b_i, 1 \le i \le n$  
and a linear optimization function $f(X) = \sum_{j=1}^mc_j.x_j$.  
__Problem description__: Which variable assignment $X'$ maximizes the objective function $f$ while satisfying all inequalities $S$?

## Random Number Generation

__Input description: Nothing, or perhaps a seed.  
__Problem description__: Generate a sequence of random integers.

## Factoring and Primality Testing

__Input description__: An integer $n$.  
__Problem description__: Is $n$ a prime number, and if not what are its factors?

## Arbitrary-Precision Arithmetic

__Input description__: Two very large integers, $x$ and $y$.  
__Problem description__: What is $x + y$, $x−y$, $x×y$, and $x/y$?

## Knapsack Problem

__Input description__: A set of items $S = \lbrace1,...,n\rbrace$, where item $i$ has size $s_i$ and value $v_i$. A knapsack capacity is $C$.  
__Problem description__: Find the subset $S' \subset S$ that maximizes the value of $\sum_{i \in S'} v_i$, given that $\sum_{i \in S'} s_i \le C$; i.e. , all the items fit in a knapsack of size $C$.

## Discrete Fourier Transform

__Input description__: A sequence of $n$ real or complex values $h_i , 0 \le i \le n−1$, sampled at uniform intervals from a function $h$.  
__Problem description__: The discrete Fourier transform $H_m = \sum_{k=0}^{n-1}h_ke^{2{\pi}ikm/n}$ for $0 \le m \le n−1$.

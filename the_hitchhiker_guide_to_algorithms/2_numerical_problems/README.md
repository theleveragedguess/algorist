# Numerical Problems

Numerical algorithms tend to be different beasts than combinatorial algorithms for at least two reasons:

- _Issues of Precision and Error_ – Numerical algorithms typically perform repeated floating-point computations, which accumulate error at each operation until, eventually, the results are meaningless.
- _Extensive Libraries of Codes_ – Large, high-quality libraries of numerical routines have existed since the 1960s, which is still not yet the case for combinatorial algorithms.

## Solving Linear Equations

**Input description**: An $m \times n$ matrix $A$ and an $m×1$ vector $b$, together representing $m$ linear equations on $n$ variables.  
**Problem description**: What is the vector $x$ such that $A·x = b$?

## Bandwidth Reduction

**Input description**: A graph $G =(V,E)$, representing an $n×n$ matrix $M$ of zero and non-zero elements.  
**Problem description**: Which permutation $p$ of the vertices minimizes the length of the longest edge when the vertices are ordered on a line—i.e. , minimizes $max_{(i,j) \in E} |p(i)−p(j)|$?

## Matrix Multiplication

**Input description**: An $x×y$ matrix $A$ and a $y×z$ matrix $B$.  
**Problem description**: Compute the $x×z$ matrix $A×B$.

## Determinants and Permanents

**Input description**: An $n×n$ matrix $M$.  
**Problem description**: What is the determinant $|M|$ or permanent $perm(M)$ of the matrix $m$?

## Constrained and Unconstrained Optimization

**Input description**: A function $f(x_1,...,x_n)$.  
**Problem description**: What point $p =( p_1,...,p_n)$ maximizes (or minimizes) the function $f$?

## Linear Programming

**Input description**: A set $S$ of $n$ linear inequalities on $m$ variables  
$S_i := \sum_{j=1}^mc_{ij}.x_j \ge b_i, 1 \le i \le n$  
and a linear optimization function $f(X) = \sum_{j=1}^mc_j.x_j$.  
**Problem description**: Which variable assignment $X'$ maximizes the objective function $f$ while satisfying all inequalities $S$?

## Random Number Generation

**Input description**: Nothing, or perhaps a seed.  
**Problem description**: Generate a sequence of random integers.

## Factoring and Primality Testing

**Input description**: An integer $n$.  
**Problem description**: Is $n$ a prime number, and if not what are its factors?

## Arbitrary-Precision Arithmetic

**Input description**: Two very large integers, $x$ and $y$.  
**Problem description**: What is $x + y$, $x−y$, $x×y$, and $x/y$?

## Knapsack Problem

**Input description**: A set of items $S = \lbrace1,...,n\rbrace$, where item $i$ has size $s_i$ and value $v_i$. A knapsack capacity is $C$.  
**Problem description**: Find the subset $S' \subset S$ that maximizes the value of $\sum_{i \in S'} v_i$, given that $\sum_{i \in S'} s_i \le C$; i.e. , all the items fit in a knapsack of size $C$.

## Discrete Fourier Transform

**Input description**: A sequence of $n$ real or complex values $h_i , 0 \le i \le n−1$, sampled at uniform intervals from a function $h$.  
**Problem description**: The discrete Fourier transform $H_m = \sum_{k=0}^{n-1}h_ke^{2{\pi}ikm/n}$ for $0 \le m \le n−1$.

# Introduction to Algorithm Design

An algorithm is a _procedure_ to accomplish a specific task.
An algorithm is the idea behind any reasonable computer program.
An algorithm is a procedure that takes any of the possible input _instances_ and transforms it to the desired output.

We seek algorithms that are _correct_ and _efficient_, while being _easy to implement_.

## Proof of Correctness

__The Salesman problem__ or why there is a fundamental difference between _algorithms_, which always produce  correct results, and _heuristics_, which may usually do a good job but without providing any guarantee.

Reasonable-looking algorithms can easily be incorrect. Algorithm correctness is a property that must be carefully demonstrated.

A mathematical _proof_ consists of a precise _statement_ of what we try to prove, a set of _assumptions_ and a _chain of reasoning_. This leads to the ▮ QED.
A proof is a _demonstration_, it should be honest with crisp arguments.

## Reasoning about Correctness

The heart of any algorithm is an idea. If your idea is not clearly revealed when you express an algorithm, then you are using too low-level a notation to describe it.

Problems specifications have two parts: (1) the set of allowed input instances, and (2) the required properties of the algorithm output.

An important and honorable technique in algorithm design is to narrow the set of allowable instances until there is a correct and efficient algorithm.

A single _counter example_ providing a bad output for an algorithm is sufficient to prove its incorrectness.
_Verifiability_ and _simplicity_ should characterize good counter examples.

To find counter examples:

* _Think small_.
* _Think exhaustively_.
* _Hunt for the weakness_.
* _Go for a tie_.
* _Seek extremes_.

__Induction and Recursion__

I've heard it said that a computer scientist is a mathematician who only knows how to prove things by induction. However one must be careful of _boundary errors_ and _cavalier extension claims_.
Mathematical induction is usually the right way to verify the correctness of a recursive or incremental insertion algorithm.

__Summations__

_Arithmetic progressions_
* _Arithmetic sequence_: $A_n = A_{n-1} + d$
* _Arithmetic series_: $S_n = \sum\limits_{i=1}^n A_i$
* _Arithmetic series general representation_: $S_n = \dfrac{n(2A_1 + (n-1)d)}{2}$
* _Arithmetic series average representation_: $S_n = \dfrac{n(A_1 + A_n)}{2}$
* _Arithmetic series common case representation_: $S_n =\sum\limits_{i=1}^n i = \dfrac{n(n + 1)}{2}$
* $S(n,p) = \sum\limits_{i=1}^n i^p = \Theta(n^{p+1})$

_Geometric progressions_
* _Geometric sequence_: $G_n = G_{n-1}r$
* _Geometric series_: $S_n = \sum\limits_{i=1}^n G_i$
* _Geometric series general representation_: $S_n = G_1\dfrac{1-r^n}{1-r}$
* _Geometric series common case representation_: $S_n =\sum\limits_{i=1}^n a^i = \dfrac{a^{n+1}-1}{a-1}$
* $G_n < 2$ when $G_1 < 1$
* $G_n = \Theta(G_1^{n + 1})$ when $G_1 > 1$

_Harmonic Numbers_
* $H_n = \sum\limits_{i=1}^n \dfrac{1}{i} \approx \ln{n}$

## Modeling the problem

To exploit the algorithm literature, one must learn to describe the problem abstractly, in terms of procedures on fundamental structures. Modeling your application in terms of well-defined structures and algorithms is the most important single step towards a solution.

__Combinatorial Objects__

* _Permutations_ — which are arrangements , or ordering, of items.
* _Subsets_ — which represent selections from a set of items.
* _Trees_ — which represent hierarchical relationships between items.
* _Graphs_ — which represent relationships between arbitrary paris of objects.
* _Points_ — which represent locations in some geometric space.
* _Polygons_ — which represent regions in some geometric spaces.
* _Strings_ — which represent sequences of characters or patterns.

__Recursive Objects__

Learning to think recursively is learning to look for big things that are made from smaller things of _exactly the same type as the big thing_. Recursive descriptions of objects require both _decomposition rules_ and _basis cases_.

## For the Road
* _Permutations Count_: $P(n,r) = \dfrac{n!}{(n-r)!}$
* _Combinations Count_: $C(n,r) = \dfrac{n!}{r!(n-r)!}$


## Implementation Program
_part_1/chapter_1/programs.cpp,.h_

A program that tackles the Lotto Set problem.
The program finds a good ticket set, although it doesn't use any heuristics to optimize the minimum number of tickets in this set. In the contrary it covers all possible subsets.
By Using the psychic minimal 'promised' numbers in a ticket we can achieve a way better result.

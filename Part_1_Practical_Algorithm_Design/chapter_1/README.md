# Introduction to Algorithm Design
An algorithm is a _procedure_ to accomplish a specific task.

An algorithm is the idea behind any reasonable computer program.

An algorithm is a procedure that takes any of the possible input _instances_ and transforms it to the desired output.

We seek algorithms that are _correct_ and _efficient_, while being _easy to implement_.

## Proof of Correctness
__The Salesman problem__ or why there is a fundamental difference between _algorithms_, which always produce a correct results, and _heuristics_,which may usually do a good job but without providing any guarantee.

Reasonable-looking algorithms can easily be incorrect. Algorithm correctness is a property that must be carefully demonstrated.

A mathematical _proof_ consists of a precise _statement_ of what we try to prove, a set of _assumptions_ and a _chain of reasoning_. This leads to the ▮ QED.

A proof is a _demonstration_, it should be honest with crisp arguments.

## Reasoning about Correctness
The heart of any algorithm is an idea. If your idea is not clearly revealed when you express an algorithm, then you are using too low-level a notation to describe it.


Problems specifications have two parts: (1) the set of allowed input instances, and (2) the required properties of the algorithm output.

An important and honorable technique in algorithm design is to narrow the set of allowable instances until there is a correct and efficient algorithm.

A single _counter example_ providing a bad output for an algorithm is sufficient to prove it's incorrectness.
_Verifiability_ and _simplicity_ should characterize good counter examples.

To find counter examples: 
* _Think small_
* _Think exhaustively_
* _Hunt for the weakness_ 
* _Go for a tie_
* _Seek extremes_

__Induction and Recursion__, I've heard it said that a computer scientist is mathematician who only knows how to prove things by induction. However one must be careful of _boundary errors_ and _cavalier extension claims_.
Mathematical induction is the usually the right way to verify the correctness of a recursive or incremental insertion algorithm.

__Summations__,  
_Arithmetic progressions_ 
* sum(1, n, i => i) => n(n+1)/2
* S(n,p) => sum(1, n, i => i^p) => Ө(n^(p+1))

_Geometric series_
* G(n, a) => sum(0, n, i => a^i) => (a^(n+1) - 1)/(a-1)
* G(n, a) < 2 when a < 1
* G(n, a) => Ө(a^(n + 1)) when a > 1

## Modeling the problem ##
To exploit the algorithm literature, you must learn to describe your problem abstractly, in terms of procedures on fundamental structures.

Modeling your application in terms of well-defined structures and algorithms is the most important single step towards a solution.

__Combinatorial Objects__
* _Permutations_
* _Subsets_
* _Trees_
* _Graphs_
* _Points_
* _Polygons_
* _Strings_

__Recursive Objects__
Learning to think recursively is learning to look for big things that are made from smaller things of _exactly the same type as the big thing_.
Recursive descriptions of objects require both _decomposition rules_ and _basis cases_.

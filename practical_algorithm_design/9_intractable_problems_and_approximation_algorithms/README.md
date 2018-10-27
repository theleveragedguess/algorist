# Intractable Problems and Approximation Algorithms

The theory of NP-completeness enables the algorithm designer to focus her efforts more productively, by revealing that the search for an efficient algorithm for this particular problem is doomed to failure. When one _fails_ to show a problem is hard, that suggests there may well be an efficient algorithm to solve it.  

The theory of NP-completeness also enables us to identify what properties make a particular problem hard. This provides direction for us to model it in different ways or exploit more benevolent characteristics of the problem.

## Problems and Reductions

Reductions are operations that convert one problem into another. To describe them, we must be somewhat rigorous in our definitions.

### The Key Idea

A translation of instances from one type of problem to instances of another such that the answers are preserved is what is meant by a reduction. Now suppose this reduction translates $G$ to $Y$ in $O(P(n))$ time. There are two possible implications:

* If my $Y$ ran in $O(P'(n))$, this means I could solve the $G$ problem in $O(P(n)+P'(n))$ by spending the time to translate the problem and then the time to execute the $Y$ subroutine.
* If I know that $Ω(P'(n))$ is a lower bound on computing $G$, meaning there definitely exists no faster way to solve it, then $Ω(P'(n)− P(n))$ must be a lower bound to compute $Y$. Why? If I could solve $Y$ any faster, then I could violate my lower bound by solving $G$ using the above reduction. This implies that there can be no way to solve $Y$ any faster than claimed.

__Reductions are a way to show that two problems are essentially identical. A fast algorithm (or the lack of one) for one of the problems implies a fast algorithm (or the lack of one) for the other.__

### Decisions Problems

The simplest interesting class of problems have answers restricted to true and false. These are called _decision problems_. It proves convenient to reduce/translate answers between decision problems because both only allow true and false as possible answers.  

Fortunately, most interesting optimization problems can be phrased as decision problems that capture the essence of the computation

## Reductions for Algorithms

To solve problem $a$, we translate/reduce the a instance to an instance of $b$, then solve this instance using an efficient algorithm for problem $b$. The overall running time is the time needed to perform the reduction plus that solve the $b$ instance.

### Hamiltonian Cycle

The Hamiltonian cycle problem is one of the most famous in graph theory. It seeks a tour that visits each vertex of a given graph exactly once.  

_Problem_: Hamiltonian Cycle  
_Input_: An unweighted graph $G$.  
_Output_: Does there exist a simple tour that visits each vertex of $G$ without repetition?  

The following reduction from Hamiltonian cycle to traveling salesman shows that the similarities are greater than the differences:  

```c
HamiltonianCycle(G =(V,E))
    Construct a complete weighted graph G' =(V',E') where V' = V.
    n = |V|
    for i = 1 to n do
        for j = 1 to n do
            if (i,j) ∈ E then w(i,j) = 1 else w(i,j) = 2
    Return the answer to Traveling-Salesman-Decision-Problem(G',n).
```

### Independent Set and Vertex Cover

The vertex cover problem, asks for a small set of vertices that contacts each edge in a graph.

_Problem_: Vertex Cover  
_Input_: A graph $G =(V,E)$ and integer $k \leq |V|$.  
_Output_: Is there a subset $S$ of at most $k$ vertices such that every $e \in E$ contains at least one vertex in $S$?  

A set of vertices $S$ of graph $G$ is independent if there are no edges $(x,y)$ where both $x \in S$ and $y \in S$.  

_Problem_: Independent Set  
_Input_: A graph $G$ and integer $k \leq |V|$.  
_Output_: Does there exist an independent set of $k$ vertices in $G$?  

 This gives us a reduction between the two problems:  

 ```c
 VertexCover(G,k)
    G' = G
    k' = |V| − k
    Return the answer to IndependentSet(G',k')
 ```

### Clique

 A social clique is a group of mutual friends who all hang around together. A graph-theoretic _clique_ is a complete sub-graph where each vertex pair has an edge between them.

 _Problem_: Maximum Clique  
 _Input_: A graph $G = (V,E)$ and integer $k ≤ |V|$.  
 _Output_: Does the graph contain a clique of $k$ vertices; i.e. , is there a subset $S \subset V$, where $|S| \leq k$, such that every pair of vertices in $S$ defines an edge of $G$?  

A reduction between Maximum Clique and Independent Set follows by reversing the roles of edges and non-edges — an operation known as _complementing_ the graph:

```c
IndependentSet(G,k)
    Construct a graph G' = (V',E') where V' = V , and
        For all (i,j) not in E, add (i,j) to E'
    Return the answer to Clique(G',k)
```

## Satisfiability

To demonstrate the hardness of all problems using reductions, we must start with a single problem that is absolutely, certifiably, undeniably hard. The mother of all NP-complete problems is a logic problem named _satisfiability_:

_Problem_: Satisfiability  
_Input_: A set of Boolean variables $V$ and a set of clauses $C$ over $V$.  
_Output_: Does there exist a satisfying truth assignment for $C$—i.e. , a way to set the variables $v_1,...,v_n$ true or false so that each clause contains at least one true literal?  

For a combination of social and technical reasons, it is well accepted that satisfiability is a hard problem; one for which no worst-case polynomial-time algorithm exists. Literally every top-notch algorithm expert in the world (and countless lesser lights) have directly or indirectly tried to come up with a fast algorithm to test whether a given set of clauses is satisfiable. All have failed. Furthermore, many strange and impossible-to-believe things in the field of computational complexity have been shown to be true if there exists a fast satisfiability algorithm. satisfiability is a hard problem, and we should feel comfortable accepting this.

### 3-Satisfiability

_Problem_: 3-Satisfiability (3-SAT)  
_Input_: A collection of clauses $C$ where each clause contains exactly 3 literals, over a set of Boolean variables $V$.  
_Output_: Is there a truth assignment to $V$ such that each clause is satisfied?  

Since this is a restricted case of satisfiability, the hardness of 3-SAT implies that satisfiability is hard. We can show the hardness of 3-SAT using a reduction that translates every instance of satisfiability into an instance of 3-SAT without changing whether it is satisfiable.

* $k = 1$, meaning that $C_i = \{z_1\}$ – We create two new variables $v_1,v_2$ and four new 3-literal clauses: $\{v_1,v_2,z_1\}, \{v_1,\bar{v_2},z_1\}, \{\bar{v_1},v_2,z_1\}, \{\bar{v_1},\bar{v_2},z_1\}$. Note that the only way that all four of these clauses can be simultaneously satisfied is if $z_1 = true$, which also means the original $C_i$ will be satisfied.
* $k = 2$, meaning that $C_i = \{z_1, z_2\}$ – We create one new variable $v_1$ and two new clauses: $\{v_1,z_1,z_2\}, \{\bar{v_1},z_1,z_2\}$. Again, the only way to satisfy both of these clauses is to have at least one of $z_1$ and $z_2$ be true, thus satisfying $c_i$.
* $k = 3$, meaning that $C_i = \{z_1,z_2,z_3\}$ – We copy $C_i$ into the 3-SAT instance unchanged: $\{z_1,z_2,z_3\}$.
* $k \gt 3$, meaning that $C_i = \{z_1,z_2,...,z_n\}$– We create $n−3$ new variables and $n−2$ new clauses in a chain, where for $2 \leq j \leq n−3, C_{i,j} = \{v_i,j−1,z j+1,\bar{v_i,j}\}, C_{i,1} = \{z_1,z_2,\bar{v_i,1}\}$, and $C_{i,n−2} =\{v_{i,n−3},z_{n−1},z_n\}$.

### Creative Reductions

Since both satisfiability and 3-SAT are known to be hard, we can use either of them in reductions. Usually 3-SAT is the better choice, because it is simpler to work with.  

One perpetual point of confusion is getting the direction of the reduction right. Recall that we must transform every instance of a known NP-complete problem into an instance of the problem we are interested in. If we perform the reduction the other way, all we get is a slow way to solve the problem of interest, by using a subroutine that takes exponential time.  

__A small set of NP-complete problems (3-SAT, vertex cover, integer partition, and Hamiltonian cycle) suffice to prove the hardness of most other hard problems.__

## The Art of Proving Hardness

Proving that problems are hard is a skill. But once you get the hang of it, reductions can be surprisingly straightforward and pleasurable to do. Indeed, the dirty little secret of NP-completeness proofs is that they are usually easier to create than explain, in much the same way that it can be easier to rewrite old code than understand and modify it.

* _Make your source problem as simple (i.e. , restricted) as possible._ — Never try to use full satisfiability to prove hardness. Start with 3-satisfiability. Hamiltonian path over Hamiltonian cycle over traveling salesman problem.
* _Make your target problem as hard as possible._ — There's no need to afraid of adding extra constraints or freedoms to make the target problem more general.
* _Select the right source problem for the right reason._:
  * _3-SAT_: The old reliable for when none of the three problems below seem appropriate.
  * _Integer partition_: This is the one and only choice for problems whose hardness seems to require using large numbers.
  * _Vertex cover_: This is the answer for any graph problem whose hardness depends upon selection. Chromatic number, clique, and independent set all involve trying to select the correct subset of vertices or edges.
  * _Hamiltonian path_: For any graph problem whose hardness depends upon ordering.
* _Amplify the penalties for making the undesired selection._ — Be bold with the penalties; to punish anyone for trying to deviate from the intended solution.
* _Think strategically at a high level, then build gadgets to enforce tactics._
* _When you get stuck, alternate between looking for an algorithm or a reduction_

## P vs. NP

The theory of NP-completeness rests on a foundation of rigorous but subtle definitions from automata and formal language theory.

### Verification vs. Discovery

The primary question in __P vs NP__ is whether _verification_ is really an easier task than initial _discovery_.

### The Classes P and NP

Every well-defined algorithmic problem must have an asymptotically fastest possible algorithm solving it,as measured in the Big-Oh, worst-case sense of fastest.  

We can think of the class __P__ as an exclusive club for algorithmic problems that a problem can only join after demonstrating that there exists a polynomial-time algorithm to solve it.  

A less-exclusive club welcomes all the algorithmic problems whose solutions can be verified in polynomial-time. As shown above, this club contains traveling salesman, satisfiability, and vertex cover, none of which currently have the credentials to join P. We call this less-exclusive club __NP__.  

The \$1,000,000 question is whether there are in fact problems in NP that cannot be members of P. If no such problem exists, the classes must be the same and $P = NP$. If even one such a problem exists, the two classes are different and $P \neq NP$. The opinion of most algorists and complexity theorists is that the classes differ, meaning $P \neq NP$, but a much stronger proof than “I can’t ﬁnd a fast enough algorithm” is needed.

### Why is Satisfiability the Mother of All Hard Problems

An enormous tree of NP-completeness reductions has been established that entirely rests on the hardness of satisfiability.  

There exists an extraordinary super-reduction (called Cook’s theorem). reducing all the problems in NP to satisfiability. Thus, if you prove that satisfiability (or equivalently any single NP-complete problem) is in P, then all other problems in NP follow and $P = NP$.  

Our inability to ﬁnd a fast algorithm for any of these problems is a strong reason for believing that they are all truly hard, and probably $P \neq NP$.  

### NP-hard vs. NP-complete

We say that a problem is NP-hard if, like satisfiability, it is at least as hard as any problem in NP. We say that a problem is NP-complete if it is NP-hard, and also in NP itself. Because NP is such a large class of problems, most NP-hard problems you encounter will actually be complete.  

That said, there are problems that appear to be NP-hard yet not in NP. These problems might be even harder than NP-complete!

## Dealing with NP-complete Problems

For the practical person, demonstrating that a problem is NP-complete is never the end of the line. That application will not go away when told that there is no polynomial-time algorithm. There's more to do however:

* _Algorithms fast in the average case_ – i.e. backtracking algorithms with substantial pruning.
* _Heuristics_ – i.e. simulated annealing or greedy approaches.
* _Approximation algorithms_ – The theory of NP-completeness only stipulates that it is hard to get close to the answer. With clever, problem-specific heuristics, we can probably get _close_ to the optimal answer on all possible instances.

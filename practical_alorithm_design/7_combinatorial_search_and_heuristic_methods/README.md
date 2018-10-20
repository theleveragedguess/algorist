# Combinatorial Search and Heuristic Methods

We can solve many problems to optimality using exhaustive search techniques, although the time complexity can be enormous.    
In this section, we introduce backtracking as a technique for listing all possible solutions for a combinatorial algorithm problem. We illustrate the power of clever pruning techniques to speed up real search applications. For problems that are too large to contemplate using brute-force combinatorial search, we introduce heuristic methods such as simulated annealing. Such heuristic methods are important weapons in any practical algorist’s arsenal.

## Backtracking   

Backtracking is a systematic way to iterate through all the possible configurations of a search space. These configurations may represent all possible arrangements of objects (permutations) or all possible ways of building a collection of them (subsets). Other situations may demand enumerating all spanning trees of a graph, all paths between two vertices, or all possible ways to partition vertices into color classes.   
We must generate each one possible configuration exactly once. Avoiding both repetitions and missing configurations means that we must define a systematic generation order. We will model our combinatorial search solution as a vector $a = (a_1, a_2,..., a_n)$, where each element $a_i$ is selected from a finite ordered set $S_i$. At each step in the backtracking algorithm, we try to extend a given partial solution $a = (a_1, a_2,..., a_k)$ by adding another element at the end. After extending it, we must test whether what we now have is a solution: if so, we should print it or count it. If not, we must check whether the partial solution is still potentially extendible to some complete solution.    
Backtracking constructs a tree of partial solutions, where each vertex represents a partial solution. There is an edge from $x$ to $y$ if node $y$ was created by advancing from $x$. This tree of partial solutions provides an alternative way to think about backtracking, for the process of constructing the solutions corresponds exactly to doing a depth-first traversal of the backtrack tree. Viewing backtracking as a depth first search on an implicit graph yields a natural recursive implementation of the basic algorithm.    
Although a breadth-first search could also be used to enumerate solutions, a depth-first search is greatly preferred because it uses much less space. The current state of a search is completely represented by the path from the root to the current search depth-first node. This requires space proportional to the _height_ of the tree. In breadth-first search, the queue stores all the nodes at the current level, which is proportional to the _width_ of the search tree. For most interesting problems, the width of the tree grows exponentially in its height.   

__Implementation__ 

```c
bool finished = FALSE; // found all solutions yet?

void backtrack(int a[], int k, data input)
{
    int c[MAXCANDIDATES]; // candidates for next position
    int ncandidates;      // next position candidate count
    int i;                // counter 

    if (is_a_solution(a, k, input))
        process_solution(a, k, input);
    else
    {
        k = k + 1;
        construct_candidates(a, k, input, c, &ncandidates);
        for (i = 0; i < ncandidates; i++)
        {
            a[k] = c[i];
            make_move(a, k, input);
            backtrack(a, k, input);
            unmake_move(a, k, input);
            if (finished)
                return; // terminate early
        }
    }
}
```

Backtracking ensures correctness by enumerating all possibilities. It ensures efficiency by never visiting a state more than once.   

The application-specific parts of this algorithm consists of ﬁve subroutines:
* ```is_a_solution(a, k, input)```
* ```construct_candidates(a, k, input, c, ncandidates)```
* ```process_solution(a, k, input)```
* ```make_move(a, k, input)``` and ```unmake_move(a, k, input)```

__Constructing All Subsets__   

Each subset is described by elements that are in it. To construct all $2^n$ subsets, we set up an array/vector of $n$ cells, where the value of $a_i$ (true or false) signifies whether the $i$th item is in the given subset. In the scheme of our general backtrack algorithm, $S_k = (true,false)$ and $a$ is a solution whenever $k = n$. We can now construct all subsets with simple implementations of ```is_a_solution()```, ```construct_candidates()```, and ```process_solution()```.

```c
bool is_a_solution(int a[], int k, int n) 
{ 
    return k == n; // is k == n?
}

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    c[0] = TRUE;
    c[1] = FALSE;
    *ncandidates = 2;
}

void process_solution(int a[], int k)
{
    int i; // counter
    
    printf("{");
    for (i = 1; i <= k; i++)
        if (a[i] == TRUE)
            printf(" %d", i);
    printf(" }\n");
}

void generate_subsets(int n)
{
    int a[NMAX]; // solution vector
    backtrack(a, 0, n);
}
```

__Constructing All Permutations__    
       
Set up an array/vector $a$ of $n$ cells. The set of candidates for the $i$th position will be the set of elements that have not appeared in the $(i−1)$ elements of the partial solution, corresponding to the first $i−1$ elements of the permutation. In the scheme of the general backtrack algorithm, $S_k = \lbrace1,...,n\rbrace −a$, and $a$ is a solution whenever $k = n$.   

```c
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i;              // counter
    bool in_perm[NMAX]; // who is in the permutation?

    for (i = 1; i < NMAX; i++)
        in_perm[i] = FALSE;
    for (i = 0; i < k; i++)
        in_perm[a[i]] = TRUE;
    
    *ncandidates = 0;
    for (i = 1; i <= n; i++)
        if (in_perm[i] == FALSE)
        {
            c[*ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
}

void process_solution(int a[], int k)
{
    int i; // counter
    for (i = 1; i <= k; i++)
        printf(" %d", a[i]);
    printf("\n");
}

bool is_a_solution(int a[], int k, int n) 
{ 
    return (k == n); 

}

void generate_permutations(int n)
{
    int a[NMAX]; // solution vector
    backtrack(a, 0, n);
}

```

__Constructing All Paths in a Graph__    

In general, $S_{k+1}$ consists of the set of vertices adjacent to $a_k$ that have not been used elsewhere in the partial solution $A$.

```c

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i;             // counters
    bool in_sol[NMAX]; // what’s already in the solution?
    edgenode *p;       // temporary pointer
    int last;          // last vertex on current path

    for (i = 1; i < NMAX; i++)
        in_sol[i] = FALSE;
    for (i = 1; i < k; i++)
        in_sol[a[i]] = TRUE;
    if (k == 1)
    { // always start from vertex 1
        c[0] = 1;
        *ncandidates = 1;
    }
    else
    {
        *ncandidates = 0;
        last = a[k - 1];
        p = g.edges[last];
        while (p != NULL)
        {
            if (!in_sol[p->y])
            {
                c[*ncandidates] = p->y;
                *ncandidates = *ncandidates + 1;
            }
            p = p->next;
        }
    }
}

bool is_a_solution(int a[], int k, int t) 
{
    return (a[k] == t);

}

void process_solution(int a[], int k) 
{
    solution_count++; // count all s to t paths 
}

```

## Search Pruning

_Pruning_ is the technique of cutting oﬀ the search the instant we have established that a partial solution cannot be extended into a full solution. Exploiting symmetry is another avenue for reducing combinatorial searches. Pruning away partial solutions identical to those previously considered requires recognizing underlying symmetries in the search space.   

__Clever pruning can make short work of surprisingly hard combinatorial search problems. Proper pruning will have a greater impact on search time than any other factor__

## Heuristic Search Methods   

Heuristic methods provide an alternate way to approach difficult combinatorial optimization problems. Backtracking gave us a method to ﬁnd the best of all possible solutions, as scored by a given objective function. However, any algorithm searching all configurations is doomed to be impossible on large instances.    
In particular, we will look at three different heuristic search methods: random sampling, gradient-descent search, and simulated annealing. All three methods have two common components: 
* _Solution space representation_ – This is a complete yet concise description of the set of possible solutions for the problem.
* _Cost function_ – Search methods need a cost or evaluation function to access the quality of each element of the solution space. 

__Random Sampling__   

The simplest method to search in a solution space uses random sampling. It is also called the _Monte Carlo method_. We repeatedly construct random solutions and evaluate them, stopping as soon as we get a good enough solution, or (more likely) when we are tired of waiting. We report the best solution found over the course of our sampling.   
True random sampling requires that we are able to select elements from the solution space _uniformly at random_. This means that each of the elements of the solution space must have an equal probability of being the next candidate selected. Such sampling can be a subtle problem.   

```c
void random_sampling(tsp_instance *t, int nsamples, tsp_solution *bestsol)
{
    tsp_solution s;   // current tsp solution
    double best_cost; // best cost so far
    double cost_now;  // current cost
    int i;            // counter

    initialize_solution(t->n, &s);
    best_cost = solution_cost(&s, t);
    copy_solution(&s, bestsol);

    for (i = 1; i <= nsamples; i++)
    {
        random_solution(&s);
        cost_now = solution_cost(&s, t);
        if (cost_now < best_cost)
        {
            best_cost = cost_now;
            copy_solution(&s, bestsol);
        }
    }
}
```

When might random sampling do well? 
* _When there are a high proportion of acceptable solutions._
* _When there is no coherence in the solution space._

__Local Search__    

A local search employs _local neighborhood_ around every element in the solution space. Think of each element $x$ in the solution space as a vertex, with a directed edge $(x,y)$ to every candidate solution $y$ that is a neighbor of $x$. Our search proceeds from $x$ to the most promising candidate in $x$’s neighborhood.   
We certainly do _not_ want to explicitly construct this neighborhood graph for any sizable solution space. Instead, we want a general transition mechanism that takes us to the next solution by slightly modifying the current one. Typical transition mechanisms include swapping a random pair of items or changing (inserting or deleting) a single item in the solution.    
A local search heuristic starts from an arbitrary element of the solution space, and then scans the neighborhood looking for a favorable transition to take. In a _hill-climbing_ procedure, we try to ﬁnd the top of a mountain (or alternately, the lowest point in a ditch) by starting at some arbitrary point and taking any step that leads in the direction we want to travel. We repeat until we have reached a point where all our neighbors lead us in the wrong direction. We are now _King of the Hill_ (or _Dean of the Ditch_). We are probably not _King of the Mountain_, however.   
Hill-climbing and closely related heuristics such as _greedy search_ or _gradient descent search_ are great at finding local optima quickly, but often fail to ﬁnd the globally best solution.

```c
void hill_climbing(tsp_instance *t, tsp_solution *s)
{
    double cost;  // best cost so far
    double delta; // swap cost
    int i, j;     // counters
    bool stuck;   // did I get a better solution?

    double transition();
    initialize_solution(t->n, s);
    random_solution(s);
    cost = solution_cost(s, t);

    do
    {
        stuck = TRUE;
        for (i = 1; i < t->n; i++)
            for (j = i + 1; j <= t->n; j++)
            {
                delta = transition(s, t, i, j);
                if (delta < 0)
                {
                    stuck = FALSE;
                    cost = cost + delta;
                }
                else
                    transition(s, t, j, i);
            }
    } while (!stuck);
}
```

When does local search do well?   
* _When there is great coherence in the solution space._
* _Whenever the cost of incremental evaluation is much cheaper than global evaluation._

__Simulated Annealing__    

Simulated annealing is a heuristic search procedure that allows occasional transitions leading to more expensive (and hence inferior) solutions. This may not sound like progress, but it helps keep our search from getting stuck in local optima.   
The inspiration for simulated annealing comes from the physical process of cooling molten materials down to the solid state. In thermodynamic theory, the energy state of a system is described by the energy state of each particle constituting it. A particle’s energy state jumps about randomly, with such transitions governed by the temperature of the system. In particular, the transition probability $P(e_i,e_j,T)$ from energy $e_i$ to $e_j$ at temperature $T$ is given by   
$P(e_i,e_j,T) = e^{\frac{(e_i-e_j)}{k_BT}}$    
where $k_B$ is a constant—called Boltzmann’s constant.
Consider the value of the exponent under different conditions. The probability of moving from a high-energy state to a lower energy state is very high. But, there is still a nonzero probability of accepting a transition into a high-energy state, with such small jumps much more likely than big ones. The higher the temperature, the more likely energy jumps will occur.   
A physical system, as it cools, seeks to reach a minimum-energy state. Minimizing the total energy is a combinatorial optimization problem for any set of discrete particles. Through random transitions generated according to the given probability distribution, we can mimic the physics to solve arbitrary combinatorial optimization problems.   

__Simulated annealing is effective because it spends much more of its time working on good elements of the solution space than on bad ones, and because it avoids getting trapped repeatedly in the same local optima.__    

As with a local search, the problem representation includes both a representation of the solution space and an easily computable cost function $C(s)$ measuring the quality of a given solution. The new component is the _cooling schedule_, whose parameters govern how likely we are to accept a bad transition as a function of time.    
At the beginning of the search, we are eager to use randomness to explore the search space widely, so the probability of accepting a negative transition should be high. As the search progresses, we seek to limit transitions to local improvements and optimizations. The cooling schedule can be regulated by the following parameters: 
* _Initial system temperature_ – Typically $t_1 = 1$. 
* _Temperature decrement function_ – Typically $t_k = α.t_{k−1}$, where $0.8 \leq α \leq 0.99$. This implies an exponential decay in the temperature, as opposed to a linear decay. 
* _Number of iterations between temperature change_ – Typically, $100$ to $1,000$ iterations might be permitted before lowering the temperature.
* _Acceptance criteria_ – A typical criterion is to accept any transition from $s_i$ to $s_{i+1}$ when $C(s_{i+1}) < C(s_i)$, and also accept a negative transition whenever $e^{-\frac{(C(s_i) - C(s_{i+1}))}{k.t_i}} \geq r$, where $r$ is a random number $0 \leq r \lt 1$. The constant $k$ normalizes this cost function so that almost all transitions are accepted at the starting temperature.
* _Stop criteria_ – Typically, when the value of the current solution has not changed or improved within the last iteration or so, the search is terminated and the current solution reported.   

Creating the proper cooling schedule is somewhat of a trial-and-error process of mucking with constants and seeing what happens.   
In expert hands, the best problem-specific heuristics for TSP can slightly outperform simulated annealing. But the simulated annealing solution works admirably more easily.

```c
void anneal(tsp_instance *t, tsp_solution *s)
{
    int i1, i2;           // pair of items to swap
    int i, j;             // counters
    double temperature;   // the current system temp
    double current_value; // value of current state
    double start_value;   // value at start of loop
    double delta;         // value after swap
    double merit, flip;   // hold swap accept condition
    double exponent;      // exponent for energy function

    double random_float();
    double solution_cost(), transition();
    
    temperature = INITIAL_TEMPERATURE;
    initialize_solution(t->n, s);
    current_value = solution_cost(s, t);
    
    for (i = 1; i <= COOLING_STEPS; i++)
    {
        temperature *= COOLING_FRACTION;
        start_value = current_value;
        for (j = 1; j <= STEPS_PER_TEMP; j++)
        { // pick indices of elements to swap
            i1 = random_int(1, t->n);
            i2 = random_int(1, t->n);
            flip = random_float(0, 1);
            delta = transition(s, t, i1, i2);
            exponent = (-delta / current_value) / (K * temperature);
            merit = pow(E, exponent);
            if (delta < 0) // ACCEPT-WIN
                current_value = current_value + delta;
            else
            {
                if (merit > flip) // ACCEPT-LOSS
                    current_value = current_value + delta;
                else // REJECT
                    transition(s, t, i1, i2);
            }
        }
        // restore temperature if progress has been made
        if ((current_value - start_value) < 0.0)
            temperature = temperature / COOLING_FRACTION;
    }
}
```

## Other Heuristic Search Methods

Several heuristic search methods have been proposed to search for good solutions for combinatorial optimization problems. Like simulated annealing, many techniques relies on analogies to real-world physical processes. Popular methods include _genetic algorithms_, _neural networks_, and _ant colony optimization_.   

__Genetic Algorithms__   

Genetic algorithms draw their inspiration from evolution and natural selection. Through the process of natural selection, organisms adapt to optimize their chances for survival in a given environment.   
Genetic algorithms maintain a “population” of solution candidates for the given problem. Elements are drawn at random from this population and allowed to “reproduce” by combining aspects of the two-parent solutions. The probability that an element is chosen to reproduce is based on its “fitness,”—essentially the cost of the solution it represents. Unfit elements die from the population, to be replaced by a successful-solution offspring.    
The idea behind genetic algorithms is extremely appealing. However, the crossover and mutation operations typically make no use of problem-specific structure, so most transitions lead to inferior solutions, and convergence is slow. Indeed, the analogy with evolution—where significant progress require millions of years—can be quite appropriate.   

__Seldom are problems where genetic algorithms seemed to be the right way to attack it. Stick to simulated annealing for your heuristic search voodoo needs.__

## Parallel Algorithms 

Two heads are better than one, and more generally, $n$ heads are better than $n−1$. Parallel processing is becoming more important with the advent of cluster computing and multi-core processors. It seems like the easy way out of hard problems. Indeed, sometimes, for some problems, parallel algorithms are the most effective solution.   
However, there are several pitfalls associated with parallel algorithms that you should be aware of: 

* _There is often a small upper bound on the potential win_ –  Greater performance gains may be possible by finding a better sequential algorithm. Your time spent parallelizing a code might well be better spent enhancing the sequential version. Performance-tuning tools such as profilers are better developed for sequential machines than for parallel models. 
* _Speedup means nothing_ – A carefully designed sequential algorithm can often beat an easily-parallelized code running on a typical parallel machine. The one-processor parallel version of your code is likely to be a crummy sequential algorithm, so measuring speedup typically provides an unfair test of the benefits of parallelism.
* _Parallel algorithms are tough to debug_ – Unless your problem can be decomposed into several independent jobs, the different processors must communicate with each other to end up with the correct final result. Unfortunately, the non-deterministic nature of this communication makes parallel programs notoriously difficult to debug.

Parallel processing should be considered only after attempts at solving a problem sequentially prove too slow. Even then, attention should be restricted to algorithms that parallelize the problem by partitioning the input into distinct tasks where no communication is needed between the processors, except to collect the final results. Such large-grain, naive parallelism can be simple enough to be both implementable and debuggable, because it really reduces to producing a good sequential implementation.

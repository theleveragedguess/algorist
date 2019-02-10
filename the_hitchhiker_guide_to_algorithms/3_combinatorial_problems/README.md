# Combinatorial Problems

We are particularly interested in algorithms that rank and unrank combinatorial objects—i.e. , that map each distinct object to and from a unique integer. Rank and unrank operations make many other tasks simple, such as generating random objects (pick a random number and unrank) or listing all objects in order (iterate from $1$ to $n$ and unrank).

## Sorting

**Input description**: A set of $n$ items.  
**Problem description**: Arrange the items in increasing (or decreasing) order.

## Searching

**Input description**: A set of $n$ keys $S$, and a query key $q$.  
**Problem description**: Where is $q$ in $S$?

## Median and Selection

**Input description**: A set of $n$ numbers or keys, and an integer $k$.  
**Problem description**: Find the key smaller than exactly $k$ of the $n$ keys.

## Generating Permutations

**Input description**: An integer $n$.  
**Problem description**: Generate (1) all, or (2) a random, or (3) the next permutation of length $n$.

## Generating Subsets

**Input description**: An integer $n$.  
**Problem description**: Generate (1) all, or (2) a random, or (3) the next subset of the integers $\lbrace 1,...,n\rbrace$.

## Generating Partitions

**Input description**: An integer $n$.  
**Problem description**: Generate (1) all, or (2) a random, or (3) the next integer or set partitions of length $n$.

## Generating Graphs

**Input description**: Parameters describing the desired graph, including the number of vertices $n$, and the number of edges $m$ or edge probability $p$.  
**Problem description**: Generate (1) all, or (2) a random, or (3) the next graph satisfying the parameters.

## Calendrical Calculations

**Input description**: A particular calendar date $d$, specified by month, day, and year.  
**Problem description**: Which day of the week did $d$ fall on according to the given calendar system?

## Job Scheduling

**Input description**: A directed acyclic graph $G =(V,E)$, where vertices represent jobs and edge $(u,v)$ implies that task $u$ must be completed before task $v$.  
**Problem description**: What schedule of tasks completes the job using the minimum amount of time or processors?

## Satisfiability

**Input description**: A set of clauses in conjunctive normal form.  
**Problem description**: Is there a truth assignment to the Boolean variables such that every clause is simultaneously satisfied?

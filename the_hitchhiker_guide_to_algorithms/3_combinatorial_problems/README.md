# Combinatorial Problems

We are particularly interested in algorithms that rank and unrank combinatorial objects—i.e. , that map each distinct object to and from a unique integer. Rank and unrank operations make many other tasks simple, such as generating random objects (pick a random number and unrank) or listing all objects in order (iterate from 1 to n and unrank).

## Sorting

__Input description__: A set of $n$ items.  
__Problem description__: Arrange the items in increasing (or decreasing) order.

## Searching

__Input description__: A set of $n$ keys $S$, and a query key $q$.  
__Problem description__: Where is $q$ in $S$?

## Median and Selection

__Input description__: A set of $n$ numbers or keys, and an integer $k$.  
__Problem description__: Find the key smaller than exactly $k$ of the $n$ keys.

## Generating Permutations

__Input description__: An integer $n$.  
__Problem description__: Generate (1) all, or (2) a random, or (3) the next permutation of length $n$.

## Generating Subsets

__Input description__: An integer $n$.  
__Problem description__: Generate (1) all, or (2) a random, or (3) the next subset of the integers $\lbrace 1,...,n\rbrace$.

## Generating Partitions

__Input description__: An integer $n$.  
__Problem description__: Generate (1) all, or (2) a random, or (3) the next integer or set partitions of length $n$.

## Generating Graphs

__Input description__: Parameters describing the desired graph, including the number of vertices $n$, and the number of edges $m$ or edge probability $p$.  
__Problem description__: Generate (1) all, or (2) a random, or (3) the next graph satisfying the parameters.

## Calendrical Calculations

__Input description__: A particular calendar date $d$, specified by month, day, and year.  
__Problem description__: Which day of the week did $d$ fall on according to the given calendar system?

## Job Scheduling

__Input description__: A directed acyclic graph $G =(V,E)$, where vertices represent jobs and edge $(u,v)$ implies that task $u$ must be completed before task $v$.  
__Problem description__: What schedule of tasks completes the job using the minimum amount of time or processors?

## Satisfiability

__Input description__: A set of clauses in conjunctive normal form.  
__Problem description__: Is there a truth assignment to the Boolean variables such that every clause is simultaneously satisfied?

# Dynamic Programming

The most challenging algorithmic problems involve optimization, where we seek to ﬁnd a solution that maximizes or minimizes some function.  

Algorithms for optimization problems require proof that they always return the best possible solution. Greedy algorithms that make the best local decision at each step are typically efficient but usually do not guarantee global optimality. Exhaustive search algorithms that try all possibilities and select the best always produce the optimum result, but usually at a prohibitive cost in terms of time complexity.  

Dynamic programming combines the best of both worlds. It gives us a way to design custom algorithms that systematically search all possibilities (thus guaranteeing correctness) while storing results to avoid recomputing (thus providing efficiency). By storing the _consequences_ of all possible decisions and using this information in a systematic way, the total amount of work is minimized. Once you understand it, dynamic programming is probably the easiest algorithm design technique to apply in practice.  

Dynamic programming is a technique for efficiently implementing a recursive algorithm by storing partial results. The trick is seeing whether the naive recursive algorithm computes the same sub-problems over and over and over again.  

Dynamic programming is generally the right method for optimization problems on combinatorial objects that have an inherent _left to right_ order among components.  

## Caching vs. Computation

Dynamic programming is essentially a tradeoff of space for time. Repeatedly recomputing a given quantity is harmless unless the time spent doing so becomes a drag on performance. Then we are better off storing the results of the initial computation and looking them up instead of recomputing them again.  

### Fibonacci Numbers by Recursion

The Fibonacci numbers were originally defined by the Italian mathematician Fibonacci in the thirteenth century to model the growth of rabbit populations.  

$F_n = F_{n−1} + F_{n−2}$ with basis cases $F_0 = 0$ and $F_1 = 1$.  

A recursive function algorithm written in C looks like this:

```c
long fib_r(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return (fib_r(n - 1) + fib_r(n - 2));
}
```

How much time does this algorithm take to compute $F(n)$? Since $F_{n+1}/F_n \approx \varphi = (1+\sqrt{5})/2 \approx 1.61803$, this means that $F_n > 1.6^n$. Since our recursion tree has only $0$ and $1$ as leaves, summing up to such a large number means we must have at least $1.6^n$ leaves or procedure calls! This humble little program takes exponential time to run!  

### Fibonacci Numbers by Caching

In fact, we can do much better. We can explicitly store (or cache) the results of each Fibonacci computation $F(k)$ in a table data structure indexed by the parameter $k$. The key to avoiding recomputation is to explicitly check for the value before trying to compute it:

```c
#define MAXN 45     // largest interesting n
#define UNKNOWN -1  // contents denote an empty cell
long f[MAXN + 1];   // array for caching computed fib values


long fib_c(int n)
{
    if (f[n] == UNKNOWN)
        f[n] = fib_c(n - 1) + fib_c(n - 2);
    return f[n];
}

long fib_c_driver(int n)
{
    int i; // counter

    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++)
        f[i] = UNKNOWN;
    return fib_c(n);
}
```

This cached version runs instantly up to the largest value that can fot in a long integer.  

What is the running time of this algorithm? The recursion tree provides more of a clue than the code. In fact, it computes $F(n)$ in linear time (in other words, $O(n)$ time) because the recursive function ```fib_c(k)``` is called exactly twice for each value $0 \leq k \leq n$.  

Caching makes sense only when the space of distinct parameter values is modest enough that we can afford the cost of storage. Since the argument to the recursive function ```fib_c(k)``` is an integer between $0$ and $n$, there are only $O(n)$ values to cache. A linear amount of space for an exponential amount of time is an excellent tradeoff. But as we shall see, we can do even better by eliminating the recursion completely.  

__Explicit caching of the results of recursive calls provides most of the benefits of dynamic programming, including usually the same running time as the more elegant full solution.__  

### Fibonacci Numbers by Dynamic Programming

We can calculate $F_n$ in linear time more easily by explicitly specifying the order of evaluation of the recurrence relation:

```c
long fib_dp(int n)
{
    int i;            // counter
    long f[MAXN + 1]; // array to cache computed fib values

    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];

    return f[n];
}
```

 Each of the $n$ values is computed as the simple sum of two integers in total $O(n)$ time and space.  

 More careful study shows that we do not need to store all the intermediate values for the entire period of execution. Because the recurrence depends on two arguments, we only need to retain the last two values we have seen:

 ```c
 long fib_ultimate(int n)
{
    int i;                     // counter
    long back2 = 0, back1 = 1; // last two values of f[n]
    long next;                 // placeholder for sum

    if (n == 0)
        return 0;

    for (i = 2; i < n; i++)
    {
        next = back1 + back2;
        back2 = back1;
        back1 = next;
    }
    return (back1 + back2);
}
 ```

This analysis reduces the storage demands to constant space with no asymptotic degradation in running time.

### Binomial Coefficients

We now show how to compute the _binomial coefficients_ as another illustration of how to eliminate recursion by specifying the order of evaluation. The binomial coefficients are the most important class of counting numbers, where $\binom{n}{k}$ counts the number of ways to choose $k$ things out of $n$ possibilities.  

How do you compute the binomial coefficients? First, $\binom{n}{k} = \dfrac{n!}{(n-k)!k!}$, so in principle you can compute them straight from factorials and you know why you might not want that.  

A more stable way to compute binomial coefficients is using the recurrence relation implicit in the construction of Pascal’s triangle:  

![alt text](https://upload.wikimedia.org/wikipedia/commons/c/ca/Pascal_triangle_small.png "Pascal Triangle")

Each number is the sum of the two numbers directly above it. The recurrence relation implicit in this is that:  

$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$  

Why does this work? Consider whether the $n$th element appears in one of the
$\binom{n}{k}$ subsets of $k$ elements. If so, we can complete the subset by picking $k−1$ other items from the other $n−1$. If not, we must pick all $k$ items from the remaining $n−1$. There is no overlap between these cases, and all possibilities are included, so the sum counts all $k$ subsets.
This leaves us with a clean implementation:  

```c
long binomial_coefficient(n, m) int n, m; // computer n choose m
{
    int i, j;            // counters
    long bc[MAXN][MAXN]; // table of binomial coefficients

    for (i = 0; i <= n; i++)    // how many subsets of 0 elements for the set of i elements?
        bc[i][0] = 1;           // one! the empty one

    for (j = 0; j <= n; j++)    // how many subsets of j elements for the set of j elements?
        bc[j][j] = 1;           // one! the full one

    for (i = 1; i <= n; i++)
        for (j = 1; j < i; j++)
            bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];

    return bc[n][m];
}

```

## Approximate String Matching

Searching for patterns in text strings is a problem of unquestionable importance.  

How can we search for the substring closest to a given pattern to compensate for spelling errors? To deal with inexact string matching, we must first define a cost function telling us how far apart two strings are—i.e., a distance measure between pairs of strings. A reasonable distance measure reflects the number of changes that must be made to convert one string to another. There are three natural types of changes: _Substitution, Insertion, Deletion._  

### Edit Distance by Recursion

We can define a recursive algorithm using the observation that the last character in the string must either be matched, substituted, inserted, or deleted. Chopping off the characters involved in this last edit operation leaves a pair of smaller strings. Let $i$ and $j$ be the last character of the relevant prefix of $P$ and $T$, respectively. There are three pairs of shorter strings after the last operation, corresponding to the strings after a match/substitution, insertion, or deletion. If we knew the cost of editing these three pairs of smaller strings, we could decide which option leads to the best solution and choose that option accordingly. We can learn this cost through the magic of recursion.

```c
#define MATCH 0  // enumerated type symbol for match
#define INSERT 1 // enumerated type symbol for insert
#define DELETE 2 // enumerated type symbol for delete

int string_compare(char *s, char *t, int i, int j)
{
    int k;           // counter
    int opt[3];      // cost of the three options
    int lowest_cost; // lowest cost

    if (i == 0)
        return (j * indel(’ ’));

    if (j == 0)
        return (i * indel(’ ’));

    opt[MATCH] = string_compare(s, t, i - 1, j - 1) + match(s[i], t[j]);
    opt[INSERT] = string_compare(s, t, i, j - 1) + indel(t[j]);
    opt[DELETE] = string_compare(s, t, i - 1, j) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++)
        if (opt[k] < lowest_cost)
            lowest_cost = opt[k];

    return lowest_cost;
}
```

This algorithm is very slow. It takes exponential time because it recomputes values again and again and again. At every position in the string, the recursion branches three ways, meaning it grows at a rate of at least $3^n$—indeed, even faster since most of the calls reduce only one of the two indices, not both of them.

### Edit Distance by Dynamic Programming

The important observation is that most of these recursive calls are computing things that have been previously computed. How do we know? There can only be $|P|·|T|$ possible unique recursive calls, since there are only that many distinct $(i,j)$ pairs to serve as the argument parameters of recursive calls. By storing the values for each of these $(i,j)$ pairs in a table, we just look them up as needed and avoid recomputing them.  

```c
typedef struct
{
    int cost;   // cost of reaching this cell
    int parent; // parent cell
} cell;

cell m[MAXLEN + 1][MAXLEN + 1]; // dynamic programming table

int string_compare(char *s, char *t)
{
    int i, j, k; // counters
    int opt[3];  // cost of the three options

    for (i = 0; i < MAXLEN; i++)
    {
        row_init(i);
        column_init(i);
    }

    for (i = 1; i < strlen(s); i++)
    {
        for (j = 1; j < strlen(t); j++)
        {
            opt[MATCH] = m[i - 1][j - 1].cost + match(s[i], t[j]);
            opt[INSERT] = m[i][j - 1].cost + indel(t[j]);
            opt[DELETE] = m[i - 1][j].cost + indel(s[i]);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (k = INSERT; k <= DELETE; k++)
                if (opt[k] < m[i][j].cost)
                {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
        }
    }

    goal_cell(s, t, &i, &j);
    return m[i][j].cost;
}
```

Be aware that we adhere to somewhat unusual string and index conventions in the routine above. In particular, we assume that each string has been padded with an initial blank character, so the first real character of string $s$ sits in $s[1]$. Why did we do this? It enables us to keep the matrix $m$ indices in sync with those of the strings for clarity. Recall that we must dedicate the zeroth row and column of $m$ to store the boundary values matching the empty prefix. Alternatively, we could have left the input strings intact and just adjusted the indices accordingly.  

### Reconstructing the Path

The string comparison function returns the cost of the optimal alignment, but not the alignment itself. Knowing you can convert “thou shalt not” to “you should not” in only five moves is dandy, but what is the sequence of editing operations that does it?  

```c
void reconstruct_path(char *s, char *t, int i, int j)
{
    if (m[i][j].parent == -1)
        return;

    if (m[i][j].parent == MATCH)
    {
        reconstruct_path(s, t, i - 1, j - 1);
        match_out(s, t, i, j);
        return;
    }

    if (m[i][j].parent == INSERT)
    {
        reconstruct_path(s, t, i, j - 1);
        insert_out(t, j);
        return;
    }

    if (m[i][j].parent == DELETE)
    {
        reconstruct_path(s, t, i - 1, j);
        delete_out(s, i);
        return;
    }
}
```

### Varieties of Edit Distance

The ```string_compare``` and path reconstruction routines reference several functions that we have not yet defined. These fall into four categories:

* _Table Initialization_

```c
void row_init(int i)
{
    m[0][i].cost = i;
    if (i > 0)
        m[0][i].parent = INSERT;
    else
        m[0][i].parent = -1;
}

void column_init(int i)
{
    m[i][0].cost = i;
    if (i > 0)
        m[i][0].parent = DELETE;
    else
        m[i][0].parent = -1;
}
```

* _Penalty Costs_

```c
int match(char c, char d)
{
    if (c == d)
        return 0;
    else
        return 1;
}

int indel(char c)
{
    return 1
}
```

* _Goal Cell Identification_

```c
void goal_cell(char *s, char *t, int *i, int *j)
{
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}
```

* _Traceback Actions_

```c
void insert_out(char *t, int j)
{
     printf("I");
}

void delete_out(char *s, int i)
{
    printf("D");
}

void match_out(char *s, char *t, int i, int j)
{
    if (s[i] == t[j])
        printf("M");
    else
        printf("S");
}
```

This may seem to be a lot of infrastructure to develop for such a simple algorithm. However, several important problems can now be solved as special cases of edit distance using only minor changes to some of these stub functions:

* _Substring Matching_ – We want an edit distance search where the cost of starting the match is independent of the position in the text, so that a match in the middle is not prejudiced against. Now the goal state is not necessarily at the end of both strings, but the cheapest place to match the entire pattern somewhere in the text. Modifying these two functions gives us the correct solution:

```c
row_init(int i)
{
    m[0][i].cost = 0;    // note change
    m[0][i].parent = -1; // note change
}

goal_cell(char *s, char *t, int *i, int *j)
{
    int k; // counter
    *i = strlen(s) - 1;
    *j = 0;

    for (k = 1; k < strlen(t); k++)
        if (m[*i][k].cost < m[*i][*j].cost)
            *j = k;
}
```

* _Longest Common Subsequence_ – Perhaps we are interested in finding the longest scattered string of characters included within both strings.

A common subsequence is defined by all the identical-character matches in an edit trace. To maximize the number of such matches, we must prevent substitution of nonidentical characters. With substitution forbidden, the only way to get rid of the non-common subsequence is through insertion and deletion. The minimum cost alignment has the fewest such “in-dels”, so it must preserve the longest common substring. We get the alignment we want by changing the match-cost function to make substitutions expensive:

```c
int match(char c, char d)
{
    if (c == d)
        return 0;
    else
        returnMAXLEN;
}
```

As you can see, our edit distance routine can be made to do many amazing things easily. The trick is observing that your problem is just a special case of approximate string matching.

There are three steps involved in solving a problem by dynamic programming:

1. Formulate the answer as a recurrence relation or recursive algorithm.
2. Show that the number of different parameter values taken on by your recurrence is bounded by a (hopefully small) polynomial.
3. Specify an order of evaluation for the recurrence so the partial results you need are always available when you need them.

## The Partition Problem

_Problem_: Integer Partition without Rearrangement  
_Input_: An arrangement S of non negative numbers $\{s_1,...,s_n\}$ and an integer $k$.  
_Output_: Partition $S$ into $k$ or fewer ranges, to minimize the maximum sum over all the ranges, without reordering any of the numbers.  

This so-called linear partition problem arises often in parallel process. We seek to balance the work done across processors to minimize the total elapsed run time.  

Therefore, let us define $M[n,k]$ to be the minimum possible cost over all partitionings of $\{s_1,...,s_n\}$ into $k$ ranges, where the cost of a partition is the largest sum of elements in one of its parts. Thus defined, this function can be evaluated:

* $M[n,k]= \min_{i=1}^{n}max(M[i,k-1],\sum_{j=i+1}^{n}{s_j})$
* $M[1,k] = s_1$, for all $k>0$
* $M[n,1] = \sum_{i=1}^{n}{s_i}$

```c
void partition(int s[], int n, int k)
{
    int m[MAXN + 1][MAXK + 1]; // DP table for values
    int d[MAXN + 1][MAXK + 1]; // DP table for dividers
    int p[MAXN + 1];           // prefix sums array
    int cost;                  // test split cost
    int i, j, x;               // counters
    p[0] = 0;                  // construct prefix sums

    for (i = 1; i <= n; i++)
        p[i] = p[i - 1] + s[i];
    for (i = 1; i <= n; i++)
        m[i][1] = p[i]; // initialize boundaries
    for (j = 1; j <= k; j++)
        m[1][j] = s[1];

    for (i = 2; i <= n; i++) // evaluate main recurrence
        for (j = 2; j <= k; j++)
        {
            m[i][j] = MAXINT;
            for (x = 1; x <= (i - 1); x++)
            {
                cost = max(m[x][j - 1], p[i] - p[x]);
                if (m[i][j] > cost)
                {
                    m[i][j] = cost;
                    d[i][j] = x;
                }
            }
        }

    reconstruct_partition(s, d, n, k); // print book partition
}

void reconstruct_partition(int s[], int d[MAXN + 1][MAXK + 1], int n, int k)
{
    if (k == 1)
        print_books(s, 1, n);
    else
    {
        reconstruct_partition(s, d, d[n][k], k - 1);
        print_books(s, d[n][k] + 1, n);
    }
}

void print_books(int s[], int start, int end)
{
    int i; // counter
    for (i = start; i <= end; i++)
        printf(" %d ", s[i]);
    printf("\n");
}
```

## Limitations of Dynamic Programming

A main concern for dynamic programing is evaluation order. What can you evaluate first? Because there is no left-to-right or smaller-to-bigger ordering of the vertices on the graph, it is not clear what the smaller subprograms are. Without such an ordering, we get stuck in an infinite loop as soon as we try to do anything. Dynamic programming can be applied to any problem that observes the principle of optimality. Roughly stated, this means that partial solutions can be optimally extended with regard to the state after the partial solution, instead of the specifics of the partial solution itself. Future decisions are made based on the consequences of previous decisions, not the actual decisions themselves. Problems do not satisfy the principle of optimality when the specifics of the operations matter, as opposed to just the cost of the operations. Properly formulated, however, many combinatorial problems respect the principle of optimality.

__Without an inherent left-to-right ordering on the objects, dynamic programming is usually doomed to require exponential space and time.__

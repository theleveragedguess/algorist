# Dynamic Programming

The most challenging algorithmic problems involve optimization, where we seek to ﬁnd a solution that maximizes or minimizes some function.   
Algorithms for optimization problems require proof that they always return the best possible solution. Greedy algorithms that make the best local decision at each step are typically efficient but usually do not guarantee global optimality. Exhaustive search algorithms that try all possibilities and select the best always produce the optimum result, but usually at a prohibitive cost in terms of time complexity.     
Dynamic programming combines the best of both worlds. It gives us a way to design custom algorithms that systematically search all possibilities (thus guaranteeing correctness) while storing results to avoid recomputing (thus providing efficiency). By storing the _consequences_ of all possible decisions and using this information in a systematic way, the total amount of work is minimized. Once you understand it, dynamic programming is probably the easiest algorithm design technique to apply in practice.     
Dynamic programming is a technique for efficiently implementing a recursive algorithm by storing partial results. The trick is seeing whether the naive recursive algorithm computes the same subproblems over and over and over again.    
Dynamic programming is generally the right method for optimization problems on combinatorial objects that have an inherent _left to right_ order among components.   

## Caching vs. Computation

Dynamic programming is essentially a tradeoff of space for time. Repeatedly recomputing a given quantity is harmless unless the time spent doing so becomes a drag on performance. Then we are better off storing the results of the initial computation and looking them up instead of recomputing them again.    

__Fibonacci Numbers by Recursion__    

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

__Fibonacci Numbers by Caching__    

In fact, we can do much better. We can explicitly store (or cache) the results of each Fibonacci computation $F(k)$ in a table data structure indexed by the parameter $k$. The key to avoiding recomputation is to explicitly check for the value before trying to compute it:

```c
#define MAXN 45     // largest interesting n
#define UNKNOWN - 1 // contents denote an empty cell 
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
What is the running time of this algorithm? The recursion tree provides more of a clue than the code. In fact, it computes $F(n)$ in linear time (in other words, $O(n)$ time) because the recursive function ```fib c(k)``` is called exactly twice for each value $0 \leq k \leq n$.    
Caching makes sense only when the space of distinct parameter values is modest enough that we can afford the cost of storage. Since the argument to the recursive function ```fib c(k)``` is an integer between $0$ and $n$, there are only $O(n)$ values to cache. A linear amount of space for an exponential amount of time is an excellent tradeoff. But as we shall see, we can do even better by eliminating the recursion completely.    

__Explicit caching of the results of recursive calls provides most of the benefits of dynamic programming, including usually the same running time as the more elegant full solution.__   

__Fibonacci Numbers by Dynamic Programming__    

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

__Binomial Coefficients__    

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

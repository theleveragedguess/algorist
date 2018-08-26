# Algorithm Analysis

The two most important tools to compare the efficiency of algorithms without implementing them:
* The RAM model of computation
* The asymptotic analysis of worst-case complexity

## The RAM Model of Computation

Machine-independent algorithm design depends upon a hypothetical computer called the Random Access Machine or RAM, where:
* Each _simple_ operation (+, *, - =, if, call) takes exactly one time step.
* Loops and subroutines are not considered simple operations.
* Each memory access takes exactly one time step.

To understand how good or bad an algorithm is in general, we must know how it works over _all_ instances:
* The _worst-case complexity_.
* The _best-case complexity_.
* The _average-case complexity_.

The important thing to realize is that each of the these time complexities define a numerical function, representing time (in steps) versus problem size. But time complexities are such complicated functions that we must simplify them to work with them. For this we need the "Big Oh" notation.

## The Big Oh Notation

Time complexity functions are very difficult to work precisely with because they tend _to have too many bumps_ and _require too much detail to specify precisely_. We just need to reason with upper and lower bounds. The Big Oh simplifies our analysis by ignoring levels of detail that do not impact our comparison.

* $f(n) = O(g(n))$ means $c.g(n)$ is an _upper bound_ on $f(n)$ thus there exists some constant $c$ such that $f(n)$ is always $\leq c.g(n)$ for large enough $n$ (i.e $n \geq n_0$ for some constant $n_0$).
* $f(n) = Ω(g(n))$ means $c.g(n)$ is a _lower bound_ on $f(n)$ thus there exists some constant $c$ such that $f(n)$ is always $\geq c.g(n)$ for large enough $n$.
* $f(n) = \Theta(g(n))$ means $c_1.g(n)$ is an _upper bound_ on $f(n)$ and $c_2.g(n)$ is a _lower bound_ on $f(n)$ thus there exists constants $c_1$ and $c_2$ such that $f(n)$ is always $\leq c_1.g(n)$ and $f(n) \geq c_2.g(n)$ for large enough $n$.

## Growth Rates and Dominance Relations

* Any algorithm with $n!$ running time becomes useless for $n \geq 20$.
* Algorithms whose running time is $2^n$ have a greater operating range, but become impractical for $n > 40$.
* Quadratic-time algorithms whose running time is $n^2$ remain usable up to about $n = 10,000$, but quickly deteriorate with larger inputs. They are likely to be hopeless for $n > 1,000,000$.
* Linear-time and $n.\lg{n}$ algorithms remain practical on inputs of one billion items.
* An $O(lg(n))$ hardly breaks a sweat for any imaginable value of $n$.

__Dominance Relations__

The Big Oh notation groups functions into a set of classes, such that all the functions in a particular class are equivalent with respect to the Big Oh.
We say that a faster-growing function _dominates_ a slower-growing one.

Only a few functions classes tend to occur in the course of basic algorithm analysis
* _Constant functions_: $f(n) = 1$
* _Logarithmic functions_: $f(n) = \log{n}$
* _Linear functions_: $f(n) = n$
* _Super linear functions_: $f(n) = n\log{n}$
* _Quadratic functions_: $f(n) = n^2$
* _Cubic functions_: $f(n) = n^3$
* _Exponential functions_: $f(n) = c^n$
* _Factorial functions_: $f(n) = n!$

Although esoteric functions arise in advanced algorithm analysis, a small variety of time complexities suffice and account for most algorithms that are widely used in practice.

## Working with the Big Oh

On simplifications of algebraic expressions

__Adding Functions__
* $O(f(n) + O(g(n))) = O(\max(f(n), g(n)))$
* $Ω(f(n) + Ω(g(n))) = Ω(\max(f(n), g(n)))$
* $\Theta(f(n) + \Theta(g(n))) = \Theta(\max(f(n), g(n)))$

Everything is small potatoes besides the dominant terms

__Multiplying Functions__
* $O(c.f(n)) = O(f(n))$
* $Ω(c.f(n)) = Ω(f(n))$
* $\Theta(c.f(n)) = \Theta(f(n))$
* $O(f(n)) . O(g(n)) = O(f(n).g(n))$
* $Ω(f(n)) . Ω(g(n)) = Ω(f(n).g(n))$
* $\Theta(f(n)) . \Theta(g(n)) = \Theta(f(n).g(n))$

## Reasoning about Efficiency

* __Selection Sort__ is $O(n^2)$.

```c
void selection_sort(int s[], int n)
{
    int i,j;    // counters;
    int min;    // index of minimum

    for(i=0; i<n; i++)
    {
        min=i;
        for(j=i+1; j<n; j++)
        {
            if(s[j] < s[min]) min = j;
        }
        swap(&s[i], &s[min]);
    }
}
```

* __Insertion Sort__ is $O(n^2)$.

```c
for(i=0; i<n; i++)
{
    j=i;
    while(j>0 && (s[j] < s[j-1]))
    {
        swap(&s[i], &s[min]);
        j = j-1;
    }
}
```
* __String Pattern Match__ is $O(n.m)$ where $m$ is the length of the string we're trying to find in the string of length $n$.

```c
int findmatch(char *p, char *t)
{
    int i,j;    // counters
    int m,n;    // string lengths

    m = strlen(p);
    n = strlen(t);

    for(i=0; i<=(n-m); i=i+1)
    {
        j=0;
        while(j<m && (t[i+j]==p[j]))
            j = j+1;
        if (j == m) return i;
    }

    return -1;

}
```
* __Matrix Multiplication__ is $O(n^3)$.

```c
for(i=1; i<=x; i++)
{
    for(j=1; j<=z; j++)
    {
        C[i][j] = 0;
        for(k=1; k<=y; k++)
            C[i][j] += A[i][k] * B[k][j];
    }
}
```

## Logarithms and Their Applications

Logarithm is an anagram of algorithm, but that's not why we need to know what logarithms are. A _logarithm_ is simply an inverse exponential function. $b^x = y$ so $x = \log_b{y}$
Logarithms arise whenever things are repeatedly halved or doubled.

## Properties of Logarithms

* Base $b = 2$ the _binary logarithm_ or $\lg{x}$
* Base $b = e$ the _natural log_ or $\ln{x}$
* Base $b = 10$ the _common logarithm_ or $\log{x}$
* $\log_a{x.y} = \log_a{x} + \log_a{y}$
* $\log_a{n^b} = b.\log_a{n}$
* $\log_a{b} = \dfrac{\log_c{b}}{\log_c{a}}$

* _The base of the algorithm has no real impact on the growth rate_ Thus we are usually justified in ignoring the base of the logarithm when analyzing algorithms.
* _Logarithms cut any thing down to size_ The growth rate of the logarithm of any polynomial function is $O(\lg{n})$ because $\log_a{n^b} = b\log_a{n}$.

 ## Advanced Analysis

 __Esoteric Functions__

 * Inverse Ackermann's function — $f(n) = α(n)$ the slowest-growing complexity function
 * $f(n) = \log{\log{n}}$ — the log log function i.e binary search on a sorted array of $\log{n}$ items
 * $f(n) = \dfrac{\log{n}}{\log{\log{n}}}$ — i.e. height of tree of degree $\log{n}$
 * $f(n) = \log{n}^2$ — The log squared i.e intricate nested data structures
 * $f(n) = \sqrt{n}$ — the square root i.e for d-dimensional hypercubes of length $n^{1/d}$ on each side with volume $d$
 * $f(n) = n^{1+ε}$ — to simplify algorithms that runs in $2^c.n^{(1+1/c)}$

 __Limits and Dominance Relations__

 We say that $f(n)$ dominates $g(n)$ if $\lim_{n\to\infty} g(n)/f(n) = 0$.
 The higher-Degree polynomial dominates even for $n^{1.2}$ and $n^{1.1999999}$.
 The exponential with the higher base dominates.

$n! \gg c^n \gg n^3 \gg n^2 \gg n^{1+ε} \gg n\log{n} \gg n \gg \sqrt{n} \gg \log^2{n} \gg log{n} \gg \dfrac{\log{n}}{\log{\log{n}}} \gg \log{\log{n}} \gg α(n) \gg 1$

## For the Road

* $f(n) = o(g(n))$ means $c.g(n)$ is a _theoretical upper bound_ on $f(n)$ thus for every constant $c$ we are sure that $f(n)$ is always $\leq c.g(n)$ for large enough $n$ (i.e $n \geq n_0$ for some constant $n_0$).
* $f(n) = ω(g(n))$ means $c.g(n)$ is a _theoretical lower bound_ on $f(n)$ thus for every constant $c$ we are sure that $f(n)$ is always $\geq c.g(n)$ for large enough $n$.

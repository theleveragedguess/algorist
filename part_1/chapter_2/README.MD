# Algorithm Analysis

The two most important tools to compare the efficiency of algorithms without implementing them:
* The RAM model of computation
* The asymptotic analysis of worst-case complexity

## The RAM Model of Computation

Machine-independent algorithm design depends upon a hypothetical computer called the Random Access Machine or RAM, where:
* Each _simple_ operation (+, *, - =, if, call) takes exactly one time step
* Loops and subroutines are not considered simple operations
* Each memory access takes exactly one time step
 
To understand how good or bad an algorithm is in general, we must know how it works over _all_ instances:
* The _worst-case complexity_
* The _best-case complexity_
* The _average-case complexity_

The important thing to realize is that each of the these time complexities define a numerical function, representing time (in steps) versus problem size. But time complexities are such complicated functions that we must simplify them to work with them. For this we need the "Big Oh" notation.

## The Big Oh Notation

Time complexity functions are very difficult to work precisely with because they tend _to have too many bumps_ and _require too much detail to specify precisely_. We just need to reason with upper and lower bounds. The Big Oh simplifies our analysis by ignoring levels of detail that do not impact our comparison.
* _f(n)_ => _O(g(n))_ means _c.g(n)_ is an _upper bound_ on _f(n)_ thus there exists some constant _c_ such that _f(n)_ is always <= _c.g(n)_ for large enough _n_ (i.e _n_ >= _n0_ for some constant _n0_).
* _f(n)_ => _Ω(g(n))_ means _c.g(n)_ is a _lower bound_ on _f(n)_ thus there exists some constant _c_ such that _f(n)_ is always >= _c.g(n)_ for large enough _n_.
* _f(n)_ => _θ(g(n))_ means _c1.g(n)_ is an _upper bound_ on _f(n)_ and _c2.g(n)_ is a _lower bound_ on _f(n)_ thus there exists constants _c1_ and _c2_ such that _f(n)_ is always <= _c1.g(n)_ and _f(n)_ >= _c2.g(n)_ for large enough _n_.

## Growth Rates and Dominance Relations

* Any algorithm with _n!_ running time becomes useless for _n_ >= 20.
* Algorithms whose running time is _2^n_ have a greater operating range, but become impractical for _n_ > 40.
* Quadratic-time algorithms whose running time is _n^2_ remain usable up to about _n_ = 10,000, but quickly deteriorate with larger inputs. They are likely to be hopeless for _n_ > 1,000,000.
* Linear-time and _n.lg(n)_ algorithms remain practical on inputs of one billion items.
* An _O(lg(n))_ hardly breaks a sweat for any imaginable value of _n_.

__Dominance Relations__  
The Big Oh notation groups functions into a set of classes, such that all the functions in a particular class are equivalent with respect to the Big Oh.
We say that a faster-growing function _dominates_ a slower-growing one.

Only a few functions classes tend to occur in the course of basic algorithm analysis
* _Constant functions_ f(n) = 1
* _Logarithmic functions_ f(n) = log(n)
* _Linear functions_ f(n) = n
* _Superlinear functions_ f(n) = n.log(n)
* _Quadratic functions_ f(n) = n^2
* _Cubic functions_  f(n) = n^3
* _Exponential functions_ f(n) = c^n
* _Factorial functions_ f(n) = n!

Although esoteric functions arise in advanced algorithm analysis, a small variety of time complexities suffice and account for most algorithms that are widely used in practice.

## Working with the Big Oh

On simplifications of algebraic expressions

__Adding Functions__
* O(f(n) + O(g(n))) => O(max(f(n), g(n)))
* Ω(f(n) + Ω(g(n))) => Ω(max(f(n), g(n)))
* θ(f(n) + θ(g(n))) => θ(max(f(n), g(n)))

Everything is small potatoes besides the dominant terms

__Multiplying Functions__
* O(c.f(n)) => O(f(n))
* Ω(c.f(n)) => Ω(f(n))
* θ(c.f(n)) => θ(f(n))
* O(f(n)) . O(g(n)) => O(f(n).g(n))
* Ω(f(n)) . Ω(g(n)) => Ω(f(n).g(n))
* θ(f(n)) . θ(g(n)) => θ(f(n).g(n))

## Reasoning about Efficiency

* __Selection Sort__ is O(n^2).
* __Insertion Sort__ is O(n^2).
* __String Pattern Match__ is O(n.m) where _m_ is the length of the string we're trying to find in the string of length _n_.
* __Matrix Multiplication__ is O(n^3).

## Logarithms and Their Applications

Logarithm is an anagram of algorithm, but that's not why we need to know what logarithms are. A _logarithm_ is simply an inverse exponential function. _b^x = y_ so _x = log\<b\>(y)_
Logarithms arise whenever things are repeatedly halved or doubled

## Properties of Logarithms

* Base b = 2 the _binary logarithm_ or lg(x)
* Base b = _e_ the _natural log_ or ln(x)
* Base b = 10 the _common logarithm_ or log(x)
* log\<a\>(x.y) = log\<a\>(x) + log\<a\>(y)
* log\<a\>(n^b) = b.log\<a\>(n)
* log\<a\>(b) = log\<c\>(b)/log\<c\>(a)

* _The base of the algorithm has no real impact on the growth rate_ Thus we are usually justified in ignoring the base of the logarithm when analyzing algorithms.
* _Logarithms cut any thing down to size_ The growth rate of the logarithm of any polynomial function is _O(lg(n))_ because _log\<a\>(n^b) = b.log\<a\>(n)_.
 
 ## Advanced Analysis

 __Esoteric Functions__
 * Inverse Ackermann's function, f(n) = α(n) the slowest-growing complexity function
 * f(n) = log(log(n)) the log log function i.e binary search on a sorted array of log(n) items
 * f(n) = log(n)/(log(n).log(n)) i.e height of tree of degree log(n)
 * f(n) = log(n)^2 The log squared i.e intricate nested data structures
 * f(n) = sqrt(n) the square root i.e for d-dimensional hypercubes of length n^(1/d) on each side with volume d
 * f(n) = n^(1+ε) to simplify algorithms that runs in (2^c).(n^(1+(1/c)))

 __Limits and Dominance Relations__  
 We say that _f(n)_ dominates _g(n)_ if _lim\<n to ∞\>g(n)/f(n) = 0_.  
 The higher-Degree polynomial dominates even for _n^1.2_ and _n^1.1999999_.  
 The exponential with the higher base dominates.

 n! > c^n > n^3 > n^2 > n^(1+ε) > n.log(n) > n > sqrt(n) > log(n)^2 > log(n) > log(n)/(log(n).log(n)) > log(log(n)) > α(n) > 1
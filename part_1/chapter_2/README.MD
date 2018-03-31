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

* Any algorithm with _n!_ running time becomes useless for _n >= 20_.
* Algorithms whose running time is _2^n_ have a greater operating range, but become impractical for _n > 40_.
* Quadratic-time algorithms whose running time is _n^2_ remain usable up to about _n = 10,000_, but quickly deteriorate with larger inputs. They are likely to be hopeless for _n > 1,000,000_.
* Linear-time and _n.lg(n)_ algorithms remain practical on inputs of one billion items.
* An _O(lg(n))_ hardly breaks a sweat for any imaginable value of _n_.

__Dominance Relations__
The Big Oh notation groups functions into a set of classes, such that all the functions in a particular class are equivalent with respect to the Big Oh.
We say that a faster-growing function _dominates_ a slower-growing one.

Only a few functions classes tend to occur in the course of basic algorithm analysis
* _Constant functions f(n) = 1_
* _Logarithmic functions f(n) = log(n)_
* _Linear functions f(n) = n_
* _Superlinear functions f(n) = n.log(n)_
* _Quadratic functions f(n) = n^2_
* _Cubic functions f(n) = n^3_
* _Exponential functions f(n) = c^n_
* _Factorial functions f(n) = n!_

Although esoteric functions arise in advanced algorithm analysis, a small variety of time complexities suffice and account for most algorithms that are widely used in practice.

## Working with the Big Oh

On simplifications of algebraic expressions

__Adding Functions__
* _O(f(n) + O(g(n))) => O(max(f(n), g(n)))_
* _Ω(f(n) + Ω(g(n))) => Ω(max(f(n), g(n)))_
* _θ(f(n) + θ(g(n))) => θ(max(f(n), g(n)))_

Everything is small potatoes besides the dominant terms

__Multiplying Functions__
* _O(c.f(n)) => O(f(n))_
* _Ω(c.f(n)) => Ω(f(n))_
* _θ(c.f(n)) => θ(f(n))_
* _O(f(n)) . O(g(n)) => O(f(n).g(n))_
* _Ω(f(n)) . Ω(g(n)) => Ω(f(n).g(n))_
* _θ(f(n)) . θ(g(n)) => θ(f(n).g(n))_

## Reasoning about Efficiency

* __Selection Sort__ is _O(n^2)_.
* __Insertion Sort__ is _O(n^2)_.
* __String Pattern Match__ is _O(n.m)_ where _m_ is the length of the string we're trying to find in the string of length _n_.
* __Matrix Multiplication__ is _O(n^3)_.

## Logarithms and Their Applications

Logarithm is an anagram of algorithm, but that's not why we need to know what logarithms are. A _logarithm_ is simply an inverse exponential function. _b^x = y_ so _x = log\<b\>(y)_
Logarithms arise whenever things are repeatedly halved or doubled

## Properties of Logarithms

* Base _b_ = 2 the _binary logarithm_ or _lg(x)_
* Base _b_ = _e_ the _natural log_ or _ln(x)_
* Base _b_ = 10 the _common logarithm_ or _log(x)_
* _log\<a\>(x.y) = log\<a\>(x) + log\<a\>(y)_
* _log\<a\>(n^b) = b.log\<a\>(n)_
* _log\<a\>(b) = log\<c\>(b)/log\<c\>(a)_

* _The base of the algorithm has no real impact on the growth rate_ Thus we are usually justified in ignoring the base of the logarithm when analyzing algorithms.
* _Logarithms cut any thing down to size_ The growth rate of the logarithm of any polynomial function is _O(lg(n))_ because _log\<a\>(n^b) = b.log\<a\>(n)_.

 ## Advanced Analysis

 __Esoteric Functions__
 * Inverse Ackermann's function, _f(n) = α(n)_ the slowest-growing complexity function
 * _f(n) = log(log(n))_ the log log function i.e binary search on a sorted array of _log(n)_ items
 * _f(n) = log(n)/(log(n).log(n))_ i.e height of tree of degree _log(n)_
 * _f(n) = log(n)^2_ The log squared i.e intricate nested data structures
 * _f(n) = sqrt(n)_ the square root i.e for d-dimensional hypercubes of length _n^(1/d)_ on each side with volume _d_
 * _f(n) = n^(1+ε)_ to simplify algorithms that runs in _(2^c).(n^(1+(1/c)))_

 __Limits and Dominance Relations__
 We say that _f(n)_ dominates _g(n)_ if _lim\<n to ∞\>g(n)/f(n) = 0_.
 The higher-Degree polynomial dominates even for _n^1.2_ and _n^1.1999999_.
 The exponential with the higher base dominates.

_n! > c^n > n^3 > n^2 > n^(1+ε) > n.log(n) > n > sqrt(n) > log(n)^2 > log(n) > log(n)/(log(n).log(n)) > log(log(n)) > α(n) > 1_

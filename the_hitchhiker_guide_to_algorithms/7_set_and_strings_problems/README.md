# Set and String Problems

## Set Cover

__Input description__: A collection of subsets $S = \lbrace S_1,...,S_m \rbrace$ of the universal set $U = \lbrace 1,...,n \rbrace$.  
__Problem description__: What is the smallest subset $T$ of $S$ whose union equals the universal set—i.e. , $\bigcup_{i=1}^{|T|} = U$?

## Set Packing

__Input description__: A set of subsets $S = \lbrace S_1,...,S_m \rbrace$ of the universal set $U = \lbrace 1,...,n \rbrace$.  
__Problem description__: Select (an ideally small) collection of mutually disjoint subsets from $S$ whose union is the universal set.

## String Matching

__Input description__: A text string $t$ of length $n$. A pattern string $p$ of length $m$.  
__Problem description__: Find the first (or all) instances of pattern $p$ in the text.

## Approximate String Matching

__Input description__: A text string $t$ and a pattern string $p$.  
__Problem description__: What is the minimum-cost way to transform $t$ to $p$ using insertions, deletions, and substitutions?

## Text Compression

__Input description__: A text string $S$.  
__Problem description__: Create a shorter text string $S'$ such that $S$ can be correctly reconstructed from $S'$.

## Cryptography

__Input description__: A plaintext message $T$ or encrypted text $E$, and a key $k$.  
__Problem description__: Encode $T$ (decode $E$) using $k$ giving $E$ ($T$).

## Finite State Machine Minimization

__Input description__: A deterministic finite automaton $M$.  
__Problem description__: Create the smallest deterministic finite automaton $M'$ such that $M'$ behaves identically to $M$.

## Longest Common Substring/Subsequence

__Input description__: A set $S$ of strings $S_1,...,S_n$.  
__Problem description__: What is the longest string $S'$ such that all the characters of $S'$ appear as a substring or subsequence of each $S_i, 1 \le i ≤ n$?

## Shortest Common Superstring

__Input description__: A set $S$ of strings $S_1,...,S_n$.  
__Problem description__: Find the shortest string $S'$ that contains each string $S_i$ as a substring of $S'$.

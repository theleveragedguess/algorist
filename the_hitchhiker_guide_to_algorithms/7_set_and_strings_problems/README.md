# Set and String Problems

## Set Cover

**Input description**: A collection of subsets $S = \lbrace S_1,...,S_m \rbrace$ of the universal set $U = \lbrace 1,...,n \rbrace$.
**Problem description**: What is the smallest subset $T$ of $S$ whose union equals the universal set—i.e. , $\bigcup_{i=1}^{|T|} = U$?

## Set Packing

**Input description**: A set of subsets $S = \lbrace S_1,...,S_m \rbrace$ of the universal set $U = \lbrace 1,...,n \rbrace$.
**Problem description**: Select (an ideally small) collection of mutually disjoint subsets from $S$ whose union is the universal set.

## String Matching

**Input description**: A text string $t$ of length $n$. A pattern string $p$ of length $m$.
**Problem description**: Find the first (or all) instances of pattern $p$ in the text.

## Approximate String Matching

**Input description**: A text string $t$ and a pattern string $p$.
**Problem description**: What is the minimum-cost way to transform $t$ to $p$ using insertions, deletions, and substitutions?

## Text Compression

**Input description**: A text string $S$.
**Problem description**: Create a shorter text string $S'$ such that $S$ can be correctly reconstructed from $S'$.

## Cryptography

**Input description**: A plaintext message $T$ or encrypted text $E$, and a key $k$.
**Problem description**: Encode $T$ (decode $E$) using $k$ giving $E$ ($T$).

## Finite State Machine Minimization

**Input description**: A deterministic finite automaton $M$.
**Problem description**: Create the smallest deterministic finite automaton $M'$ such that $M'$ behaves identically to $M$.

## Longest Common Substring/Subsequence

**Input description**: A set $S$ of strings $S_1,...,S_n$.
**Problem description**: What is the longest string $S'$ such that all the characters of $S'$ appear as a substring or subsequence of each $S_i, 1 \le i ≤ n$?

## Shortest Common Superstring

**Input description**: A set $S$ of strings $S_1,...,S_n$.
**Problem description**: Find the shortest string $S'$ that contains each string $S_i$ as a substring of $S'$.

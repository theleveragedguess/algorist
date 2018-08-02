#pragma once

namespace combinatorics
{
    typedef unsigned int uint;

    uint factorial(const uint upper, const uint lower = 1);

    uint subsetCount(const uint n, const uint r);

    // This invertible, deterministic function produce an unique sequencing index for a subset r of a set n
    // the index is between 0 and subsetCount(n,r)-1
    // We assume the subset is given in its unique ascending ordering, otherwise the function will be wrong
    uint linearizeSubset(const uint n, const uint r, const uint* subset);

    // This is the inverse function of linearizeSubset
    // The outputted subset is in its unique ascending ordering
    void unlinearizeSubset(const uint n, const uint r, const uint linearIndex, uint* subset);
}
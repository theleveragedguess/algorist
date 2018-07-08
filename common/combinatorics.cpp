#include <algorithm>
#include "combinatorics.h"

using namespace combinatorics;

uint combinatorics::factorial(const uint upper, const uint lower)
{
    //This factorial function can stop before 1 if needed

    if(upper <= 1 || lower > upper) return 1;

    uint factorial = upper;
    for(uint i = upper - 1; i >= std::max(lower, 1u); i--)
        factorial *= i;

    return factorial;
}

uint combinatorics::subsetCount(const uint n, const uint r)
{
    // We'll use the subset count formula C(n,r)= n!/(r!(n-r)!)

    if(r == 0) return 1;
    if(r > n) return 0;

    // We factorize a lower part of the dividend factorial with the biggest factorial of the divisor
    // To save instructions and try to avoid the MAX_UINT while doing intermediate computations
    const uint lower = std::max(r, n-r);
    const uint divisor = std::min(r, n-r);
    return factorial(n, lower+1) / factorial(divisor);
}

uint combinatorics::linearizeSubset(const uint n, const uint r, const uint* subset)
{
    // For each subset we'll use its unique ascending ordering {2,6,5,1} => {1,2,5,6}
    // The sequencing index is simply the subset rank in an ascending order where each subset is represented by it's unique ascending ordering
    // for n=6, r=4 {1,2,3,4} => 0; {1,2,3,5} => 1; {3,4,5,6} => 15; (15 == subsetCount(6,4))

    uint rank = 0u; // We'll start with the lowest rank and keep ascending until the right one
    for(uint ri = 0u; ri < r; ri++)
    {
        // We'll process the ranking slot by slot
        // For each slot, we'll go from the smallest value possible until the actual subset slot value
        // While doing so, we'll add to the rank the number of all the subsets that have been overtaken
        // When all the precedent subset have been overtaken for all the slots, we'll have the right rank

        const uint from = ri > 0 ? subset[ri-1]+1 : ri+1;
        const uint to = subset[ri];

        for(uint ni = from; ni < to; ni++)
            rank += subsetCount(n - ni, r - (ri+1));
    }

    return rank;
}

void combinatorics::unlinearizeSubset(const uint n, const uint r, const uint linearIndex, uint* subset)
{
    uint rank = 0u; // We'll be using an operative rank to track our research progress in the subset's slots
    for(uint ri = 0u; ri < r; ri++)
    {
        //We'll be looking for the slot value that covers the index

        //Minimal Slot value
        uint candidate = ri > 0u ? subset[ri-1]+1 : 1u;

        bool found = false;
        while (!found)
        {
            // the amount of subsets that are covered by this slot value
            uint candidateRange = subsetCount(n - candidate,  r - (ri + 1));

            // if the index is in the range, we have the right slot value
            if( linearIndex < rank + candidateRange )
                found = true;
            else{
                rank = rank + candidateRange;
                candidate++;
            }
        }
        subset[ri] = candidate;
    }
}

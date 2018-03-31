
#pragma once
#include <string>
namespace part_one_chapter_one 
{

    struct LottoPsychicInput
    {
        unsigned int n; // The size of the candidate Set S of promised numbers
        unsigned int k; // The count of numbers per ticket
        unsigned int j; // The minimum count of promised numbers from S in a ticket
        unsigned int l; // The minimum matching numbers in a ticket to win a prize
    };
    

    // Find a set of tickets of input.k slots that guarantees a prize win (i.e covers all l subset of input.n)
    void lottoPsychic(LottoPsychicInput input);
}
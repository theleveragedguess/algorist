#include <list>
#include <iostream>
#include <functional>
#include "common/combinatorics.h"
#include "programs.h"

using namespace combinatorics;

uint* createTicket(uint k)
{
    uint* ticket = new uint[k];
    for(uint i = 0; i < k; i++)
        ticket[i] = 0;
    return ticket;
}

bool isSubsetFillableInTicket(
    const uint* subset, const uint subsetSize,
    const uint* ticket, const uint ticketSize,
    bool *filledSlotsOfSubset, bool *alreadyFilled)
{
    uint freeTicketSlotCount = ticketSize;
    for(uint ki = 0u; ki < ticketSize; ki++)
        if(ticket[ki] != 0)
            freeTicketSlotCount--;

    uint unfilledSlotCount = subsetSize;
    for(uint li = 0u; li < subsetSize; li++)
    {
        filledSlotsOfSubset[li] = false;

        uint k = 0u;
        while(  filledSlotsOfSubset[li] != true 
            &&  k < ticketSize)
        {
            if(subset[li] == ticket[k++])
            {
                filledSlotsOfSubset[li] = true;
                unfilledSlotCount--;
            }       
        }
    }

    *alreadyFilled = unfilledSlotCount == 0u;

    return freeTicketSlotCount >= unfilledSlotCount;
}

void fillSubsetInTicket(
    const uint* subset, const uint subsetSize,
    const uint* ticket, const uint ticketSize,
    uint* filledTicket)
{
    // We'll going to merge the subset and ticket slots inside the filledTicket
    // For each slot we'll take the smallest of the two 
    uint ki = 0u; // The next ticket slot to use
    uint li = 0u; // the next subset slot to use
    for(uint fki = 0u; fki < ticketSize; fki++)
    {
        // We'll skip all the zeros
        while(ki < ticketSize && ticket[ki] == 0)
            ki++;

        bool useK = ki < ticketSize;
        bool useL = li < subsetSize;
        
        if( useK && useL )
        {
            if(ticket[ki] < subset[li])
                useL = false;
            else if(ticket[ki] > subset[li])
                useK = false;
            else
            {
                useL = false;
                li++;
            }
        }

        if(useK)
            filledTicket[fki] = ticket[ki++];
        else if(useL)
            filledTicket[fki] = subset[li++];
        else
            filledTicket[fki] = 0u;                    
    }
}

void loopThroughSubsetsOfTicket(
    const uint* ticket, const uint ticketSize,
    const uint subsetSize,
    const std::function <void (const uint*)>& processSubset
)
{
    uint* ticketSubset = new uint[subsetSize];
    const uint ticketSubsetCount = subsetCount(ticketSize, subsetSize);
    for(uint tli = 0u; tli < ticketSubsetCount; tli++)
    {
        unlinearizeSubset(ticketSize, subsetSize, tli, ticketSubset);
        processSubset(ticketSubset);
    }
    delete ticketSubset;
}

void part_one_chapter_one::lottoPsychic(part_one_chapter_one::LottoPsychicInput input)
{
    uint lSubsetCount = subsetCount(input.n, input.l);
    if(lSubsetCount <= 0) throw "bad input or possibilities too big";

    bool* coveredLSubsets = new bool[lSubsetCount];
    uint* subset = new uint[input.l]; // An operative variable representing a subset
    uint* ticket = createTicket(input.k); // An operative variable representing a ticket
    bool* filledSlotsOfSubset = new bool[input.l]; // An operative variable representing the slots of a subset that have been filed in a ticket
    std::list<uint*> tickets; // An operative variable representing the list of elected tickets

    for(uint i = 0u; i < lSubsetCount; i++)
        coveredLSubsets[i] = false;

    tickets.push_back(createTicket(input.k));

    for(uint si = 0u; si < lSubsetCount; si++)
    {
        if(coveredLSubsets[si] == true)
            continue;

        unlinearizeSubset(input.n, input.l, si, subset);
        
        // Fill the subset in one of our tickets, otherwise create a ticket that holds it
        auto ticketIt = tickets.begin();
        bool filled = false;
        uint* newTicket = NULL;
        while(!filled && ticketIt != tickets.end())
        {
            bool fillable = isSubsetFillableInTicket(
                subset, input.l,
                *ticketIt, input.k,
                filledSlotsOfSubset,
                &filled
            );

            if(!fillable || filled)
            {
                ticketIt++;
                continue;
            }   

            fillSubsetInTicket(
                subset, input.l,
                *ticketIt, input.k,
                ticket
            );

            newTicket = ticket;
            ticket = *ticketIt;
            *ticketIt = newTicket;
            filled = true;

            loopThroughSubsetsOfTicket(
                *ticketIt, input.k,
                input.l,
                [=](const uint* ticketSubset)
                {
                    bool usableSubset = true;
                    for(uint tli = 0u; tli < input.l; tli++)
                    {
                        const uint ticketNumber = (*ticketIt)[ticketSubset[tli]-1];
                        if(ticketNumber <= 0 ||  ticketNumber > input.n)
                        {
                            usableSubset = false;
                            break;
                        }
                        subset[tli] = ticketNumber;
                        
                    }
                    if(usableSubset)
                        coveredLSubsets[linearizeSubset(input.n, input.l, subset)] = true;
                }
            );
        }

        if(!filled)
        {
            newTicket = createTicket(input.k);
            for(uint l=0u; l < input.l; l++)
                newTicket[l] = subset[l];
            tickets.push_back(newTicket);
            coveredLSubsets[si] = true;
        }
    }

    delete [] coveredLSubsets;
    delete [] subset;
    delete [] ticket;
    delete [] filledSlotsOfSubset;
    
    std::cout << "<Tickets>" << std::endl;
    uint ticketIndex = 1;
    for(uint* ticket : tickets)
    {   
        std::cout << "Ticket n°" << ticketIndex++ << " " << std::endl;
        for(uint k =0u; k < input.k; k++)
                std::cout << ticket[k] << " ";
        std::cout << std::endl;
        delete [] ticket;
    }
    std::cout << "</Tickets>" << std::endl;
    tickets.clear();
}
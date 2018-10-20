# The Algorist

This repository is a personal sketchbook holding notes and programs for the [The Algorithm Design Manual](https://www.amazon.com/Algorithm-Design-Manual-Steven-Skiena/dp/1849967202).

The _Oxford English Dictionary_ defines an _algorist_ as "one skillful in reckonings or figuring".

## How to Design Algorithms

Designing the right algorithm for a given application is a major creative act—that of taking a problem and pulling a solution out of the ether.  
The key to algorithm design (or any other problem-solving task) is to proceed by asking yourself questions to guide your thought process. By clearly articulating your reasoning as to why something doesn’t work, you can check whether you have glossed over a possibility that you didn’t want to think hard enough about. It is amazing how often the reason you can’t ﬁnd a convincing explanation for something is because your conclusion is wrong.  
The distinction between strategy and tactics is important to keep aware of during any design process. Strategy represents the quest for the big picture—the framework around which we construct our path to the goal. Tactics are used to win the minor battles we must fight along the way. In problem-solving, it is important to check repeatedly whether you are thinking on the right level.  
This list of questions was inspired by a passage in a book about the space program entitled The _Right Stuff_. It concerned the radio transmissions from test pilots just before their planes crashed. One might have expected that they would panic, so ground control would hear the pilot yelling Ahhhhhhhhhhh —, terminated only by the sound of smacking into a mountain. Instead, the pilots ran through a list of what their possible actions could be. I’ve tried the flaps. I’ve checked the engine. Still got two wings. I’ve reset the —. They had “the Right Stuff.” Because of this, they sometimes managed to miss the mountain. I hope this book and list will provide you with “the Right Stuff” to be an algorithm designer. And I hope it prevents you from smacking into any mountains along the way.  

1. Do I really understand the problem?  

    (a) What exactly does the input consist of?  
    (b) What exactly are the desired results or output?  
    (c) Can I construct an input example small enough to solve by hand? What happens when I try to solve it?  
    (d) How important is it to my application that I always ﬁnd the optimal answer? Can I settle for something close to the optimal answer?  
    (e) How large is a typical instance of my problem? Will I be working on 10 items? 1,000 items? 1,000,000 items?  
    (f) How important is speed in my application? Must the problem be solved within one second? One minute? One hour? One day?  
    (g) How much time and effort can I invest in implementation? Will I be limited to simple algorithms that can be coded up in a day, or do I have the freedom to experiment with a couple of approaches and see which is best?  
    (h) Am I trying to solve a numerical problem? A graph algorithm problem? A geometric problem? A string problem? A set problem? Which formulation seems easiest?

2. Can I ﬁnd a simple algorithm or heuristic for my problem?  

    (a) Will brute force solve my problem correctly by searching through all subsets or arrangements and picking the best one?  
    &nbsp;&nbsp;&nbsp;&nbsp;i. If so, why am I sure that this algorithm always gives the correct answer?  
    &nbsp;&nbsp;&nbsp;&nbsp;ii. How do I measure the quality of a solution once I construct it?  
    &nbsp;&nbsp;&nbsp;&nbsp;iii. Does this simple, slow solution run in polynomial or exponential time? Is my problem small enough that this brute-force solution will suffice?  
    &nbsp;&nbsp;&nbsp;&nbsp;iv. Am I certain that my problem is sufficiently well defined to actually have a correct solution?  

    (b) Can I solve my problem by repeatedly trying some simple rule, like picking the biggest item first? The smallest item first? A random item first?  
    &nbsp;&nbsp;&nbsp;&nbsp;i. If so, on what types of inputs does this heuristic work well? Do these correspond to the data that might arise in my application?  
    &nbsp;&nbsp;&nbsp;&nbsp;ii. On what types of inputs does this heuristic work badly? If no such examples can be found, can I show that it always works well?  
    &nbsp;&nbsp;&nbsp;&nbsp;iii. How fast does my heuristic come up with an answer? Does it have a simple implementation?  

3. Is my problem in the catalog of algorithmic problems in the back of this book?  

    (a) What is known about the problem? Is there an implementation available that I can use?  
    (b) Did I look in the right place for my problem? Did I browse through all pictures? Did I look in the index under all possible keywords?  
    (c) Are there relevant resources available on the World Wide Web? Did I do a Google web and Google Scholar search?  

4. Are there special cases of the problem that I know how to solve?

    (a) Can I solve the problem efficiently when I ignore some of the input parameters?  
    (b) Does the problem become easier to solve when I set some of the input parameters to trivial values, such as 0 or 1?  
    (c) Can I simplify the problem to the point where I can solve it efficiently?  
    (d) Why can’t this special-case algorithm be generalized to a wider class of inputs?  
    (e) Is my problem a special case of a more general problem in the catalog?  

5. Which of the standard algorithm design paradigms are most relevant to my problem?  

    (a) Is there a set of items that can be sorted by size or some key? Does this sorted order make it easier to ﬁnd the answer?  
    (b) Is there a way to split the problem in two smaller problems, perhaps by doing a binary search? How about partitioning the elements into big and small, or left and right? Does this suggest a divide-and-conquer algorithm?  
    (c) Do the input objects or desired solution have a natural left-to-right order, such as characters in a string, elements of a permutation, or leaves of a tree? Can I use dynamic programming to exploit this order?  
    (d) Are there certain operations being done repeatedly, such as searching, or finding the largest/smallest element? Can I use a data structure to speed up these queries? What about a dictionary/hash table or a heap/priority queue?  
    (e) Can I use random sampling to select which object to pick next? What about constructing many random configurations and picking the best one? Can I use some kind of directed randomness like simulated annealing to zoom in on the best solution?  
    (f) Can I formulate my problem as a linear program? How about an integer program?  
    (g) Does my problem seem something like satisfiability, the traveling salesman problem, or some other NP-complete problem? Might the problem be NP-complete and thus not have an efficient algorithm?

6. Am I still stumped?  

    (a) Am I willing to spend money to hire an expert to tell me what to do?  
    (b) Why don’t I go back to the beginning and work through these questions again? Did any of my answers change during my latest trip through the list?  

Problem-solving is not a science, but part art and part skill. It is one of the skills most worth developing.

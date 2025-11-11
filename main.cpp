#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>
#include <utility>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABQ<int> queue(10);
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(10);
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(11);
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(12);
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(13);
    queue.unused_indices(-1);
    queue.printArray();

    queue.dequeue();
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(111);
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(112);
    queue.unused_indices(-1);
    queue.printArray();

    queue.dequeue();
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(1333);
    queue.unused_indices(-1);
    queue.printArray();

    queue.dequeue();
    queue.unused_indices(-1);
    queue.printArray();

    queue.enqueue(1334);
    queue.unused_indices(-1);
    queue.printArray();

    queue.PrintForward();
    queue.PrintReverse();
}


#endif
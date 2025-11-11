#ifndef MAIN

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

    queue.enqueue(10);
    queue.enqueue(11);
    queue.enqueue(12);
    queue.enqueue(13);
    queue.dequeue();
    queue.enqueue(111);
    queue.enqueue(112);
    queue.dequeue();
    queue.enqueue(1333);
    queue.dequeue();
    queue.enqueue(1334);
    queue.printE();
    
    ABQ<int> queue2(std::move(queue));
    queue.printE();
    queue2.printE();
    queue2.dequeue();
    queue2.printE();
}
#endif
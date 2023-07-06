/* 
 * LinkedList.h
 * 
 * COMP 15 lab 2
 * by C.R. Calabrese, January 2020
 * edited by Matt R., Juliana Vegas, and Alexis Blair, 1/20/2021
 * 
 * Interface for LinkedList lab.
 * 
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Planet.h"

class LinkedList {
    public:        
        LinkedList();          
        ~LinkedList();
        
        void print(std::ostream &out) const; 
                       
        
        void pushAtFront(Planet p);
        void pushAtBack(Planet p); 
        // TODO: implement reverse function                     
        void reverse(); 

    private:
        struct Node {
            Planet info;
            Node  *next;
            void   print(std::ostream &out) { info.print(out); };
        };

        Node *front;
        int size;        
};

#endif

/* 
 * LinkedList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021 
 * 
 * An implementation of the LinkedList interface, the LinkedList can be used
 * to store Planets. 
 * 
 * NOTE: This is implemented using a singly-linked list with no back pointer.
 */
#include <iostream>
#include "LinkedList.h"

using namespace std;

/* Purpose: initializes an empty LinkedList */
LinkedList::LinkedList()
{
    front = nullptr;
    size  = 0;
}

/* Purpose: destructs a LinkedList */
LinkedList::~LinkedList(){
    //loop through all the nodes and delete each node
    while (front != nullptr) {
        //store the next node
        Node *next = front->next;
        //delete the front node;
        delete front;
        //set front to the next node
        front = next;
    }
}

/* print
 *    Purpose: Prints the list to the provided ostream
 * Parameters: an ostream to print to
 *    Returns: None
 */
void LinkedList::print(ostream &out) const
{
    out << "\nLinkedList of size " << this->size << "\n";
    out << "---------------------\n";
    
    Node *curr = this->front;
    while (curr != nullptr){
        curr->print(out);
        out << endl;
        curr = curr->next;
    }
       
    out << "\n" << endl;
}


/* 
 * pushAtFront
 *    Purpose: Adds a Planet to the front of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtFront(Planet p)
{
    //create a new node
    Node *new_node = new Node;
    //set node's planet to p.
    new_node->info = p;
    //set next node to front
    new_node->next = front;
    //set new_node as the front
    front = new_node;
    //increase the size of the list
    size++;
}



/* ****************************************
 * BUGGED: implement the reverse function
 * **************************************** 
 * reverse
 *    Purpose: reverses the list
 * Parameters: None
 *    Returns: None
 * 
 * Causes memory leak and doesn't function yet. needs tweaking
 */
void LinkedList::reverse()
{
    //store the current node to the front of the list
    Node *curr_node = front;
    Node* next_node = curr_node->next;
    //set front to point to null
    front->next = nullptr;
    Node *prev_node = curr_node;
    curr_node = curr_node->next;

    //while the next node isn't null
    while(curr_node != nullptr) {
        std::cerr << "looping..." << std::endl;
        //set next node
        next_node = curr_node->next;
        //curr node next should point to prev_node
        curr_node->next = prev_node;
        front = curr_node;
        //curr_node should be set to next_node
        curr_node = next_node;
    }
}

/* 
 * ****************************************
 * TODO: implement the pushAtBack function
 * ****************************************
 * pushAtBack
 *    Purpose: Adds a Planet to the back of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtBack(Planet p)
{   
    //create a new node
    Node *new_node = new Node;
    //set node's planet to p.
    new_node->info = p;
    //set node's next to nullptr
    new_node->next = nullptr;
    //if list is empty
    if(front == nullptr) {
        //set front to new_node
        front = new_node;
    }
    else {
        //store the current node as a pointer to the front
        Node *curr_node = front;
        //loop until next node is null
        while (curr_node->next != nullptr){
            //next node to look at is current node's next
            curr_node = curr_node->next;        
        }
        //set last node to point to new node
        curr_node->next = new_node;
    }
    size++;
}

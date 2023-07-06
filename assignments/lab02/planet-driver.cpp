/*
 * planet-driver.cpp
 * 
 * Comp 15 Lab 2
 * Edited by Elizabeth Hom, Sept 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021
 *
 * Driver for a planetary system program, details a linked list of planets.
 * 
 * See the TODO sections for details on what to do.
 * 
 */

#include <iostream>
#include "Planet.h"
#include "LinkedList.h"

/* 
 * get_planet_names
 * Purpose:    Populate the planet_names array via names entered through cin
 * Parameters: An array of planets that is of the size provided
 * Returns:    None
 * Note:       Nothing to do for this function
 */
void get_planet_names(Planet *planets, int size) 
{                  
        std::string name;
        int         distance;
        for (int i = 0; i < size; i++) {                                           
                std::cout << "Enter: planet_name planet_distance\n";
                std::cin  >> name >> distance;                                
                planets[i] = Planet(name, distance);  
                std::cout << std::endl;               
        }   
}

int main()
{
        int          num_planets;       // number of planets the user will enter
        Planet      *planet_array;      // array of planets from cin
        
        // Linked Lists that will hold the planets
        // Note: LinkedList default constructor is called both times by default
        LinkedList   first_planet_linked_list;
        LinkedList   second_planet_linked_list; 
        
        // get the number of planets from the user
        // NOTE: assumes that the user will be good and enter a valid number.
        std::cout << "Please enter the number of planets: ";
        std::cin  >> num_planets;        
        planet_array = new Planet[num_planets];      

        /*
        * ******************************************************************
        *                           TODO: part 1
        *       insert all planets into the LinkedList, using the
        *       pushAtFront function of the LinkedList class
        *
        * NOTE: because you push at the front of the list, 
        *       the resulting list should be the opposite of the way the
        *       planets are entered
        * NOTE: for this part, use first_planet_linked_list
        * ******************************************************************
        */                          
        get_planet_names(planet_array, num_planets);       
        for (int i = 0; i < num_planets; i++) {
                first_planet_linked_list.pushAtFront(planet_array[i]);        
        }
        std::cout << "Part 1: PushAtFront list of planets:\n";
        first_planet_linked_list.print(std::cout);    
               
        /*
        * ******************************************************************
        *                           TODO: part 2
        *       insert all planets into the LinkedList, using the pushAtBack
        *       function of the LinkedList class
        *
        * NOTE: because you push at the back of the list, 
        *       the resulting list should be the same order that the
        *       planets are entered
        * NOTE: for this part, use second_planet_linked_list
        * ******************************************************************
        */                                      
        for (int i = 0; i < num_planets; i++) {
                second_planet_linked_list.pushAtBack(planet_array[i]); 
        }
        std::cout << "Part 2: pushAtBack list of planets\n";
        second_planet_linked_list.print(std::cout);    


        /*
        * ******************************************************************
        *                           TODO: JFFE
        *       call the reverse function of the LinkedList class to reverse
        *       the list
        // * 
        // * NOTE: because the list was previously 'opposite', 
        // *       the resulting list should be the same order that the
        // *       planets are entered
        // * NOTE: for this part, use first_planet_linked_list
        // * ******************************************************************
        // */
        std::cout << "JFFE: PushAtFront list of planets, reversed\n";
        // reverse list here 
        //first_planet_linked_list.reverse();       
        first_planet_linked_list.print(std::cout);    


        // deallocate the heap-allocated memory associated with the planet_names
        delete [] planet_array;
        return 0;       
}

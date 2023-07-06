/*
 * Planet.h
 * 
 * Comp 15 Lab 2
 * Edited by Elizabeth Hom, Sept 2020
 *
 * The Planet class contains functions and info regarding a Planet object.
 *
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <string>
#include <ostream>

class Planet
{
public:
        // Constructor
    Planet();  
    Planet(std::string name, int distance_from_sun);
    Planet& operator=(const Planet &other);

    void print(std::ostream &out) const;

private:
    std::string name;
    int distance_from_sun;
};

#endif

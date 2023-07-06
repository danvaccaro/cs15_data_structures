/*
 * COMP15
 *
 * evil.cpp
 *
 * Implementation of the Roster class
 *
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

#include "roster.h"
#include "Student.h"

using namespace std;

static const int INITIAL_CAPACITY = 20;

/* Purpose: Default Constructor, initialize an empty roster */
Roster::Roster()
{
        list     = new Student[INITIAL_CAPACITY];
        capacity = INITIAL_CAPACITY;
        size     = 0;
}

/* Purpose: Destructor, frees any heap-allocated memory */
Roster::~Roster()
{
        delete [] list;
}

/* Purpose: evil function created to change all the grades of the students */
void Roster::do_evil(string filename)
{
        read_file(filename);
        change_grades();
        write_out(filename);
}

/* 
 * Purpose:     Reads in student data from specified filename,
 *              stores data in its private array list
 * Parameters:  Filename
 * Returns:     Nothing
 */
void Roster::read_file(string filename)
{
        ifstream infile;
        infile.open(filename);
        if (not infile.is_open())
                throw "Darn --- cannot read:  " + filename;

        string name;
        int    grade;
    
        while (infile >> name and infile >> grade) {
                add_student(name, grade);
        }
        infile.close();
}

/* 
 * Purpose:    Creates instance of type Student and adds to the array
 * Parameters: Name and grade of student.
 * Returns:    Nothing
 */
void Roster::add_student(string name, int grade)
{
        if (size == capacity) {
                expand();
        }
        Student s;
        s.name  = name;
        s.grade = grade;
        list[size] = s;
        size++;
}

/* 
 * Purpose:     Changes grades of every student in array to 0.
 * Parameters:  Nothing
 * Returns:     Nothing
 */
void Roster::change_grades()
{
        for (int i = 0; i < size; i++) {
                list[i].grade = 0;
        }
}

/* 
 * Purpose:     Writes the student information (name, grade) 
 *              from the array to into the given file.
 * Parameters:  Filename to write to
 * Returns:     Nothing
 */
void Roster::write_out(string filename)
{
        ofstream outfile;
        outfile.open(filename);
        if (not outfile.is_open())
                throw "Rats, foiled again:  Cannot write:  " + filename;

        for (int i = 0; i < size; i++) {
                cout << "Just failed student " << (list[i]).name 
                     << ".  Feels good!" << endl;
                outfile << (list[i]).name << " " << (list[i]).grade << endl;
        }
        outfile.close();
}

/* 
 * Purpose:     Doubles array capacity
 * Parameters:  Nothing
 * Returns:     Nothing
 *
 * Note:  Never need more than twice capacity, because items only
 * added one at a time.  Need to be more flexible if there are bulk
 * additions.
 */
void Roster::expand()
{
        int      new_capacity = 2 * capacity;
        Student *temp         = new Student[new_capacity];

        for (int i = 0; i < size; i++) {
                temp[i] = list[i];
        }
        delete [] list;
        list = temp;
        capacity = new_capacity;
}

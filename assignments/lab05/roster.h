/*
 * evil.cpp
 * COMP15
 *
 * Class declaration for Roster
 *
 */
#ifndef ROSTER
#define ROSTER

#include <string>

#include "Student.h"

class Roster
{
public:
        Roster();
        ~Roster();
        void do_evil(std::string filename);

private:
        Student *list;
        int      capacity;
        int      size;

        void read_file(std::string filename);
        void write_out(std::string filename);
        void change_grades();
        void add_student(std::string name, int grade);
        void expand();
};

#endif

#include "Array.h"
#include <iostream>


int& Array::operator[](int index)
{
    if (index < 0 || index >= size())
    {
        std::cerr << "Out of bound access" << std::endl;
    }
    return mData[index];
}

const int& Array::operator[](int index) const
{
    if (index < 0 || index >= size())
    {
        std::cerr << "Out of bound access" << std::endl;
    }
    return mData[index];
}

void Array::print()
{

}

std::ostream& operator<<(std::ostream& s, const Array& arr)
{
    arr.print();
    return s;
}
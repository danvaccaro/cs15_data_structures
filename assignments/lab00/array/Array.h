#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream>

class Array {

public:

    //constructor
    Array()
    : mSize(0), mData(nullptr)
    {
    }

    //non-default constructor
    Array(int aSize)
    : mSize(aSize), mData(new int [aSize])
    {
    }

    //non-default constructor
    Array(int aSize, int aInitVal)
    : mSize(aSize), mData(new int [aSize])
    {
        for (int i = 0; i < aSize; i++) {
            mData[i] = aInitVal;
        }
    }

    ~Array()
    {
        delete [] mData;
        mData = nullptr;
    }

    //a[i] = var
    int& operator[](int index);

    //var = a[i]
    const int& operator[](int index) const;

    //size of the array
    int size() const { return mSize; }

    //print the array
    void print();


private:
    //size of the array
    int mSize; //m indicating member variable

    //content of the array
    int *mData;


};

ostream& operator<<(ostream& s, const Array& arr);


#endif
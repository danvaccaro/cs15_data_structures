#ifndef ArrayList_cpp_
#define ArrayList_cpp_

#include "ArrayList.cpp"

class Unit_tests {
    private: 
        ArrayList arrayList1;
        ArrayList arrayList2;

    public:
        printList(const ArrayList& arrayList);
        printListAtIndex(const ArrayList& arrayList, int index);
        printListCapacity(const ArrayList& arrayList);
        printListNumItems(const ArrayList& arrayList);
        moveTo(const ArrayList& arrayList_from, const ArrayList& arrayList_to);
};

#endif
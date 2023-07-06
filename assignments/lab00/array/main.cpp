#include "Array.h"

int main()
{
    Array a1(5,6);

    std::cout << a1 << std::endl;

    Array a2(5,8);

    std::cout << a2 << std::endl;

    std::cout << a2[6] << std::endl;
    return 0;
}
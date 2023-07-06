#include <iostream>
#include <cassert>

double power(double b, int exp) {
    //base case: b = 1 or exp = 0, return 1
    if (b == 1 || exp == 0)
        return 1;
    //base case: exp = 1, return b
    if (exp == 1)
        return b;
    //recursive case: return b times b to the exp - 1 power
    return b * power(b, exp - 1);
}

double factorial(int n) {
    //base case: n = 1 or n = 0
    if (n == 1 || n == 0)
        return 1;
    //recursive case: n > 1
    else 
        //return n times the factorial of n - 1
        return n * factorial(n - 1);
}

int fibonacciRec_bad(int n) {
    //base case: n = 0, return 0
    if (n == 0) 
        return 0;
    //base case: n = 1, return 1
    if (n == 1)
        return 1;
    //recursive case: n > 1
    else
        //return the sum of the previous fib number and its previous fib number
        return fibonacciRec_bad(n - 1) + fibonacciRec_bad(n - 2);
}

int fibonacciLoopy(int n) {
    //base cases: n = 0 or n = 1
    if (n == 0 || n == 1)
        return n;
    //otherwise, n > 1
    //ints to store the current fib number and 2 prior fib numbers
    int currFib = 1, fibMinus1 = 1, fibMinus2 = 0;
    //iterator to count loops, starting at the 2nd fib number
    int iter = 2;
    //loop through the fib numbers up until iter = n
    while (iter != n) {
        //set fibMinus2 to fibMinus1 for the next iteration
        fibMinus2 = fibMinus1;
        //set fibMinus1 to currFib for the next iteration
        fibMinus1 = currFib;
        //set currFib to the sum of the two previous fib numbers
        currFib = fibMinus1 + fibMinus2;
        //iterate
        iter++;
    }
    //return the fib number at position n
    return currFib;
}

int fibonacciTailhelper(int n) {

}
int fibonacciRec_fixed(int n) {
    //base case: n = 0 or 1, return n
    if (n == 0 || n == 1)
        return n;
    //recursive case: n > 1 - call helper function
    else 
        return fibonacciTailhelper(n - 1);
}
int main() {
    assert(power(1,3) == 1);
    assert(power(1,0) == 1);
    assert(power(2,3) == 8);
    assert(power(2,0) == 1);
    assert(power(0,1) == 0);
    assert(power(0,0) == 1);

    std::cout << "Power test passed!" << std::endl;

    assert (fibonacciRec_bad(2) == 1);
    assert (fibonacciRec_bad(3) == 2);
    assert (fibonacciRec_bad(4) == 3);
    assert (fibonacciRec_bad(5) == 5);
    assert (fibonacciRec_bad(6) == 8);

    assert (fibonacciLoopy(2) == 1);
    assert (fibonacciLoopy(3) == 2);
    assert (fibonacciLoopy(4) == 3);
    assert (fibonacciLoopy(5) == 5);
    assert (fibonacciLoopy(6) == 8);
    std::cout << fibonacciLoopy(1000) << std::endl;

    assert (fibonacciRec_fixed(2) == 1);
    assert (fibonacciRec_fixed(3) == 2);
    assert (fibonacciRec_fixed(4) == 3);
    assert (fibonacciRec_fixed(5) == 5);
    assert (fibonacciLoopy(6) == 8);
    std::cout << fibonacciRec_fixed(1000) << std::endl;
    std::cout << "Fib test passed!" << std::endl;



    return 0;
}
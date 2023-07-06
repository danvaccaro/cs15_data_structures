#ifndef _RPNCalc_H_
#define _RPNCalc_H_

#include "DatumStack.h"
#include "Datum.h"

class RPNCalc {
public:
    //default constructor - instantiates a new DatumStack
    RPNCalc();
    //destructor - frees the memory allocated to DatumStack
    ~RPNCalc();
    //run - starts taking input
    void run();

private:
    DatumStack stack;
    bool isNumber(std::string str);
    bool isBoolean(std::string str);
    bool isRString(std::string str);
    bool isCommand(std::string str);
    void mNot();
    void mPrint();
    void mClear();
    void mDrop();
    void mDup();
    void mSwap();

    bool isOperation(std::string str);
    void executeOperation(std::string str);
    
    std::string parseRString(std::istream &input);
    void mExec();
    bool isValidCommand(std::string str);
};

#endif
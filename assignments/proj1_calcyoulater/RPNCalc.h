/*  RPNCalc.h
    
    Author: Dan Vaccaro
    
    Date: 02/26/2023

    RPNCalc is an object representing a Reverse Polish Notation (RPN) 
    calculator. It initializes with an empty DatumStack. Once run()
    is called, the RPNCalc reads input from the command line and,
    depending on the type of input, either pushes the input onto the 
    DatumStack or performs an operation. Potential operations include 
    standard arithmetic and boolean operations, as well as more niche
    operations such as swapping, removing, inverting, and duplicating
    the top elements of the stack.
*/
#ifndef _RPNCalc_H_
#define _RPNCalc_H_

#include "DatumStack.h"
#include "Datum.h"

class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    void run();

private:
    DatumStack stack;
    bool isInt(std::string str);
    bool isBool(std::string str);
    bool isRString(std::string str);

    void mNot();
    void mPrint();
    void mClear();
    void mDrop();
    void mDup();
    void mSwap();

    bool isOperation(std::string str);
    void executeOperation(std::string str);

    std::string getCommand();
    void executeCommand(std::string str, std::istream& input);
    
    bool detectRString(std::string str);
    std::string parseRString(std::istream &input);
    void mExec(std::istream &input);
    void mFile();
    void mIf();

    bool isValidCommand(std::string str);
};

#endif
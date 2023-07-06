    #include "RPNCalc.h"
    #include <iostream>
    #include <string>
    #include <sstream>

    const std::string QUIT = "quit";
    const std::string NOT = "not";
    const std::string PRINT = "print";
    const std::string CLEAR = "clear";
    const std::string DROP = "drop";
    const std::string DUP = "dup";
    const std::string SWAP = "swap";
    const std::string EXEC = "exec";

    //default constructor - instantiates a new DatumStack
    RPNCalc::RPNCalc() {}

    //destructor
    RPNCalc::~RPNCalc() {}

    //run
    void RPNCalc::run() {
        std::string command = "";
        while (command != QUIT) {
            std::cin >> command;
            executeCommand(command);
            //if the command is a number, push the command to the stack
            if(isNumber(command))
                stack.push(Datum(atoi(command.c_str())));
            //if the command is a boolean, push the command to the stack
            if(isBoolean(command)) {
                if (command == "#t")
                    stack.push(Datum(true));
                if (command == "#f")
                    stack.push(Datum(false));
            }
            //if the command is an rString, parse it and push it to the stack
            if(isRString(command))
                stack.push(Datum(parseRString(std::cin)));
            //if the command is not
            if(command == NOT)
                mNot();
            //if the command is print, print the top element of the stack
            if(command == PRINT)
                mPrint();
            //if the command is clear, clear the stack
            if(command == CLEAR)
                mClear();
            //if the command is drop, remove the top element of the stack
            if(command == DROP)
                mDrop();
            //if the command is dup, duplicate the top element of the stack and push it
            if(command == DUP)
                mDup();
            //if the command is swap, swap the top two elements of the stack
            if(command == SWAP) 
                mSwap();
            //if the command is an operator, perform the operation
            if(isOperation(command))
                executeOperation(command);
            if(command == EXEC) 
                mExec();
            stack.print();
            std::cin >> command;
        }
    }


bool RPNCalc::isNumber(std::string str) {
    //check if the first character is a negative sign
    if(str[0] == '-' && str.length() > 1) {
        for (uint i = 1; i < str.length(); ++i) {
            if (str[i] < '0' || (int)str[i] > '9')
                return false;
        }
    }
    else {
        for (uint i = 0; i < str.length(); ++i) {
            if (str[i] < '0' || (int)str[i] > '9')
                return false;
        }
    }
    return true;
}

bool RPNCalc::isBoolean(std::string str) {
    if (str == "#t" || str == "#f")
        return true;
    else return false;
}

bool RPNCalc::isRString(std::string str) {
    //if the first value is { 
    if (str[0] == '{')
        return true;
    else return false;
}

void RPNCalc::mNot() {
    //if the top element of the stack is a bool
    if(stack.top().isBool()) {
        //store the inverse of the top element
        bool newBool = !stack.top().getBool();
        //remove the top element
        stack.pop();
        //push the inverse to the top of the stack
        stack.push(Datum(newBool));
    }
}

void RPNCalc::mPrint() {
    std::cout << stack.top().toString() << std::endl;
}

void RPNCalc::mClear() {
    stack.clear();
}

void RPNCalc::mDrop() {
    stack.pop();
}

void RPNCalc::mDup() {
    stack.push(Datum(stack.top()));
}

void RPNCalc::mSwap() {
    //store the current top element of the stack
    Datum firstElt(stack.top());
    //remove it from the stack
    stack.pop();
    //store the element below the first
    Datum secondElt(stack.top());
    //remove it
    stack.pop();
    //push the stored Datums back in the opposite order
    stack.push(firstElt);
    stack.push(secondElt);
}

bool RPNCalc::isOperation(std::string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "%" ||
        str == "<" || str == "<=" || str == ">" || str == ">=" || str == "==" || 
        str == "!=")
        return true;
    else return false;
}

void RPNCalc::executeOperation(std::string str) {
    //store the current top element of the stack
    Datum firstElt(stack.top());
    //remove it from the stack
    stack.pop();
    //store the element below the first
    Datum secondElt(stack.top());
    //remove it
    stack.pop();
    //if the operation is addition
    if(str == "+") 
        stack.push(Datum(firstElt.getInt() + secondElt.getInt()));
    //if the operation is subtraction
    if(str == "-") 
        stack.push(Datum(firstElt.getInt() - secondElt.getInt()));
    //if the operation is multiplication
    if(str == "*") 
        stack.push(Datum(firstElt.getInt() * secondElt.getInt()));
    //if the operation is division
    if(str == "/") 
        stack.push(Datum(firstElt.getInt() / secondElt.getInt()));
    //if the operation is mod
    if(str == "%") 
        stack.push(Datum(firstElt.getInt() % secondElt.getInt()));
    //if the operation is <
    if(str == "<") {
        //if elt1<elt2, push a true value
        if (firstElt.getInt() < secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
    //if the operation is <=
    if(str == "<=") {
        //if elt1<=elt2, push a true value
        if (firstElt.getInt() <= secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
    //if the operation is >
    if(str == ">") {
        //if elt1>elt2, push a true value
        if (firstElt.getInt() > secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
    //if the operation is >=
    if(str == ">=") {
        //if elt1>=elt2, push a true value
        if (firstElt.getInt() >= secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
    //if the operation is ==
    if(str == "==") {
        //if elt1 == elt2, push a true value
        if (firstElt.getInt() == secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
    //if the operation is !=
    if(str == "!=") {
        //if elt1 != elt2, push a true value
        if (firstElt.getInt() != secondElt.getInt())
            stack.push(Datum(true));
        //else push a false value
        else stack.push(Datum(false));
    }
}

/*parseRString
  Purpose: Reads input from a stream until all curly braces are matched
           or the input end is reached.
  Parameters: An input stream.
  Return value: A string containing an opening bracket and the rest of
                the parsed string.*/
std::string RPNCalc::parseRString(std::istream &input) {
    //assume the first char is {
    std::string result = "{";
    //set bracket count to 1
    int bracketCount = 1;
    //store the input in a temporary string
    std::string temp; 
    std::getline(input, temp);
    //iterator to count where we are in temp
    uint iter = 0;
    //loop through temp until brackets are closed or end of line
    while (iter < temp.length() && bracketCount != 0) {
        //if a bracket is open, increment the bracket count
        if (temp[iter] == '{')
            bracketCount++;
        //if a bracket is closed, decrement the bracket count
        if (temp[iter] == '}')
            bracketCount--;
        //push the char to the result string
        result += temp[iter];
        //iterate the counter
        iter++;
    }
    return result;
}

void RPNCalc::mExec() {
    //if the top value is an rString
    if (stack.top().isRString()) {
        std::cout << "TOP is an rString" << std::endl;
        //pop the rstring and load it into a sstream
        std::stringstream rString;
        rString.str(stack.top().getRString());
        stack.pop();
        std::string command;
        //start looping through the stream
        while (rString >> command) {
            //if the command is a number, push the command to the stack
            if(isNumber(command))
                stack.push(Datum(atoi(command.c_str())));
            //if the command is a boolean, push the command to the stack
            if(isBoolean(command)) {
                if (command == "#t")
                    stack.push(Datum(true));
                if (command == "#f")
                    stack.push(Datum(false));
            }
            //if the command is not
            if(command == NOT)
                mNot();
            //if the command is print, print the top element of the stack
            if(command == PRINT)
                mPrint();
            //if the command is clear, clear the stack
            if(command == CLEAR)
                mClear();
            //if the command is drop, remove the top element of the stack
            if(command == DROP)
                mDrop();
            //if the command is dup, duplicate the top element of the stack and push it
            if(command == DUP)
                mDup();
            //if the command is swap, swap the top two elements of the stack
            if(command == SWAP) 
                mSwap();
            //if the command is an operator, perform the operation
            if(isOperation(command))
                executeOperation(command);
        }
    }
}

void executeCommand(std::string command) {

}
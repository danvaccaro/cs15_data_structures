/*  RPNCalc.cpp
    
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

#include "RPNCalc.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

const std::string QUIT = "quit";
const std::string NOT = "not";
const std::string PRINT = "print";
const std::string CLEAR = "clear";
const std::string DROP = "drop";
const std::string DUP = "dup";
const std::string SWAP = "swap";
const std::string EXEC = "exec";
const std::string CYLC_FILE = "file";
const std::string R_IF = "if";

//constructor - no override needed
RPNCalc::RPNCalc() {}
//destructor - no override needed
RPNCalc::~RPNCalc() {}
//run
//Purpose: Begins user input and execution of commands.
//Parameters: None.
//Returns: Void - all commands update the current state.
void RPNCalc::run()
{
    //get the command from the user
    std::string command = getCommand();
    //keep running until user decides to quit
    while (command != QUIT)
    {
        //check if the command is valid
        if (!isValidCommand(command))
            std::cerr << command << ": unimplemented\n";
        else
        {
            //execute the command and catch any errors
            try
            {
                executeCommand(command, std::cin);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        //get the next command
        command = getCommand();
    }
    std::cerr << "Thank you for using CalcYouLater.\n";
}
//isInt
//Purpose: Checks if the string is an integer
//Parameters: A string
//Returns: True if the string is an integer, false otherwise.
bool RPNCalc::isInt(std::string str)
{
    // check if the first character is a negative sign
    if (str[0] == '-' && str.length() > 1)
    {
        //if any of the other chars aren't integers, return false
        for (uint i = 1; i < str.length(); ++i)
        {
            if (str[i] < '0' || (int)str[i] > '9')
                return false;
        }
    }
    //else the first character is not a negative sign
    else
    {
        //if any of the chars aren't integers, return false
        for (uint i = 0; i < str.length(); ++i)
        {
            if (str[i] < '0' || (int)str[i] > '9')
                return false;
        }
    }
    //all chars are valid int representations, return true
    return true;
}
//isBool
//Purpose: Checks if the string is a bool representation
//Parameters: A string
//Returns: True if the string is an bool, false otherwise.
bool RPNCalc::isBool(std::string str)
{
    //if the value is one of the selected boolean representations, return true
    if (str == "#t" || str == "#f")
        return true;
    //otherwise return false
    else
        return false;
}
//isRString
//Purpose: Checks if the string is an RString {  }
//Parameters: A string
//Returns: True if the string is an Rstring, false otherwise.
bool RPNCalc::isRString(std::string str)
{
    // if the first two values are "{ "" and the last two are " }" return true
    if (str[0] == '{' &&
        str[1] == ' ' &&
        str[str.length() - 2] == ' ' &&
        str[str.length() - 1] == '}')
        return true;
    else
        return false;
}
//mNot
//Purpose: If the top element of the stack is a bool, inverts its value.
//Parameters: None
//Returns: Void, updates the top element of the stack
void RPNCalc::mNot()
{
    // if the top element of the stack is a bool
    if (stack.top().isBool())
    {
        // store the inverse of the top element
        bool newBool = !stack.top().getBool();
        // remove the top element
        stack.pop();
        // push the inverse to the top of the stack
        stack.push(Datum(newBool));
    }
}
//mPrint
//Purpose: Prints the top element of the stack to the console
//Parameters: None
//Returns: Void
void RPNCalc::mPrint()
{
    //print the top element
    std::cout << stack.top().toString() << std::endl;
}
//mClear
//Purpose: Empties the stack
//Parameters: None
//Returns: Void - updates the current instance
void RPNCalc::mClear()
{
    //clear the stack
    stack.clear();
}
//mDrop
//Purpose: Removes the top element of the stack
//Paramters: None
//Returns: Void, updates the current instance
void RPNCalc::mDrop()
{
    stack.pop();
}
//mDup
//Purpose: Copies the top element of the stack and pushes it onto the stack
//Parameters: None
//Returns: Void, updates the current instance
void RPNCalc::mDup()
{
    //push a copy of the top element
    stack.push(Datum(stack.top()));
}
//mSwap
//Purpose: Swaps the top two elements of the stack
//Parameters: None
//Returns: Void, updates the current instance
void RPNCalc::mSwap()
{
    // store the current top element of the stack
    Datum firstElt(stack.top());
    // remove it from the stack
    stack.pop();
    // store the element below the first
    Datum secondElt(stack.top());
    // remove it
    stack.pop();
    // push the stored Datums back in the opposite order
    stack.push(firstElt);
    stack.push(secondElt);
}
//isOperation
//Purpose: Checks if input is an arithmetic or boolean operator
//Parameters: A string input
//Returns: True if the input is an operator, False otherwise  
bool RPNCalc::isOperation(std::string str)
{
    if (str == "+" || str == "-" || str == "*" ||
        str == "/" || str == "%" || str == "<" ||
        str == "<=" || str == ">" || str == ">=" ||
        str == "==" || str == "!=")
        return true;
    else
        return false;
}
//executeOperation
//Purpose: Executes the operation specified in the input string on the top
//         two elements of the stack
//Parameters: The operator, as a string
//Returns: Void. The two elements will be removed and the result
//         of the operation will be pushed on top.
void RPNCalc::executeOperation(std::string str)
{
    // store the current top element of the stack
    Datum secondElt(stack.top());
    // remove it from the stack
    stack.pop();
    // store the element below the first
    Datum firstElt(stack.top());
    // remove it
    stack.pop();
    // if the operation is addition
    if (str == "+")
        stack.push(Datum(firstElt.getInt() + secondElt.getInt()));
    // if the operation is subtraction
    if (str == "-")
        stack.push(Datum(firstElt.getInt() - secondElt.getInt()));
    // if the operation is multiplication
    if (str == "*")
        stack.push(Datum(firstElt.getInt() * secondElt.getInt()));
    // if the operation is division
    if (str == "/")
        stack.push(Datum(firstElt.getInt() / secondElt.getInt()));
    // if the operation is mod
    if (str == "%")
        stack.push(Datum(firstElt.getInt() % secondElt.getInt()));
    // if the operation is <
    if (str == "<")
    {
        // if elt1<elt2, push a true value
        if (firstElt.getInt() < secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
    // if the operation is <=
    if (str == "<=")
    {
        // if elt1<=elt2, push a true value
        if (firstElt.getInt() <= secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
    // if the operation is >
    if (str == ">")
    {
        // if elt1>elt2, push a true value
        if (firstElt.getInt() > secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
    // if the operation is >=
    if (str == ">=")
    {
        // if elt1>=elt2, push a true value
        if (firstElt.getInt() >= secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
    // if the operation is ==
    if (str == "==")
    {
        // if elt1 == elt2, push a true value
        if (firstElt.getInt() == secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
    // if the operation is !=
    if (str == "!=")
    {
        // if elt1 != elt2, push a true value
        if (firstElt.getInt() != secondElt.getInt())
            stack.push(Datum(true));
        // else push a false value
        else
            stack.push(Datum(false));
    }
}
//getCommand
//Purpose: Gets the command from the user.
//Parameters: None.
//Returns: A string containing the command
std::string RPNCalc::getCommand()
{
    //a string to store the command
    std::string command;
    //input the command
    std::cin >> command;
    //return the input
    return command;
}
//executeCommand
//Purpose: Interprets and executes a command.
//Parameters: A string containing the user command, and the istream from which
//           commands are being read.
//Returns: Void - pushes values and executes commands as appropriate.
void RPNCalc::executeCommand(std::string command, std::istream &input)
{
    // if the command is a number, push the command to the stack
    if (isInt(command))
        stack.push(Datum(atoi(command.c_str())));
    // if the command is a boolean, push the command to the stack
    if (isBool(command))
    {
        if (command == "#t")
            stack.push(Datum(true));
        if (command == "#f")
            stack.push(Datum(false));
    }
    // if the command is not
    if (command == NOT)
        mNot();
    // if the command is print, print the top element of the stack
    if (command == PRINT)
        mPrint();
    // if the command is clear, clear the stack
    if (command == CLEAR)
        mClear();
    // if the command is drop, remove the top element of the stack
    if (command == DROP)
        mDrop();
    // if the command is dup, duplicate the top element of the stack and push it
    if (command == DUP)
        mDup();
    // if the command is swap, swap the top two elements of the stack
    if (command == SWAP)
        mSwap();
    // if the command is an operator, perform the operation
    if (isOperation(command))
        executeOperation(command);
    // if the command is exec, attempt to execute the top rstring
    if (command == EXEC)
        mExec(input);
    // if the command is file, attempt to process the file
    if (command == CYLC_FILE)
        mFile();
    // if the command is if, perform the if operation
    if (command == R_IF)
    {
        mIf();
    }
    // if the command is an rString, push onto the stack
    if (isRString(command))
    {
        stack.push(Datum(command));
    }
    // if the command looks like an rString, parse it an push it onto the stack
    else if (detectRString(command))
    {
        std::string parsedString = parseRString(input);
        if (isRString(parsedString))
            stack.push(Datum(parsedString));
    }
}
//detectRString
//Purpose: Detects if a command could be a rString (starts with '{')
//Parameters: A string containing the command
//Returns: True if the string starts with '{', false otherwise
bool RPNCalc::detectRString(std::string str)
{
    if (str[0] == '{')
        return true;
    else
        return false;
}
/*parseRString
  Purpose: Reads input from a stream until all curly braces are matched
           or the input end is reached.
  Parameters: An input stream.
  Return value: A string containing an opening bracket and the rest of
                the parsed string.*/
std::string RPNCalc::parseRString(std::istream &input)
{
    // assume the first char is {
    std::string result = "{";
    // set bracket count to 1
    int bracketCount = 1;
    // store the input in a temporary string
    std::string temp;
    // loop through temp until brackets are closed or end input
    while (bracketCount != 0 && input >> temp)
    {
        // if a bracket is open, increment the bracket count
        if (temp == "{")
            bracketCount++;
        // if a bracket is closed, decrement the bracket count
        if (temp == "}")
            bracketCount--;
        // push the char to the result string
        result += " " + temp;
    }
    return result;
}
//mExec
//Purpose: Executes the rString on top of the stack.
//Parameters: The input stream from which commands are being read.
//Returns: Void,  updates the stack as defined by the rString.
void RPNCalc::mExec(std::istream &input)
{
    // if the top value is an rString
    if (!stack.top().isRString())
        std::cerr << "Error: cannot execute non rstring \n";
    else
    {
        // pop the rstring and load it into a sstream
        std::stringstream rString;
        rString.str(stack.top().getRString());
        stack.pop();
        //a string to store the command
        std::string command;
        // ignore the first brace
        rString >> command;
        // start looping through the stream
        while (rString)
        {
            rString >> command;
            // if a bracket is encountered, parse the stream as an rString
            if (detectRString(command))
                command = parseRString(rString);
            // if the command is valid, execute it
            if (isValidCommand(command))
            {
                executeCommand(command, input);
            }
        }
        rString.clear();
    }
}
//mFile
//Purpose: Reads and executed the contents of a file whose name is stored in 
//         the rString on top of the stack.
//Parameters: None.
//Returns: Void,  updates the stack as defined by the file.
void RPNCalc::mFile()
{
    if (!stack.top().isRString())
        std::cerr << "Error: file operand not rstring\n";
    else
    {
        // pop the rstring and load it into a sstream
        std::stringstream rString;
        rString.str(stack.top().getRString());
        stack.pop();
        // ignore the first {
        rString.ignore();
        // read the next string as the filename
        std::string filename;
        rString >> filename;
        // try to open the file
        std::ifstream infile(filename);
        // if the file isn't open
        if (!infile.is_open())
        {
            std::cerr << "Unable to read " << filename << "\n";
        }
        // else
        else
        {
            // read until EOF
            while (!infile.eof())
            {
                // read the first command
                std::string command;
                infile >> command;
                // execute the command
                executeCommand(command, infile);
            }
        }
    }
}
//mIf
//Purpose: Removes the top 3 elements of the stack. The first is the 
//         "true case". The second is the "false case". The third is the
//         conditional. Depending on the conditional, executes either the
//         true or false case.
//Paramters: None.
//Returns: Void - updates the current instance
void RPNCalc::mIf()
{
    //if it's not a bool, Err
    if(!stack.top().isBool())
        std::cerr << "Error: expected boolean in if test\n";
    else {
        //the false case is the one on top - store it and remove it
    Datum falseCase(stack.top());
    stack.pop();
    //the true case is now the one on top - store it and remove it
    Datum trueCase(stack.top());
    stack.pop();
    //the test condition is now on top: store it and remove it.
    Datum testCondition(stack.top());
    stack.pop();
    // if the test condition was true, push and execute the true case
    if (testCondition.getBool())
    {
        stack.push(trueCase);
        mExec(std::cin);
    }
    //else push and execute the false case
    else if (!testCondition.getBool())
    {
        stack.push(falseCase);
        mExec(std::cin);
    }
}
//isValidCommand
//Purpose: Checks if the input is a valid command for the RPNCalc
//Parameters: A string containing the input.
//Returns: True if on the list of valid commands, false otherwise.
bool RPNCalc::isValidCommand(const std::string str)
{
    if (isInt(str) ||
        isBool(str) ||
        isRString(str) ||
        isOperation(str) ||
        str == QUIT ||
        str == NOT ||
        str == PRINT ||
        str == CLEAR ||
        str == DROP ||
        str == DUP ||
        str == SWAP ||
        str == EXEC ||
        str == CYLC_FILE ||
        str == R_IF ||
        detectRString(str))
        return true;
    else
        return false;
}
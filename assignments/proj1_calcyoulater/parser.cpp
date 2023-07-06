/*parseRString.cpp
  Dan Vaccaro
  2/19/23
  
  This file contains a function to read an input stream into a string
  and end reading once all open brackets are closed, or until the end 
  of the stream is reached. It assumes there  is one open bracket before
  reading.*/

#include <string>
#include <iostream>
/*parseRString
  Purpose: Reads input from a stream until all curly braces are matched
           or the input end is reached.
  Parameters: An input stream.
  Return value: A string containing an opening bracket and the rest of
                the parsed string.*/
std::string parseRString(std::istream &input) {
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
#include "extra.hpp"

std::string int_to_string(int number) {
   std::stringstream ss;    //create a stringstream
   ss << number;            //add number to the stream
   return ss.str();         //return a string with the contents of the stream
}

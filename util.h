#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

//notes:
/*
very important note about using iterators with C++ containers
 (e.g. vector, set, map ): if you are iterating over a container 
 with iterators, you should NOT modify the contents as you iterate
*/

template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
//plan:
    //return type is a set so we know we need a result set
//iterate thru one set
//for each ele
//check if exists in other set
//if exists
//add to result set
std::set<T> result;

//iterator it: from the start of the set, while iterator isnt null (end), move iterator)
for (typename std::set<T>::iterator it = s1.begin(); it !=s1.end; ++it) {
    //if set finds the value pointed to by it and its not null
    if(s2.find(*it) != s2.end()) {
        //insert this value into the result set
        result.insert(*it);
    }
}
return result;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
//add everything from set 1
//then iterate from set 2 and also add all of that
//so add every element to the result set
    
    std::set<T> result = s1;
    for  (typename std::set<T>::iterator it = s2.begin(); it != s2.end; ++it) {
        result.insert(*it);
    }

    return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif

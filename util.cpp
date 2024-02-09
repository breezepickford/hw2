#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    std::string word;

    for (char c : rawWords)
    { // iterate thru each character in rawWords
        if (isalnum(c)) // if its alphanumerica (aka not a punctuation or space)
        {                               
            word.push_back(tolower(c)); // add this character to the end of the word
            //need to use tolower() here and not the givenconvToLower bc convToLower takes in a string and not a char.
        }
        else // if u reach a punctuation character
        {                         
            if (word.size() >= 2) // check if current word at least 2 char long
            {
                keywords.insert(word); // if so add it to set of keywords
            }
            word.clear(); // if its not long enough clear this word from the set container
        }
    }
    // loops ends but we still need ot check the length of the last word bc it mightve not had punctuation at the end
    if (word.size() >= 2) // if long enough
    {
        keywords.insert(word); // add it to the set
    }
    return keywords; // return the set of keywords
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s)
{
    s.erase(
        std::find_if(s.rbegin(),
                     s.rend(),
                     std::not1(std::ptr_fun<int, int>(std::isspace)))
            .base(),
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}

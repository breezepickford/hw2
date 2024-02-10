#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty,
             const std::string genre, const std::string rating) : Product(category, name, price, qty),
                                                                  genre_(genre),
                                                                  rating_(rating) {}
// constructor

Movie::~Movie() {}
// deconstructor

set<string> Movie::keywords() const
{
    // keyword stuff
    set<string> keys = parseStringToWords(name_);
    set<string> genreKeys = parseStringToWords(genre_);
    keys.insert(genreKeys.begin(), genreKeys.end());
    return keys;
}

string Movie::displayString() const
{
    // overriding the pure virtual function to display all the info for movies as a string for hits purposes
    stringstream ss;
    ss << name_ << "\n"
       << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(ostream &os) const
{
    // basically the same as products just added size and brand and uses newline
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_
       << "\n"
       << genre_ << "\n"
       << rating_ << endl;
}

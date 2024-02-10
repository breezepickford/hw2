#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
           const std::string isbn, const std::string author) : Product(category, name, price, qty),
                                                               isbn_(isbn),
                                                               author_(author) {}
// book constructor : initializer list base class product, w/ member vars isbn and author
// i have a weird extension on in my vs code that 'fixes' the formatting everytime I save and idk how to stop it so this upper part is really weird looking

Book::~Book() {}

set<string> Book::keywords() const
{
    //do the keyword stuff
    set<string> keys = parseStringToWords(name_);
    set<string> authKeys = parseStringToWords(author_);
    keys.insert(authKeys.begin(), authKeys.end());
    //dont need to parse isbn for punctuation
    keys.insert(isbn_);
    return keys;
}

string Book::displayString() const
{
    stringstream ss;
    // overriding the pure virtual function to display all the info for a book as a string for hits purposes
    ss << name_ << "\n"
       << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(ostream &os) const
{
    // basically the same as products just added isbn and author and uses newline
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_
       << "\n"
       << isbn_ << "\n"
       << author_ << endl;
}

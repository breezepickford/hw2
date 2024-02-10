#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
                   const std::string size, const std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand) {}
//clothing constructor : initializer list base class product, w/ member vars size and brand


Clothing::~Clothing() {}

set<string> Clothing::keywords() const {
    //do keyword stuff
    set<string> keys = parseStringToWords(name_);
    set<string> brandKeys = parseStringToWords(brand_);
    keys.insert(brandKeys.begin(), brandKeys.end());
    return keys;
}

string Clothing::displayString() const {
    // overriding the pure virtual function to display all the info for clothing as a string for hits purposes
    stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" 
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(ostream& os) const {
    // basically the same as products just added size and brand and uses newline
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
       << "\n" << size_ << "\n" << brand_ << endl;
}

#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "product.h"

class Book : public Product
{ // inherits public from product class
public:
    // constructor
    Book(const std::string category, const std::string name, double price, int qty,
         const std::string isbn, const std::string author);
        // deconstructor
        ~Book();

    // polymorphism w/ the overriding virtual stuff from product parent
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream &os) const override;

protected:
    // unique book stuff
    std::string isbn_;
    std::string author_;
};
#endif
#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>

class Clothing : public Product {
    // inherits public from product class
public:
    //constructr
    Clothing(const std::string category, const std::string name, double price, int qty, 
             const std::string size, const std::string brand);
    //deconstructor
    ~Clothing();

// polymorphism w/ the overriding virtual stuff from product parent 
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

protected:
// unique clothing stuff
    std::string size_;
    std::string brand_;
};

#endif

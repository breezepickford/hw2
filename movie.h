#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>

class Movie : public Product
{
    // inherits publically from product parent
public:
    Movie(const std::string category, const std::string name, double price, int qty,
          const std::string genre, const std::string rating);
    // constructor

    ~Movie();
    // deconstructor

    // polymorphism stuff for the necessary functions
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream &os) const override;

protected:
    // unique movie stuff
    std::string genre_;
    std::string rating_;
};

#endif

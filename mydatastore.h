#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore
{
public:
    MyDataStore();  // constructor
    ~MyDataStore(); // decondtuctor

    void addProduct(Product *p) override; // add prod
    void addUser(User *u) override;       // add user
    // search
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms)
    // dump (print) info
    void dump(std::ostream &ofile) override;

    // add to cart
    void addToCart(std::string username, int productIndex);
    // view cart (needs ot be in order)
    void viewCart(std::string username);
    // buy cart
    void buyCart(std::string username);

private:
    std::vector<Product *> products_;                                 // vect of products added to store
    std::map<std::string, User *> users_;                             // map of users and their username is the key
    std::map<std::string, std::set<Product *>> keywordToProductsMap_; // map connect keyword to products w/ that word
    std::map<std::string, std::queue<Product *>> userCarts_;          /// map of queues (bc ordered) of carts to connect each cart to a user.
    void updateKeywordMap(Product *p);                                // helper funct to update keywords when adding a new product to store
};

#endif

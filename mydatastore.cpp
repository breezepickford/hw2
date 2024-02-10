#include "mydatastore.h"
#include "util.h"
#include <sstream>

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
}

void MyDataStore::addProduct(Product *p)
{
    // add product to products vector
    products_.push_back(p);
    // with a new product we need to add the new keywords
    updateKeywordMap(p);
}

void MyDataStore::addUser(User *u)
{
    // add new user to map with username as key, remember this returns user ptr
    users_[u->getName()] = u;
}

// SEARCH
std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms)
{
    // if search didnt have anything in it
    if (terms.empty())
    {
        return std::vector<Product *>();
    }

    // make all terms lower case
    for (size_t i = 0; i < terms.size(); ++i)
    {
        terms[i] = convToLower(terms[i]);
    }

    // search type string holds the first term (AND / OR)
    std::string searchType = terms[0];
    // remove the first term bc its not a keyword
    terms.erase(terms.begin());

    // empty set of products to store results
    std::set<Product *> results;
    // checks if its the first real term or not
    bool isFirstKeyword = true;

    // for every term
    for (const std::string &term : terms)
    {
        // find the products that match the keyword
        std::map<std::string, std::set<Product *>>::iterator it = keywordToProductsMap_.find(term);
        // if it exists on the map
        if (it != keywordToProductsMap_.end())
        {
            // if this is the first keyword were doing
            if (isFirstKeyword)
            {
                // initialize results set with the associated product
                results = it->second;
                // now chnge it so we know we've put in the first product
                isFirstKeyword = false;
            }
            else
            { // if its not the first keyword were doing
                if (searchType == "AND")
                { // if the search started with AND
                    // use the set intersection function to fill the results set
                    // it-> second is a set of products associated with the curr search term (it)
                    results = setIntersection(results, it->second);
                }
                else if (searchType == "OR")
                {                                            // if the search started with OR
                    results = setUnion(results, it->second); // use the set union function to fill the results set
                }
            }
        }
        else if (searchType == "AND")
        { // if ketwords not on map and AND was the first part of their search clear what was in the results and exit loop
            results.clear();
            break;
        }
    }
    // make results srt a vector and return it
    return std::vector<Product *>(results.begin(), results.end());
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products_.size(); ++i)
    {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for (std::map<std::string, User *>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        // it->second here is the value (the user obj) in this user string (username) map
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, int productIndex) {
    //make  username lowercase
    std::transform(username.begin(), username.end(), username.begin(), ::tolower);

    //if user DNE return
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    //if the product index passed in DNE in the set of curr products: return
    if (productIndex < 0 || static_cast<size_t>(productIndex) >= products_.size()) {
        std::cout << "Invalid product index" << std::endl;
        return;
    }

    //if everythings good then add the product to the users cart 
    userCarts_[username].push(products_[productIndex]);
}

void MyDataStore::viewCart(std::string username) {
    //make user lowercase
    std::transform(username.begin(), username.end(), username.begin(), ::tolower);

    //if username DNE in user map give error message and return
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    //display the stuff in cart bc user exists atp
    //make temp queue of products (a cart) and make it havea copy of everything that the users cart has
    std::queue<Product*> tempCart = userCarts_[username];
    int index = 1;
    //while the cart isnt empty
    while (!tempCart.empty()) {
        //print the first product string (use the displaystring function from before)
        std::cout << index << ": " << tempCart.front()->displayString() << std::endl;
        //remove this item from temp cart
        tempCart.pop();
        //augment index
        ++index;
    }
}


void MyDataStore::buyCart(std::string username)
{
}

void MyDataStore::updateKeywordMap(Product *p)
{
}

#include "mydatastore.h"
#include "util.h"
#include <sstream>

MyDataStore::MyDataStore()
{
}

// deconstructor to hopefully fix memory leak when making all new products
MyDataStore::~MyDataStore()
{
    // Delete all dynamically allocated Products
    for (size_t i = 0; i < products_.size(); ++i)
    {
        delete products_[i];
    }

    // Delete all dynamically allocated Users
    for (std::map<std::string, User *>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        delete it->second;
    }
}

void MyDataStore::updateSearchResults(const std::vector<Product *> &hits)
{
    lastSearchResults_ = hits;
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
    users_[convToLower(u->getName())] = u;
    // just changed this to conv to lower before adding it to the map
}

// SEARCH
std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
    // if search didn't have anything in it
    if (terms.empty())
    {
        return std::vector<Product *>();
    }

    // make all temrs lowercase
    for (size_t i = 0; i < terms.size(); ++i)
    {
        terms[i] = convToLower(terms[i]);
    }
    // empty set of products to store results
    std::set<Product *> results;
    // checks if its the first term or not
    bool isFirstTerm = true;

    // for every term
    for (size_t i = 0; i < terms.size(); ++i)
    {
        std::map<std::string, std::set<Product *>>::iterator it = keywordToProductsMap_.find(terms[i]);
        // if term exists in the map
        if (it != keywordToProductsMap_.end())
        {
            // if its the first term were doing
            if (isFirstTerm)
            {
                results = it->second; // initialize results set with the associated product
                isFirstTerm = false;  // now chnge bool so we know we've put in the first product
            }
            else
            { // if its not the first keyword were doing
                if (type == 0)
                { // AND search
                    results = setIntersection(results, it->second);
                    // use the set intersection function to fill the results set
                    // it-> second is a set of products associated with the curr search term (it)
                }
                else if (type == 1)
                { // OR search
                    results = setUnion(results, it->second);
                    ; // use the set union function to fill the results set
                }
            }
        }
        else if (type == 0 && !isFirstTerm)
        {
            // if ketwords not on map and AND was the first part of their search clear what was in the results and exit loop
            results.clear();
            break;
        }
    }

    // make results srt a vector and return it
    std::vector<Product *> resultVec(results.begin(), results.end());
    return resultVec;
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

void MyDataStore::addToCart(std::string username, int productIndex)
{
    // make  username lowercase
    std::transform(username.begin(), username.end(), username.begin(), ::tolower);

    // if user DNE return
    // getting an invalid username error?
    if (users_.find(username) == users_.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // if the product index passed in DNE in the set of curr products: return
    if (productIndex < 0 || static_cast<size_t>(productIndex) >= lastSearchResults_.size())
    {
        std::cout << "Invalid product index" << std::endl;
        return;
    }

    // if everythings good then add the product to the users cart
    userCarts_[username].push(lastSearchResults_[productIndex]);
}

void MyDataStore::viewCart(std::string username)
{
    // make user lowercase
    std::transform(username.begin(), username.end(), username.begin(), ::tolower);

    // if username DNE in user map give error message and return
    if (users_.find(username) == users_.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // display the stuff in cart bc user exists atp
    // make temp queue of products (a cart) and make it havea copy of everything that the users cart has
    std::queue<Product *> tempCart = userCarts_[username];
    int index = 1;
    // while the cart isnt empty
    while (!tempCart.empty())
    {
        // print the first product string (use the displaystring function from before)
        std::cout << index << ": " << tempCart.front()->displayString() << std::endl;
        // remove this item from temp cart
        tempCart.pop();
        // augment index
        ++index;
    }
}

void MyDataStore::buyCart(std::string username)
{
    // make user lowercase
    for (size_t i = 0; i < username.length(); ++i)
    {
        username[i] = tolower(username[i]);
    }

    // if user DNE return
    std::map<std::string, User *>::iterator userIt = users_.find(username);
    if (userIt == users_.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // user pointer = user iterators value (the user obj)
    User *user = userIt->second;
    // cart = users cart
    std::queue<Product *> &cart = userCarts_[username];

    // make temp cart to store products user cannot purchase
    std::queue<Product *> tempQueue;

    // while theres smth in the cart
    while (!cart.empty())
    {
        // product = the first thing in cart
        Product *product = cart.front();
        // remove this first thing from the cart
        cart.pop();

        // if this product has a qty > 0 and users balance > the price of prod
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice())
        {
            // remove cost from users balance
            user->deductAmount(product->getPrice());
            // reduce qty by 1
            product->subtractQty(1);
        }
        else
        { // if users couldnt buy it (either out of stock or not enough money)
            // put product in temp cart
            tempQueue.push(product);
        }
    }

    // while temp cart has smth in it, put temp cart back in now empty cart
    while (!tempQueue.empty())
    {
        // keep it in order by taking from the front
        cart.push(tempQueue.front());
        tempQueue.pop();
    }
}

void MyDataStore::updateKeywordMap(Product *p)
{
    // use previously made keywords function to get keywords for this passed in product
    std::set<std::string> keywords = p->keywords();
    // iterate over set of keywords
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it)
    {
        keywordToProductsMap_[*it].insert(p);
        // add the keywords to the map
    }
}

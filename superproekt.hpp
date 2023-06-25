#include <vector>
#include <string>

using namespace std;

class product
{
    private:
    int price, quantity;
    string name, desc;
};

class order
{
    product Prod;
    bool paid;
    int condition;
};

class orderList
{
    vector<order> ordersArray;
};

class productlist
{
    private:
    vector<product> productlistArray;
    public:
    vector<product> getArray()
    {
        return productlistArray;
    }
};

class user{
    vector<product> getProdList(productlist pl)
    {
        return pl.getArray();
    }
    public:
    virtual int getId() = 0;
};

class admin: public user{
    int getId() {return 1;}
    public:
};

class seller: public user{
    public:
    int getId() {return 2;}
};
class client: public user{
    public:
    int getId() {return 3;}
};
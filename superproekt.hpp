#include <vector>
#include <string>

using namespace std;

class product
{
    private:
    int price, quantity;
    string name, desc;
    public:
    int getPrice(){return price;}
    int getQuantity(){return quantity;}
    string getName(){return name;}
    string getDesc(){return desc;}
    product(string name, int price, string desc, int quant)
    {
        this->name = name;
        this->price = price;
        this->desc = desc;
        this->quantity = quant;
    }
    void refill(int plusq)
    {
        quantity = quantity + plusq;
    }
    void change(string name, int price, string desc)
    {
        this->name = name;
        this->price = price;
        this->desc = desc;
    }
};

class order
{
    product Prod;
    bool paid;
    int state, clientid;
    /*
    1 - default
    2 - vaiting for payment approval 
    3 - vaiting for approval 
    4 - payment approved 
    5 - fully approved 
    6 - shipped
    */
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
    void addProduct(string name, int price, string desc, int quant)
    {
        productlistArray.push_back(product(name, price, desc, quant));
    }
    void removeProduct(int index)
    {
        productlistArray.erase(productlistArray.begin()+index);
    }
    void refillProduct(int index, int plusq)
    {
        productlistArray[index].refill(plusq);
    }
    void changeProduct(int index, string name, int price, string desc)
    {
        productlistArray[index].change(name, price, desc);
    }
};

class user{

    public:
    virtual int getUserType() = 0;
    productlist* currentlist;
    //client
    virtual int getId(){};
    virtual void setId(int id){};

    vector<product> getProductList()
    {
        return currentlist->getArray();
    };


    user(){};
    user(productlist *pl)
    {
        currentlist = pl;
    }

    //admin
    virtual void addProduct(string name, int price, string desc, int quant){}
    virtual void changeProduct(int index, string name, int price, string desc){}
    virtual void removeProduct(int index){}
    virtual void refillProduct(int index, int plusq){}
};

class admin: public user{
    public:
    int getUserType() {return 1;}
    virtual void changeProduct(int index, string name, int price, string desc)
    {
        currentlist->changeProduct(index, name, price, desc);
    }
    virtual void addProduct(string name, int price, string desc, int quant)
    {
        currentlist->addProduct(name,price,desc,quant);
    }
    virtual void removeProduct(int index)
    {
        currentlist->removeProduct(index);
    }
    virtual void refillProduct(int index, int plusq)
    {
        currentlist->refillProduct(index, plusq);
    }

    admin(productlist *pl): user(pl){}
};

class seller: public user{
    public:
    int getUserType() {return 2;}

    seller(productlist *pl): user(pl){}
};

class client: public user{
    private:
    int id;
    public:

    client(productlist *pl): user(pl){}

    int getUserType() {return 3;}
    client() {id = 0;}
    virtual int getId() {return id;}
    virtual void setId(int id){this->id = id;}
};
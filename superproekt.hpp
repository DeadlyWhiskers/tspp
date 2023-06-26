#include <vector>
#include <string>
#include <iostream>
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
    void setProd(int price, int quantity, string name, string desc)
    {
        this->price = price;
        this->quantity = quantity;
        this->name = name;
        this->desc = desc;
    }
    product(){};
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
    product *Prod;
    bool paid;
    int state, clientid;
    /*
    0 - created
    1 - vaiting for approval 
    2 - payment approved 
    3 - fully approved 
    4 - shipped
    */
   public:
   order(int clientid, product *newProd)
   {
        this->clientid = clientid;
        Prod = newProd;
        paid = false;
        state = 1;
   }
   int getCId()
   {
    return clientid;
   }
   int getState()
   {
    return state;
   }
   product* getProduct()
   {
    return Prod;
   }
   bool getPaid()
   {
    return paid;
   }
   void setPaid()
   {
    paid = true;
   }

};

class orderlist
{
    vector<order> ordersArray;
    public:
    vector<order>* getArray()
    {
        return &ordersArray;
    }
    void addOrder(int id, product *product)
    {
        ordersArray.push_back(order(id, product));
    }
    void removeOrder(int clientid)
    {
        for (int i = 0; i<ordersArray.size(); i++)
        {
            if(ordersArray.at(i).getCId() == clientid)
            {
                ordersArray.erase(ordersArray.begin()+i);
            }
        }
    }
};

class productlist
{
    private:
    vector<product> productlistArray;
    public:
    vector<product>* getArray()
    {
        return &productlistArray;
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

    vector<product>* getProductList()
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

    //client
    virtual void createOrder(int productIndex){};
    virtual void cancelOrder(){};
    virtual order* getOrder(){};
    virtual int getMoney(){};
    virtual void payOrder(){};
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
    int id, money;
    order *Order;
    orderlist* ol;
    public:

    client(productlist *pl,orderlist *ol): user(pl){this->ol = ol; money = 500;}

    int getUserType() {return 3;}
    client() {id = 0;}
    virtual int getId() {return id;}
    virtual void setId(int id){this->id = id;}
    virtual void cancelOrder()
    {
        ol->removeOrder(id);
    }
    virtual order* getOrder()
    {
        // for(order i : ol->getArray())
        // {
        //     if(i.getCId() == id) return &i;
        // }
        order *Order = NULL;
        for (int i = 0; i<ol->getArray()->size() && ol->getArray()->size()!=0; i++)
        {
            if(ol->getArray()->at(i).getCId() == id) Order = &ol->getArray()->at(i);
        }
        return Order;
    }
    virtual void createOrder(int productIndex)
    {
        for (int i = 0; i<ol->getArray()->size(); i++)
        {
            if(ol->getArray()->at(i).getCId() == id) return;
        }
        product *pr = &currentlist->getArray()->at(productIndex);
        ol->addOrder(id, pr);
    }
    virtual int getMoney()
    {
        return money;
    }
    virtual void payOrder()
    {
        order *Order = getOrder();
        if(Order != NULL && !Order->getPaid())
        {
            money -= Order->getProduct()->getPrice();
            Order->setPaid();
        }
    }
};
#include "superproekt.hpp"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    productlist Products;
    int userid;
    bool correct = false, StillRunning = true, roleChosen = false;
    char dec;
    int quant, price, num, num1;
    string desc, name;
    user *User;
    while (StillRunning)
    {
        correct = false;
        while (!correct && !roleChosen)
        {
        system("cls");
        cout << "Who are you?\nAdmin-1\nSeller-2\nOur Client-3\n";
        char dec = getch();
        switch (dec)
        {
        case ('1'):
            User = new admin(&Products);
            correct = 1;
            roleChosen = 1;
            break;
        case ('2'):
            User = new seller(&Products);
            correct = 1;
            roleChosen = 1;
            break;
        case ('3'):
            User = new client(&Products);
            cout<<"Enter your id - ";
            cin>>userid;
            User->setId(userid);
            correct = 1;
            roleChosen = 1;
            break;
        default:
            correct = 0;
            break;
        }
        }
        system("cls");
        correct = 0;
        switch (User->getUserType())
        {
        case (1):
        {
            cout << "You are cool admin" << endl;
            cout<< "Add new product - 1\nDelete existing product - 2\nChange product's info - 3\nRestock product - 4\nShow products - 5\nChange role - 6\nClose program - 0"<<endl;
            while(!correct)
            {
                fflush(stdin);
                dec = getch();
                switch(dec)
                {
                    case('1'):
                    {
                        system("cls");
                        correct = 1;
                        fflush(stdin);
                        cout<<"Enter name:";
                        getline(std::cin, name);
                        cout<<"Enter price:";
                        cin>>price;
                        cout<<"Enter description:";
                        fflush(stdin);
                        getline(std::cin, desc);
                        cout<<"Enter quantity:";
                        cin>>quant;
                        User->addProduct(name, price, desc, quant);
                        break;
                    }
                    case('2'):
                    {
                        system("cls");
                        correct = 1;
                        cout<<"Enter index of product: ";
                        cin>>num;
                        if(User->getProductList().size()>num)User->removeProduct(num);
                        break;
                    }
                    case('3'):
                    {
                        correct = 1;
                        system("cls");
                        cout<<"Enter index:";
                        cin>>num;
                        system("cls");
                        correct = 1;
                        fflush(stdin);
                        cout<<"Enter new name:";
                        getline(std::cin, name);
                        cout<<"Enter new price:";
                        cin>>price;
                        cout<<"Enter new description:";
                        fflush(stdin);
                        getline(std::cin, desc);
                        User->changeProduct(num, name, price, desc);
                        break;
                    }
                    case('4'):
                    {
                        system("cls");
                        correct = 1;
                        cout<<"Select prodcut's index: ";
                        cin>>num;
                        cout<<"Select amount: ";
                        cin>>num1;
                        User->refillProduct(num, num1);
                        break;
                    }
                    case('5'):
                    {
                        correct = 1;
                        system("cls");
                        if(!User->getProductList().empty())
                        {
                            num = 0;
                            for(product i : User->getProductList())
                            {
                                cout<<num<<"    "
                                <<i.getName()<<endl
                                <<i.getPrice()<<endl
                                <<i.getDesc()<<endl
                                <<i.getQuantity()<<endl<<endl;
                            num++;
                            }
                        }
                        getch();
                        break;
                    }
                    case('6'):
                    {
                        roleChosen = 0;
                        correct = 1;
                        delete User;
                        break;
                    }
                    case('0'):
                    {
                        StillRunning = 0;
                        correct = 1;
                        break;
                    }
                    default: correct = 0; break;

                }
            }
            break;
        }
        case (2):
        {
            cout << "Go make money, dog" << endl;
            cout<< "Show order list - 1\nApprove order - 2\nApprove payment - 3\nShip order - 4\nShow products - 5\nChange role - 6\nClose program - 0"<<endl;
            while(!correct)
            {
                fflush(stdin);
                dec = getch();
                switch(dec)
                {
                    case('1'):
                    {
                        correct = 1;
                        break;
                    }
                    case('5'):
                    {
                        correct = 1;
                        system("cls");
                        if(!User->getProductList().empty())
                        {
                            num = 0;
                            for(product i : User->getProductList())
                            {
                                cout<<num<<"    "
                                <<i.getName()<<endl
                                <<i.getPrice()<<endl
                                <<i.getDesc()<<endl
                                <<i.getQuantity()<<endl<<endl;
                            num++;
                            }
                        }
                        getch();
                        break;
                    }
                    case('6'):
                    {
                        roleChosen = 0;
                        correct = 1;
                        delete User;
                        break;
                    }
                    case('0'):
                    {
                        StillRunning = 0;
                        correct = 1;
                        break;
                    }
                    default: correct = 0; break;

                }
            }
            break;
        }
        case (3):
        {
            cout << "Welcome back our dear client!" << endl;
            cout<< "Create order - 1\nCancel order - 2\nPay for order - 3\nShow order - 4\nShow products - 5\nChange role - 6nClose program - 0"<<endl;
            while(!correct)
            {
                fflush(stdin);
                dec = getch();
                switch(dec)
                {
                    case('1'):
                    {
                        correct = 1;
                        break;
                    }
                    case('5'):
                    {
                        correct = 1;
                        system("cls");
                        if(!User->getProductList().empty())
                        {
                            num = 0;
                            for(product i : User->getProductList())
                            {
                                cout<<num<<"    "
                                <<i.getName()<<endl
                                <<i.getPrice()<<endl
                                <<i.getDesc()<<endl
                                <<i.getQuantity()<<endl<<endl;
                            num++;
                            }
                        }
                        getch();
                        break;
                    }
                    case('6'):
                    {
                        roleChosen = 0;
                        correct = 1;
                        delete User;
                        break;
                    }
                    case('0'):
                    {
                        StillRunning = 0;
                        correct = 1;
                        break;
                    }
                    default: correct = 0; break;

                }
            }
            break;
        }
        default:
        {
            cout << "error" << endl;
        }
        }
    }
    delete User;
}
#include "superproekt.hpp"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    cout<<"Who are you?\nAdmin-1\nSeller-2\nOur Client-3\n";
    bool correct = false, StillRunning = true;
    char dec;
    user *User;
    while(!correct)
    {
    char dec = getch();
    switch(dec)
    {
        case('1'): 
        User = new admin();
        correct = 1;
        break;
        case('2'):
        User = new seller();
        correct = 1;
        break;
        case('3'):
        User = new client();
        correct = 1;
        break;
        default:
        break; 
    }
    }
    while(StillRunning)
    {
        system("cls");
        switch(User->getId())
        {
            case(1): cout<<"You are cool admin"<<endl; break;
            case(2): cout<<"Go make money, dog"<<endl; break;
            case(3): cout<<"Welcome back our dear client!"<<endl; break;
            default: cout<<"error"<<endl;
        }
        StillRunning = false;
    }
    getch();
    delete User;
}
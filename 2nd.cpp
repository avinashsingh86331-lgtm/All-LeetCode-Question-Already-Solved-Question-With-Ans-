#include<iostream>
using namespace std;

int main()
{
    int num = -12;
    
    //Condition to check if the number is negative or positive
    if (num >= 0)
    {
        if (num == 0)
            cout << "Zero";
        else
            cout << "The number is positive";
    }
    else
            cout << "The number is negative";
    
    return 0;
}
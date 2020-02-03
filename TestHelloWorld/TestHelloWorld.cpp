// TestHelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


int max(int a, int b)
{
 
    return (a > b) ? a : b;
}

int main()
{
    int a = 100; 
    int b = 200; 

    printf("max value is : %d", max(a, b));
}


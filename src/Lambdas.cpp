// Lambdas.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>
#include <iterator>
using namespace std;


int main()
{
    // the basic "hello world" lambda
    vector<int> v;
    for (int i = 0; i < 10; ++i) 
        v.push_back(i);

    for_each(v.begin(), v.end(), [](int n) {cout << n << " "; });
    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;
    for_each(v.begin(), 
             v.end(), 
             [](int n) 
                { 
                    cout << n << " "; 
                }
            );
    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;

    //multiple statements in the lambda
    for_each(v.begin(), v.end(), [](int n) {
        cout << n;
        if (n % 2 == 0) {
            cout << " even " << endl;
        } else {
            cout << " odd " << endl;
        }
    });

    std::cout << std::endl << "-----------------------" << std::endl;
    cout << endl;
    

    //deducing the return type from the code
    vector<int> v2;
    transform(v.begin(), v.end(), back_inserter(v2), [](int n) { return n * n * n; });
    for_each(v2.begin(), v2.end(), [](int n) { cout << n << " "; });
    cout << endl;
    
    std::cout << std::endl << "-----------------------" << std::endl;

    //explicitly specifying the return type
    vector<double> dv;
    transform(v.begin(), v.end(), back_inserter(dv), [](int n) -> double {
        if (n % 2 == 0) {
            return n * n * n;
        } else {
            return n / 2.0;
        }
    });

    for_each(dv.begin(), dv.end(), [](double x) { cout << x << " "; });
    cout << endl;

    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;
    
    //capturing by value explicitly  [x,y]
    int x = 3;
    int y = 7;
    cout << "printing elements between " << x << " and " << y << " inclusive" << endl;
    for_each(v.begin(), v.end(), [x,y](int n) 
        {
            if (n >= x && n <= y)
                cout << n << " ";
        });
    cout << endl;
    for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;
    
    //capturing by value implicitly  [=]
    x = 2;
    y = 9;
    cout << "printing elements between " << x << " and " << y << " inclusive" << endl;
    for_each(v.begin(), v.end(), [=](int n) 
        {
            if (n >= x && n <= y)
                cout << n << " ";
        });
    cout << endl;
    for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;

    //capturing by value and changing locally [=] mutable - also changing the param (int&)
    x = 1;
    y = 1;
    for_each(v.begin(), v.end(), [=](int& r) mutable {
        const int old = r;
        r *= 2;
        x = y;
        y = old;
    });

    cout << "doubling " << endl;
    for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
    cout << endl;
    cout << "x,y: " << x << ", " << y << endl;
    std::cout << std::endl << "-----------------------" << std::endl;

    //capturing by reference [&x, &y]  - also changing the param (int&)
    v.clear();
    for (int i = 0; i < 10; ++i) {v.push_back(i);}
    for_each(v.begin(), v.end(), [&x, &y](int& r) {
        const int old = r;
        r *= 2;
        x = y;
        y = old;
    });

    for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
    cout << endl;
    cout << "x,y: " << x << ", " << y << endl;
    cout << endl;
    std::cout << std::endl << "-----------------------" << std::endl;

    //capturing whole stack by reference (and a neater way to keep initializing these vectors)
    v.clear();
    int i = 0;
    generate_n(back_inserter(v), 10, [&] { return i++; }); // [&]() { return i++; } would have been ok too
    cout << "initializing" << endl;
    for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
    cout << endl;
    cout << "i: " << i << endl;

    std::cout << std::endl << "-----------------------" << std::endl;
return 0;
}


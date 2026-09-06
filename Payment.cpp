#include <iostream>
using namespace std;

// Abstraction
class Payment {
public:
    virtual bool pay(double amount) = 0;

    virtual ~Payment() {}
};
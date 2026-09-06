#include <iostream>

using namespace std;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment of Rs. "
             << amount << " received." << endl;

        return true;
    }
};
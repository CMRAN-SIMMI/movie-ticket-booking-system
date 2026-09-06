#include <iostream>
#include <string>

using namespace std;

class UpiPayment : public Payment {
private:
    bool shouldSucceed;

public:
    UpiPayment(bool shouldSucceed = true) {
        this->shouldSucceed = shouldSucceed;
    }

    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs. "
             << amount << "..." << endl;

        if (shouldSucceed) {
            cout << "UPI payment successful." << endl;
            return true;
        }

        cout << "UPI payment failed." << endl;
        return false;
    }
};
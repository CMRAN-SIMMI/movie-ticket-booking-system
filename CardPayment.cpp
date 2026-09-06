#include <iostream>

using namespace std;

class CardPayment : public Payment {
private:
    bool shouldSucceed;

public:
    CardPayment(bool shouldSucceed = true) {
        this->shouldSucceed = shouldSucceed;
    }

    bool pay(double amount) override {
        cout << "Processing Card payment of Rs. "
             << amount << "..." << endl;

        if (shouldSucceed) {
            cout << "Card payment successful." << endl;
            return true;
        }

        cout << "Card payment failed." << endl;
        return false;
    }
};
#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    Customer() {
        this->name = "";
        this->phone = "";
    }

    Customer(string name, string phone) {
        this->name = name;
        this->phone = phone;
    }

    string getName() {
        return name;
    }

    string getPhone() {
        return phone;
    }
};
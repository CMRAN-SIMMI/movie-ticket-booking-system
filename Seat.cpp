#include <iostream>
#include <string>
using namespace std;

class Seat {
private:
    int number;
    string type;

public:
    Seat() {
        this->number = 0;
        this->type = "";
    }

    Seat(int number, string type) {
        this->number = number;
        this->type = type;
    }

    int getNumber() {
        return number;
    }

    string getType() {
        return type;
    }

    void display() {
        cout << "Seat " << number
             << " [" << type << "]";
    }
};
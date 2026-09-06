#include <iostream>

using namespace std;

class ShowSeat {
private:
    Seat seat;
    bool booked;

public:
    ShowSeat() {
        this->booked = false;
    }

    ShowSeat(Seat seat) {
        this->seat = seat;
        this->booked = false;
    }

    int getSeatNumber() {
        return seat.getNumber();
    }

    string getSeatType() {
        return seat.getType();
    }

    bool isBooked() {
        return booked;
    }

    void book() {
        booked = true;
    }

    void release() {
        booked = false;
    }

    void display() {
        cout << "Seat " << seat.getNumber()
             << " [" << seat.getType() << "] - ";

        if (booked) {
            cout << "BOOKED";
        } else {
            cout << "AVAILABLE";
        }

        cout << endl;
    }
};
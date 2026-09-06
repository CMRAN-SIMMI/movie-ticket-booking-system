#include <iostream>
#include <vector>

using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen() {
        this->screenNumber = 0;
    }

    Screen(int screenNumber) {
        this->screenNumber = screenNumber;

        // Create physical seats for this screen
        for (int i = 1; i <= 10; i++) {
            if (i <= 4) {
                seats.push_back(Seat(i, "SILVER"));
            }
            else if (i <= 8) {
                seats.push_back(Seat(i, "GOLD"));
            }
            else {
                seats.push_back(Seat(i, "PLATINUM"));
            }
        }
    }

    int getScreenNumber() {
        return screenNumber;
    }

    vector<Seat>& getSeats() {
        return seats;
    }

    void displaySeats() {
        cout << "Screen " << screenNumber << endl;

        for (Seat& seat : seats) {
            seat.display();
            cout << endl;
        }
    }
};
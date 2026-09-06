#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Booking {
private:
    static int nextBookingId;

    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> selectedSeats;
    double totalAmount;
    bool confirmed;

public:
    Booking() {
        this->bookingId = nextBookingId++;
        this->customer = nullptr;
        this->show = nullptr;
        this->totalAmount = 0;
        this->confirmed = false;
    }

    Booking(Customer* customer, Show* show,
            vector<ShowSeat*> selectedSeats,
            double totalAmount) {

        this->bookingId = nextBookingId++;
        this->customer = customer;
        this->show = show;
        this->selectedSeats = selectedSeats;
        this->totalAmount = totalAmount;
        this->confirmed = false;
    }

    int getBookingId() {
        return bookingId;
    }

    Customer* getCustomer() {
        return customer;
    }

    Show* getShow() {
        return show;
    }

    vector<ShowSeat*>& getSelectedSeats() {
        return selectedSeats;
    }

    double getTotalAmount() {
        return totalAmount;
    }

    bool isConfirmed() {
        return confirmed;
    }

    void confirm() {
        confirmed = true;
    }

    void cancel() {
        confirmed = false;

        for (ShowSeat* seat : selectedSeats) {
            seat->release();
        }
    }
};

int Booking::nextBookingId = 1001;
#include <iostream>

using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking) {
        cout << "\n========== TICKET ==========" << endl;

        cout << "Booking ID : "
             << booking->getBookingId() << endl;

        cout << "Customer   : "
             << booking->getCustomer()->getName() << endl;

        cout << "Movie      : "
             << booking->getShow()->getMovie()->getTitle() << endl;

        cout << "Screen     : "
             << booking->getShow()->getScreen()->getScreenNumber()
             << endl;

        cout << "Time       : "
             << booking->getShow()->getStartTime() << endl;

        cout << "Seats      : ";

        for (ShowSeat* seat : booking->getSelectedSeats()) {
            cout << seat->getSeatNumber() << " ";
        }

        cout << endl;

        cout << "Total      : Rs. "
             << booking->getTotalAmount() << endl;

        cout << "Status     : CONFIRMED" << endl;

        cout << "============================" << endl;
    }
};
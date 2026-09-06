#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    Booking* bookTicket(Customer* customer,
                        Show* show,
                        vector<int> seatNumbers,
                        Payment* payment) {

        vector<ShowSeat*> selectedSeats;

        // Find and validate selected seats
        for (int number : seatNumbers) {
            ShowSeat* selectedSeat = findSeat(show, number);

            if (selectedSeat == nullptr) {
                cout << "Invalid seat number: "
                     << number << endl;
                return nullptr;
            }

            if (selectedSeat->isBooked()) {
                cout << "Seat " << number
                     << " is already BOOKED." << endl;
                return nullptr;
            }

            selectedSeats.push_back(selectedSeat);
        }

        // Calculate total price
        double total = priceCalculator.calculateTotal(selectedSeats);

        cout << "\nTotal amount: Rs. " << total << endl;

        // Temporarily mark seats as booked
        for (ShowSeat* seat : selectedSeats) {
            seat->book();
        }

        // Create booking
        Booking* booking = new Booking(
            customer,
            show,
            selectedSeats,
            total
        );

        // Process payment
        if (!payment->pay(total)) {
            cout << "Booking failed. Releasing seats..." << endl;

            for (ShowSeat* seat : selectedSeats) {
                seat->release();
            }

            delete booking;
            return nullptr;
        }

        // Payment successful
        booking->confirm();

        cout << "Booking confirmed successfully!" << endl;

        ticketPrinter.printTicket(booking);

        return booking;
    }

    void cancelBooking(Booking* booking) {
        if (booking == nullptr) {
            cout << "Invalid booking." << endl;
            return;
        }

        if (!booking->isConfirmed()) {
            cout << "Booking is not confirmed." << endl;
            return;
        }

        booking->cancel();

        cout << "Booking "
             << booking->getBookingId()
             << " cancelled successfully." << endl;

        cout << "Seats are AVAILABLE again." << endl;
    }

private:
    ShowSeat* findSeat(Show* show, int seatNumber) {
        for (ShowSeat& seat : show->getShowSeats()) {
            if (seat.getSeatNumber() == seatNumber) {
                return &seat;
            }
        }

        return nullptr;
    }
};
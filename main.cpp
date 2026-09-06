#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

void displayMovies(vector<Movie>& movies) {
    cout << "\n========== MOVIES ==========\n";

    for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". ";
        movies[i].display();
    }
}

void displayShows(vector<Show>& shows) {
    cout << "\n========== SHOWS ==========\n";

    for (Show& show : shows) {
        show.displayShow();
    }
}

Show* findShow(vector<Show>& shows, int showId) {
    for (Show& show : shows) {
        if (show.getShowId() == showId) {
            return &show;
        }
    }

    return nullptr;
}

void displaySeatLayout(Show* show) {
    if (show == nullptr) {
        cout << "Invalid show.\n";
        return;
    }

    show->displaySeats();
}

Payment* createPayment(int choice) {
    if (choice == 1) {
        int result;
        cout << "Enter payment result (1 = success, 0 = failure): ";
        cin >> result;

        return new UpiPayment(result == 1);
    }

    if (choice == 2) {
        int result;
        cout << "Enter payment result (1 = success, 0 = failure): ";
        cin >> result;

        return new CardPayment(result == 1);
    }

    if (choice == 3) {
        return new CashPayment();
    }

    return nullptr;
}

int main() {

    // Create cinema
    Cinema cinema("GEHU Cinema");

    cinema.addScreen(1);
    cinema.addScreen(2);

    // Create movies
    Movie movie1("Avengers: Endgame", "English", 181);
    Movie movie2("3 Idiots", "Hindi", 170);

    vector<Movie> movies = {
        movie1,
        movie2
    };

    // Create shows
    vector<Screen>& screens = cinema.getScreens();

    vector<Show> shows;

    shows.push_back(
        Show(101, &movies[0], &screens[0], "06:00 PM")
    );

    shows.push_back(
        Show(102, &movies[0], &screens[1], "09:00 PM")
    );

    shows.push_back(
        Show(103, &movies[1], &screens[0], "03:00 PM")
    );

    Customer customer("Simran", "9876543210");

    BookingService bookingService;

    vector<Booking*> bookings;

    int choice;

    do {
        cout << "\n\n========== MOVIE TICKET BOOKING ==========\n";
        cout << "1. List all movies\n";
        cout << "2. List shows\n";
        cout << "3. Display seat layout\n";
        cout << "4. Book seats\n";
        cout << "5. Cancel booking\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            displayMovies(movies);
            break;

        case 2:
            displayShows(shows);
            break;

        case 3: {
            int showId;

            cout << "Enter show ID: ";
            cin >> showId;

            Show* show = findShow(shows, showId);

            if (show == nullptr) {
                cout << "Invalid show ID.\n";
            } else {
                displaySeatLayout(show);
            }

            break;
        }

        case 4: {
            int showId;
            int numberOfSeats;

            cout << "Enter show ID: ";
            cin >> showId;

            Show* show = findShow(shows, showId);

            if (show == nullptr) {
                cout << "Invalid show ID.\n";
                break;
            }

            show->displaySeats();

            cout << "\nHow many seats do you want to book? ";
            cin >> numberOfSeats;

            if (numberOfSeats <= 0) {
                cout << "Invalid number of seats.\n";
                break;
            }

            vector<int> seatNumbers;

            for (int i = 0; i < numberOfSeats; i++) {
                int seatNumber;

                cout << "Enter seat number " << i + 1 << ": ";
                cin >> seatNumber;

                seatNumbers.push_back(seatNumber);
            }

            cout << "\n========== PAYMENT ==========\n";
            cout << "1. UPI\n";
            cout << "2. Card\n";
            cout << "3. Cash\n";
            cout << "Enter payment method: ";

            int paymentChoice;
            cin >> paymentChoice;

            Payment* payment = createPayment(paymentChoice);

            if (payment == nullptr) {
                cout << "Invalid payment method.\n";
                break;
            }

            Booking* booking = bookingService.bookTicket(
                &customer,
                show,
                seatNumbers,
                payment
            );

            if (booking != nullptr) {
                bookings.push_back(booking);
            }

            delete payment;

            break;
        }

        case 5: {
            int bookingId;

            cout << "Enter booking ID to cancel: ";
            cin >> bookingId;

            Booking* bookingToCancel = nullptr;

            for (Booking* booking : bookings) {
                if (booking->getBookingId() == bookingId) {
                    bookingToCancel = booking;
                    break;
                }
            }

            if (bookingToCancel == nullptr) {
                cout << "Booking not found.\n";
            } else {
                bookingService.cancelBooking(bookingToCancel);
            }

            break;
        }

        case 6:
            cout << "Thank you for using the Movie Ticket Booking System!\n";
            break;

        default:
            cout << "Invalid menu choice. Please try again.\n";
        }

    } while (choice != 6);

    for (Booking* booking : bookings) {
        delete booking;
    }

    return 0;
}
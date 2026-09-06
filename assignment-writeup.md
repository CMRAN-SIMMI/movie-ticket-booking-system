# TCS-504 System Design — Assignment 1

## A. Requirement Analysis

### Functional Requirements

| ID  | Functional Requirement                                                                                                                                                             |
| --- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| FR1 | The system shall list all movies currently playing with title, language, and duration.                                                                                             |
| FR2 | The system shall display shows for the selected movie, including show ID, screen number, and start time.                                                                           |
| FR3 | The system shall display the seat layout of a selected show with seat number, seat type, and availability status.                                                                  |
| FR4 | The system shall allow the customer to book one or more available seats and reject invalid or already-booked seats.                                                                |
| FR5 | The system shall calculate seat prices according to seat type: SILVER ₹150, GOLD ₹250, and PLATINUM ₹400.                                                                          |
| FR6 | The system shall support payment through UPI, Card, or Cash. If UPI or Card payment fails, the booking shall not be confirmed and the selected seats shall become available again. |
| FR7 | The system shall print a ticket containing booking ID, customer name, movie, screen, show time, seat numbers, total amount, and booking status.                                    |
| FR8 | The system shall allow a confirmed booking to be cancelled, after which its seats shall become AVAILABLE again.                                                                    |

### Non-Functional Requirements

| ID   | Non-Functional Requirement                                                                   |
| ---- | -------------------------------------------------------------------------------------------- |
| NFR1 | The system should be modular, with separate classes for major responsibilities.              |
| NFR2 | The system should be easy to maintain and extend.                                            |
| NFR3 | Payment methods should be extensible without changing the main booking logic.                |
| NFR4 | The system should validate invalid show IDs, seat numbers, payment methods, and booking IDs. |
| NFR5 | The system should provide clear console messages for successful and failed operations.       |
| NFR6 | The implementation should demonstrate object-oriented programming principles.                |


## B. Noun–Verb Analysis

### Noun Analysis

| Noun            | Class / Decision                         |
| --------------- | ---------------------------------------- |
| Movie           | Class                                    |
| Seat            | Class                                    |
| Screen          | Class                                    |
| Cinema          | Class                                    |
| Show            | Class                                    |
| ShowSeat        | Class                                    |
| Customer        | Class                                    |
| Booking         | Class                                    |
| Payment         | Abstract Class                           |
| UPI Payment     | Derived Class                            |
| Card Payment    | Derived Class                            |
| Cash Payment    | Derived Class                            |
| Price           | Handled by PriceCalculator               |
| Ticket          | Handled by TicketPrinter                 |
| Booking Service | Class                                    |
| Seat Layout     | Display operation, not a separate class  |
| Menu            | Main program logic, not a separate class |

### Verb Analysis

| Verb            | Method / Operation                       |
| --------------- | ---------------------------------------- |
| List movies     | `displayMovies()`                        |
| Display shows   | `displayShows()`                         |
| Find show       | `findShow()`                             |
| Display seats   | `displaySeatLayout()` / `displaySeats()` |
| Book seats      | `bookTicket()`                           |
| Calculate price | `calculateTotal()`                       |
| Pay             | `pay()`                                  |
| Print ticket    | `printTicket()`                          |
| Cancel booking  | `cancelBooking()`                        |
| Book a seat     | `book()`                                 |
| Release a seat  | `release()`                              |

### Conclusion

The nouns representing independent entities are converted into classes, while actions are converted into methods. UI concepts such as menu and seat layout are kept outside the domain model because they do not represent independent objects with their own lifecycle.


## C. Relationship Analysis

| Relationship                                 | Type        | Multiplicity | Justification using Lifetime Test                                                                                                 |
| -------------------------------------------- | ----------- | ------------ | --------------------------------------------------------------------------------------------------------------------------------- |
| Cinema → Screen                              | Composition | 1 : many     | Screens belong to a cinema. If the Cinema object is destroyed, its owned Screen objects are also destroyed.                       |
| Screen → Seat                                | Composition | 1 : many     | Physical seats belong to a screen and are created as part of the screen. Their lifetime depends on the screen.                    |
| Show → ShowSeat                              | Composition | 1 : many     | ShowSeats are created for a particular show and represent seat status for that show. They do not exist independently of the show. |
| Show → Movie                                 | Aggregation | many : 1     | A movie can exist independently and can be used in multiple shows. Destroying a Show does not destroy the Movie.                  |
| Booking → ShowSeat                           | Aggregation | 1 : many     | A booking refers to selected ShowSeats, but the ShowSeats belong to the Show and continue to exist after cancellation.            |
| Booking → Customer                           | Association | many : 1     | A booking is associated with a customer, but Customer can exist independently.                                                    |
| Show → Screen                                | Association | many : 1     | A show uses a screen, but the screen exists independently of a particular show.                                                   |
| BookingService → Booking                     | Association | 1 : many     | BookingService creates and manages bookings, but Booking is a separate domain object.                                             |
| Payment → UpiPayment/CardPayment/CashPayment | Inheritance | 1 : many     | The derived payment classes implement the common Payment abstraction.                                                             |

### Lifetime Test

The main rule used is:

> If the child object's lifetime depends on the parent object's lifetime, use Composition. If the child can exist independently, use Aggregation.

Therefore, Cinema–Screen, Screen–Seat, and Show–ShowSeat are modeled as composition, while Show–Movie and Booking–ShowSeat are modeled as aggregation.


## D. Class Diagram

```text
+----------------------+
|        Movie         |
+----------------------+
| - title : string     |
| - language : string  |
| - duration : int     |
+----------------------+
| + Movie()            |
| + Movie(...)         |
| + getTitle()         |
| + getLanguage()      |
| + getDuration()      |
| + display()          |
+----------------------+

+----------------------+
|        Seat          |
+----------------------+
| - number : int       |
| - type : string      |
+----------------------+
| + Seat()             |
| + Seat(...)          |
| + getNumber()        |
| + getType()          |
| + display()          |
+----------------------+

+----------------------+
|       Screen         |
+----------------------+
| - screenNumber : int |
| - seats : vector     |
+----------------------+
| + Screen()           |
| + Screen(...)        |
| + getScreenNumber()  |
| + getSeats()         |
| + displaySeats()     |
+----------------------+

+----------------------+
|       Cinema         |
+----------------------+
| - theatreName:string |
| - screens : vector   |
+----------------------+
| + Cinema()           |
| + Cinema(...)        |
| + addScreen()        |
| + getTheatreName()   |
| + getScreens()       |
| + displayScreens()   |
+----------------------+

+----------------------+
|       ShowSeat       |
+----------------------+
| - seat : Seat        |
| - booked : bool      |
+----------------------+
| + ShowSeat()         |
| + ShowSeat(...)      |
| + getSeatNumber()    |
| + getSeatType()      |
| + isBooked()         |
| + book()             |
| + release()          |
| + display()          |
+----------------------+

+----------------------+
|        Show          |
+----------------------+
| - showId : int       |
| - movie : Movie*     |
| - screen : Screen*   |
| - startTime : string |
| - showSeats : vector |
+----------------------+
| + Show()             |
| + Show(...)          |
| + getShowId()        |
| + getMovie()         |
| + getScreen()        |
| + getStartTime()     |
| + getShowSeats()     |
| + displayShow()      |
| + displaySeats()     |
+----------------------+

+----------------------+
|      Customer        |
+----------------------+
| - name : string      |
| - phone : string     |
+----------------------+
| + Customer()         |
| + Customer(...)      |
| + getName()          |
| + getPhone()         |
+----------------------+

+----------------------+
|       Booking        |
+----------------------+
| - nextBookingId:int  |
| - bookingId : int    |
| - customer : Customer*|
| - show : Show*       |
| - selectedSeats      |
| - totalAmount:double |
| - confirmed : bool   |
+----------------------+
| + Booking()          |
| + Booking(...)       |
| + getBookingId()     |
| + getCustomer()      |
| + getShow()          |
| + getSelectedSeats() |
| + getTotalAmount()   |
| + isConfirmed()      |
| + confirm()          |
| + cancel()           |
+----------------------+

          «abstract»
+----------------------+
|       Payment        |
+----------------------+
|                      |
+----------------------+
| + pay(amount) = 0    |
+----------------------+
          △
          |
    ┌─────┼─────┐
    |     |     |
+-------+ +-------+ +-------+
|  UPI  | | Card  | | Cash  |
+-------+ +-------+ +-------+
| +pay()| | +pay()| | +pay()|
+-------+ +-------+ +-------+

+----------------------+
|   PriceCalculator    |
+----------------------+
| + getSeatPrice()     |
| + calculateTotal()   |
+----------------------+

+----------------------+
|    TicketPrinter     |
+----------------------+
| + printTicket()      |
+----------------------+

+----------------------+
|    BookingService    |
+----------------------+
| - priceCalculator    |
| - ticketPrinter      |
+----------------------+
| + bookTicket()       |
| + cancelBooking()    |
| - findSeat()         |
+----------------------+
```

### Relationships

```text
Cinema ◆──── 1..* Screen
Screen ◆──── 1..* Seat
Show ◆────── 1..* ShowSeat
Show ◇────── 1 Movie
Booking ◇──── 1..* ShowSeat
Booking ──▶ Customer
Show ──▶ Screen
BookingService ──▶ Booking

Payment ──▷ UpiPayment
Payment ──▷ CardPayment
Payment ──▷ CashPayment
```

Legend:

* `◆` = Composition
* `◇` = Aggregation
* `──▶` = Association
* `──▷` = Inheritance
* `-` = Private
* `+` = Public
* `#` = Protected


## E. Sequence Diagram – Book a Ticket and Make Payment

```text
Customer        BookingService       Show       ShowSeat
   |                  |                |             |
   | bookTicket()     |                |             |
   |----------------->|                |             |
   |                  | findSeat()     |             |
   |                  |--------------->|             |
   |                  |                |             |
   |                  |<---------------|             |
   |                  |                |             |
   |                  | check status   |             |
   |                  |----------------------------->|
   |                  |                |             |
   |                  |<-----------------------------|
   |                  |                |             |
   |                  | calculateTotal()             |
   |                  |------------------------------> PriceCalculator
   |                  |                               |
   |                  |<------------------------------|
   |                  |                |             |
   |                  | book()         |             |
   |                  |----------------------------->|
   |                  |                |             |
   |                  |                |             |
   |                  | «create» Booking             |
   |                  |------------------------------> Booking
   |                  |                               |
   |                  | pay(total)                    |
   |                  |------------------------------> Payment
   |                  |                               |
   |                  |<------------- success/failure |
   |                  |                               |
   |                  | confirm()                     |
   |                  |------------------------------> Booking
   |                  |                               |
   |                  | printTicket()                 |
   |                  |------------------------------> TicketPrinter
   |                  |                               |
   |<-----------------| ticket / booking result      |
   |                  |                               |
```

### Detailed Flow

1. Customer selects a show and provides seat numbers.
2. `BookingService` finds the requested `ShowSeat` objects.
3. The service checks whether the seats are available.
4. `PriceCalculator` calculates the total according to seat types.
5. The selected seats are temporarily marked as booked.
6. A `Booking` object is created.
7. The selected `Payment` implementation processes the payment.
8. If payment succeeds, the booking is confirmed.
9. `TicketPrinter` prints the ticket.
10. If payment fails, the seats are released and the booking is not confirmed.


## F. Demo Run and Test Cases

### Test Case 1 – List Movies

**Input:** `1`

**Expected Result:**
The system displays all currently playing movies with their title, language, and duration.

---

### Test Case 2 – List Shows

**Input:** `2`

**Expected Result:**
The system displays show IDs, movies, screen numbers, and start times.

Example:

```text
========== SHOWS ==========
Show ID: 101 | Movie: Avengers: Endgame | Screen: 1 | Time: 06:00 PM
Show ID: 102 | Movie: Avengers: Endgame | Screen: 2 | Time: 09:00 PM
Show ID: 103 | Movie: 3 Idiots | Screen: 1 | Time: 03:00 PM
```

---

### Test Case 3 – Display Seat Layout

**Input:** `3`, followed by show ID `101`

**Expected Result:**

```text
Seat 1 [SILVER] - AVAILABLE
Seat 2 [SILVER] - AVAILABLE
Seat 3 [SILVER] - AVAILABLE
Seat 4 [SILVER] - AVAILABLE
Seat 5 [GOLD] - AVAILABLE
Seat 6 [GOLD] - AVAILABLE
Seat 7 [GOLD] - AVAILABLE
Seat 8 [GOLD] - AVAILABLE
Seat 9 [PLATINUM] - AVAILABLE
Seat 10 [PLATINUM] - AVAILABLE
```

---

### Test Case 4 – Successful Booking

Select Show `101` and book seats `2` and `6`.

Seat 2 = SILVER = ₹150
Seat 6 = GOLD = ₹250

Total:

```text
₹150 + ₹250 = ₹400
```

Choose UPI/Card/Cash and provide successful payment.

**Expected Result:**

```text
Payment successful.
Booking confirmed successfully!

========== TICKET ==========
Booking ID : 1001
Movie      : Avengers: Endgame
Screen     : 1
Time       : 06:00 PM
Seats      : 2 6
Total      : Rs. 400
Status     : CONFIRMED
```

---

### Test Case 5 – Already Booked Seat

Try booking seat `2` again for Show `101`.

**Expected Result:**

```text
Seat 2 is already BOOKED.
```

The system rejects the booking.

---

### Test Case 6 – Failed Payment

Select an available seat and choose UPI or Card.

Enter:

```text
Payment result: 0
```

**Expected Result:**

```text
UPI payment failed.
Booking failed. Releasing seats...
```

The booking is not confirmed and the selected seats become AVAILABLE again.

---

### Test Case 7 – Cancellation

Cancel a confirmed booking using its booking ID.

**Expected Result:**

```text
Booking 1001 cancelled successfully.
Seats are AVAILABLE again.
```

The previously booked seats become available again.


## G. SOLID Principles Mapping

| Principle                               | Application in the System                                                                                                                                           |
| --------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **S – Single Responsibility Principle** | `BookingService` handles booking workflow, `PriceCalculator` handles pricing, and `TicketPrinter` handles ticket printing. Each class has a focused responsibility. |
| **O – Open/Closed Principle**           | New payment methods can be added by creating another class derived from `Payment`, without modifying the existing booking workflow.                                 |
| **L – Liskov Substitution Principle**   | `UpiPayment`, `CardPayment`, and `CashPayment` can be used through a `Payment*` pointer because each derived class implements `pay()`.                              |
| **I – Interface Segregation Principle** | The `Payment` abstraction contains only the required `pay()` operation. Unnecessary operations such as `refund()` are not forced on payment classes.                |
| **D – Dependency Inversion Principle**  | `BookingService` works with the `Payment` abstraction rather than depending on a specific payment implementation such as CardPayment.                               |

### One Thing Deliberately NOT Done

A real payment gateway and database were deliberately not implemented.

The assignment scope requires a console-based movie ticket booking system with simulated UPI, Card, and Cash payment. Adding a real payment gateway or database would increase complexity and introduce functionality outside the required scope.

#include <string>

using namespace std;

class PriceCalculator {
private:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

public:
    double getSeatPrice(string seatType) {
        if (seatType == "SILVER") {
            return SILVER_PRICE;
        }

        if (seatType == "GOLD") {
            return GOLD_PRICE;
        }

        if (seatType == "PLATINUM") {
            return PLATINUM_PRICE;
        }

        return 0.0;
    }

    double calculateTotal(vector<ShowSeat*>& seats) {
        double total = 0.0;

        for (ShowSeat* seat : seats) {
            total += getSeatPrice(seat->getSeatType());
        }

        return total;
    }
};
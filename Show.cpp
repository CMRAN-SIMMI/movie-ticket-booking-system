#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Show {
private:
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show() {
        this->showId = 0;
        this->movie = nullptr;
        this->screen = nullptr;
        this->startTime = "";
    }

    Show(int showId, Movie* movie, Screen* screen, string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        for (Seat& seat : screen->getSeats()) {
            showSeats.push_back(ShowSeat(seat));
        }
    }

    int getShowId() {
        return showId;
    }

    Movie* getMovie() {
        return movie;
    }

    Screen* getScreen() {
        return screen;
    }

    string getStartTime() {
        return startTime;
    }

    vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    void displayShow() {
        cout << "Show ID: " << showId
             << " | Movie: " << movie->getTitle()
             << " | Screen: " << screen->getScreenNumber()
             << " | Time: " << startTime << endl;
    }

    void displaySeats() {
        cout << "\nSeat Layout - Screen "
             << screen->getScreenNumber() << endl;

        for (ShowSeat& showSeat : showSeats) {
            showSeat.display();
        }
    }
};
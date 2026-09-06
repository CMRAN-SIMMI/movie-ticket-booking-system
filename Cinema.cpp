#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cinema {
private:
    string theatreName;
    vector<Screen> screens;

public:
    Cinema() {
        this->theatreName = "";
    }

    Cinema(string theatreName) {
        this->theatreName = theatreName;
    }

    void addScreen(int screenNumber) {
        screens.push_back(Screen(screenNumber));
    }

    string getTheatreName() {
        return theatreName;
    }

    vector<Screen>& getScreens() {
        return screens;
    }

    void displayScreens() {
        cout << "Cinema: " << theatreName << endl;

        for (Screen& screen : screens) {
            cout << "Screen "
                 << screen.getScreenNumber() << endl;
        }
    }
};
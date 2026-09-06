#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;

public:
    // Compile-time polymorphism: default constructor
    Movie() {
        this->title = "";
        this->language = "";
        this->duration = 0;
    }

    // Compile-time polymorphism: parameterized constructor
    Movie(string title, string language, int duration) {
        this->title = title;
        this->language = language;
        this->duration = duration;
    }

    string getTitle() {
        return title;
    }

    string getLanguage() {
        return language;
    }

    int getDuration() {
        return duration;
    }

    void display() {
        cout << title << " | "
             << language << " | "
             << duration << " mins" << endl;
    }
};
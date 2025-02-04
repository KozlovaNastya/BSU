#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Train {
private:
    int numberOfTrain;
    string station;
    string type;
    string departureTime;
    int travelTime;

public:
    Train(int numberOfTrain = 0, string station = "none", string type = "none", string departureTime = "none", int travelTime = 0) :
        numberOfTrain(numberOfTrain), station(station), type(type), departureTime(departureTime), travelTime(travelTime) {}

    void setNumberOfTrain(int n) { numberOfTrain = n; }
    void setStation(string s) { station = s; }
    void setType(string t) { type = t; }
    void setDepartureTime(string t) { departureTime = t; }
    void setTravelTime(int tt) { travelTime = tt; }

    int getNumberOfTrain() const { return numberOfTrain; }
    string getStation() const { return station; }
    string getType() const { return type; }
    string getDepartureTime() const { return departureTime; }
    int getTravelTime() const { return travelTime; }

    void print() const {
        cout << numberOfTrain << ';' << station << ';' << type << ';' << departureTime << ';' << travelTime << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("trains.txt");
    if (!inputFile) {
        cerr << "Failed to open the file trains.txt" << endl;
        return 1;
    }

    if (inputFile.peek() == EOF) {
        cerr << "File trains.txt is empty" << endl;
        return 1;
    }

    vector<Train> trains;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string temp;
        Train train;

        getline(ss, temp, ';');
        train.setNumberOfTrain(stoi(temp));
        getline(ss, temp, ';');
        train.setStation(temp);
        getline(ss, temp, ';');
        train.setType(temp);
        getline(ss, temp, ';');
        train.setDepartureTime(temp);
        getline(ss, temp, ';');
        train.setTravelTime(stoi(temp));

        trains.push_back(train);
    }

    inputFile.close();

    sort(trains.begin(), trains.end(), [](const Train& a, const Train& b) {
        return a.getDepartureTime() < b.getDepartureTime();
    });

    for (const auto& train : trains) {
        train.print();
    }

    string startTime, endTime;
    cout << "\nEnter start time (HH:MM): ";
    cin >> startTime;
    cout << "Enter end time (HH:MM): ";
    cin >> endTime;

    for (const auto& train : trains) {
        if (train.getDepartureTime() >= startTime && train.getDepartureTime() <= endTime) {
            train.print();
        }
    }

    string stationName;
    cout << "Enter station name: ";
    cin >> stationName;

    for (const auto& train : trains) {
        if (train.getStation() == stationName) {
            train.print();
        }
    }

    cout << "Trains at station " << stationName << endl;
    for (const auto& train : trains) {
        if (train.getStation() == stationName && train.getType() == "High-speed") {
            train.print();
        }
    }

    Train* fastestTrain = nullptr;
    for (auto& train : trains) {
        if (train.getStation() == stationName) {
            if (fastestTrain == nullptr || train.getTravelTime() < fastestTrain->getTravelTime()) {
                fastestTrain = &train;
            }
        }
    }

    if (fastestTrain) {
        cout << "The fastest train at station " << stationName << endl;
        fastestTrain->print();
    } else {
        cout << "No trains found at station " << stationName << endl;
    }

    return 0;
}

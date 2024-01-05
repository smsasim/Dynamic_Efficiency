#include "AirportModels.h"
#include<iostream>
#include<string>
#include <iomanip>
#include <cstring>

using namespace std;

namespace sdds
{
    Airport::Airport(const string c, const string n, const string ct, const string st, const string cn, double lat, double lon)
    {
        code = c;
        name = n;
        city = ct;
        state = st;
        country = cn;
        latitude = lat;
        longitude = lon;
    }

    bool Airport::isEmpty() const 
    {
        return code.empty() && name.empty() && city.empty() && state.empty() &&
            country.empty() && latitude == 0.0 && longitude == 0.0;
    }

    ostream& operator<<(ostream& os, const Airport& airport) {
        if (airport.isEmpty()) {
            os << "Empty Airport";
        }
        else {
            os << right << setw(20) << setfill('.') << "Airport Code" << " : " << left << setw(30) << setfill('.') << airport.code << '\n'
                << right << setw(20) << setfill('.') << "Airport Name" << " : " << left << setw(30) << setfill('.') << airport.name << '\n'
                << right << setw(20) << setfill('.') << "City" << " : " << left << setw(30) << setfill('.') << airport.city << '\n'
                << right << setw(20) << setfill('.') << "State" << " : " << left << setw(30) << setfill('.') << airport.state << '\n'
                << right << setw(20) << setfill('.') << "Country" << " : " << left << setw(30) << setfill('.') << airport.country << '\n'
                << right << setw(20) << setfill('.') << "Latitude" << " : " << left << setw(30) << setfill('.') << airport.latitude << '\n'
                << right << setw(20) << setfill('.') << "Longitude" << " : " << left << setw(30) << setfill('.') << airport.longitude << setfill(' ') << endl;
        }
        return os;
    }

    void AirportLog::resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        Airport* newAirportArray = new Airport[capacity];
        for (size_t i = 0; i < count; ++i) {
            newAirportArray[i] = airportArray[i];
        }
        delete[] airportArray;
        airportArray = newAirportArray;
    }

    AirportLog::AirportLog()
    {
        airportArray = nullptr; 
        count = 0; 
        capacity = 0;
    }

    AirportLog::AirportLog(const string filename){
        airportArray = nullptr;
        count = 0;
        capacity = 0;
        
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open the file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line);

        size_t numAirports = 0;
        while (getline(file, line)) {
            numAirports++;
        }

        airportArray = new Airport[numAirports];
        capacity = numAirports;

        file.clear();
        file.seekg(0, ios::beg);
        getline(file, line);

        size_t index = 0;
        while (file) {
            string code, name, city, state, country;
            double latitude, longitude;
            string temp;
            getline(file, code, ',');
            if (code.empty())
                continue;
            getline(file, name, ',');
            getline(file, city, ',');
            getline(file, state, ',');
            getline(file, country, ',');
            file >> latitude;
            file.ignore(1);
            file >> longitude;
            getline(file, temp);

            airportArray[index++] = Airport(code, name, city, state, country, latitude, longitude);
        }

        count = numAirports;
        file.close();
    }

    AirportLog::~AirportLog() {
        delete[] airportArray;
    }

    void AirportLog::addAirport(const Airport& airport) {
        if (count == capacity) {
            resize();
        }
        airportArray[count++] = airport;
    }

    AirportLog AirportLog::findAirport(const char* state, const char* country) const {
        AirportLog result;
        for (size_t i = 0; i < count; ++i) {
            if (strcmp(airportArray[i].state.c_str(), state) == 0 && strcmp(airportArray[i].country.c_str(), country) == 0) {
                result.addAirport(airportArray[i]);
            }
        }
        return result;
    }

    Airport AirportLog::operator[](size_t index) const {
        if (index < count) {
            return airportArray[index];
        }
        return Airport();
    }

    AirportLog::operator size_t() const {
        return count;
    }

    AirportLog::AirportLog(const AirportLog& other) : count(other.count), capacity(other.capacity) {
        airportArray = new Airport[capacity];
        for (size_t i = 0; i < count; ++i) {
            airportArray[i] = other.airportArray[i];
        }
    }

    AirportLog& AirportLog::operator=(const AirportLog& other) {
        if (this != &other) {
            delete[] airportArray;

            count = other.count;
            capacity = other.capacity;
            airportArray = new Airport[capacity];
            for (size_t i = 0; i < count; ++i) {
                airportArray[i] = other.airportArray[i];
            }
        }
        return *this;
    }

    AirportLog::AirportLog(AirportLog&& other) noexcept
        : airportArray(other.airportArray), count(other.count), capacity(other.capacity) {
        other.airportArray = nullptr;
        other.count = 0;
        other.capacity = 0;
    }

    AirportLog& AirportLog::operator=(AirportLog&& other) noexcept {
        if (this != &other) {
            delete[] airportArray;

            airportArray = other.airportArray;
            count = other.count;
            capacity = other.capacity;

            other.airportArray = nullptr;
            other.count = 0;
            other.capacity = 0;
        }
        return *this;
    }
}
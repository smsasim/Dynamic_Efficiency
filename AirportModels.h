#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <fstream>
#include <string>

namespace sdds
{
    struct Airport {
        std::string code;
        std::string name;
        std::string city;
        std::string state;
        std::string country;
        double latitude;
        double longitude;

        Airport(const std::string c = "", const std::string n = "",
            const std::string ct = "", const std::string st = "",
            const std::string cn = "", double lat = 0.0, double lon = 0.0);

        bool isEmpty() const;
    };

    std::ostream& operator<<(std::ostream& os, const Airport& airport);


    class AirportLog {
    private:
        Airport* airportArray;
        size_t count;
        size_t capacity;

        void resize();

    public:
        AirportLog();
        AirportLog(const std::string filename);
        ~AirportLog();
        AirportLog(const AirportLog& other);
        AirportLog& operator=(const AirportLog& other);
        AirportLog(AirportLog&& other) noexcept;
        AirportLog& operator=(AirportLog&& other) noexcept;

        void addAirport(const Airport& airport);
        AirportLog findAirport(const char* state, const char* country) const;
        Airport operator[](size_t index) const;
        operator size_t() const;
    };
}

#endif
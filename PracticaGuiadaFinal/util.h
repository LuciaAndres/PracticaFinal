#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Color.h"
#include "Vector3D.h"
using namespace std;

const double PI = 3.14159265358979;
const double DEG2RAD = PI / 180.0;
const double RAD2DEG = 180.0 / PI;
inline double deg2rad(double d) { return d * DEG2RAD; }
inline double rad2deg(double r) { return r * RAD2DEG; }

inline double getRand(double min, double max) {
    static const int PRECISION = 10000;
    double d = max - min;
    int ir = rand() % PRECISION;
    double r = min + (double)ir / PRECISION * d;
    return r;
}
inline double getRand(double max = 1) { return getRand(0, max); }

inline vector<string> split(string line, char delim = ' ') {
    vector<string> words;
    string word;
    istringstream ss(line);
    while (getline(ss, word, delim)) {
        words.push_back(word);
    }
    return words;
}

/* TRIMMING */
inline string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars)); return str;
}
inline string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1); return str;
}
inline string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    return ltrim(rtrim(str, chars), chars);
}

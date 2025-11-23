//
// Created by cddhi on 6/16/2025.
//

#include "Bacterium.h"

#include "Bacterium.h"
#include <sstream>

// COnstructtor for bacterium
istream& operator>>(istream& is, Bacterium& bacterium) {
    string line;
    getline(is, line);

    if(line.empty()) return is;

    stringstream ss(line);
    string diseases_str;

    getline(ss, bacterium.name, ',');
    getline(ss, bacterium.species, ',');
    ss >> bacterium.size;
    ss.ignore();

    bacterium.diseases.clear();
    string disease;
    getline(ss, diseases_str);
    stringstream ds(diseases_str);
    while(getline(ds, disease, ';')) {
        if(!disease.empty())
            bacterium.diseases.push_back(disease);
    }

    return is;
}

///THis is
ostream& operator<<(ostream& os, const Bacterium& bacterium) {
    os << bacterium.name << "," << bacterium.species << "," << bacterium.size;
    for(const auto& disease : bacterium.diseases) {
        os << ";" << disease;
    }
    return os;
}
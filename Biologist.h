#ifndef BIOLOGIST_H
#define BIOLOGIST_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Biologist {
private:
    string name;
    vector<string> species;  // Changed from biologists to species for clarity

public:
    Biologist() = default;  // Add default constructor
    Biologist(const string& name, const vector<string>& species)
        : name(name), species(species) {}

    const string& getName() const { return name; }
    void setName(const string& name) { this->name = name; }

    const vector<string>& getSpecies() const { return species; }
    void setSpecies(const vector<string>& species) { this->species = species; }

    // AdDIng stream operators
    friend istream& operator>>(istream& is, Biologist& biologist);
    friend ostream& operator<<(ostream& os, const Biologist& biologist);
};

#endif
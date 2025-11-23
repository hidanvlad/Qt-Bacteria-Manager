#include "Biologist.h"
#include <sstream>

//Constructor
istream& operator>>(istream& is, Biologist& biologist) {
    string line;
    getline(is, line);
    
    if(line.empty()) return is;
    
    stringstream ss(line);
    string species_str;
    
    getline(ss, biologist.name, ',');
    biologist.species.clear();
    
    string species;
    while(getline(ss, species, ';')) {
        if(!species.empty())
            biologist.species.push_back(species);
    }
    
    return is;
}

ostream& operator<<(ostream& os, const Biologist& biologist) {
    os << biologist.name;
    for(const auto& species : biologist.species) {
        os << ";" << species;
    }
    return os;
}
//
// Created by cddhi on 6/16/2025.
//

#ifndef BACTERIUM_H
#define BACTERIUM_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;


class Bacterium {
private:
  string name;
  string species;
  int size;
  vector<string> diseases; //vector cu diseases pentru toate bacteriile
public:
  Bacterium() = default;
  Bacterium(const string& name, const string& species, int size, const vector<string>& diseases)
      : name(name), species(species), size(size), diseases(diseases) {}

   //getter si setter for name
  const string& getName() const { return name; }
  void setName(const string& name) { this->name = name; }

  //getter and setert for species
  const string& getSpecies() const { return species; }
  void setSpecies(const string& species) { this->species = species; }

  //size..
  int getSize() const { return size; }
  void setSize(int size) { this->size = size; }

  //vector with diseases
  const vector<string>& getDiseases() const { return diseases; }
  void setDiseases(const vector<string>& diseases) { this->diseases = diseases; }
  void addDisease(const string& disease) { diseases.push_back(disease); }

  friend istream& operator>>(istream& is, Bacterium& bacterium);
  friend ostream& operator<<(ostream& os, const Bacterium& bacterium);


};



#endif //BACTERIUM_H

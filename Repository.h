#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "Bacterium.h"
#include "Biologist.h"

class Repository {
private:
  vector<Bacterium> bacterium_list;
  vector<Biologist> biologist_list;
  string biologists_file;
  string bacteriums_file;

public:
  Repository(const string& biologists_file = "../biologists.txt",
            const string& bacteriums_file = "../bacteriums.txt");

  void readBiologists();
  void readBacteriums();
  void saveBacteriums();

  vector<Bacterium> getBacteriums() const { return bacterium_list; }
  vector<Biologist> getBiologists() const { return biologist_list; }

  void addBacterium(const Bacterium& bacterium);
  void updateBacterium(const Bacterium& bacterium);
  Bacterium* findBacterium(const string& name, const string& species);
};

#endif


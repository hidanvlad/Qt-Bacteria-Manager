#include "Repository.h"
#include <stdexcept>

Repository::Repository(const string& biologists_file, const string& bacteriums_file)
    : biologists_file(biologists_file), bacteriums_file(bacteriums_file) {}

void Repository::readBiologists() {
    ifstream file(biologists_file);
    if (!file.is_open()) {
        throw runtime_error("Could not open biologists file");
    }

    biologist_list.clear();
    Biologist biologist;
    while (file >> biologist) {
        biologist_list.push_back(biologist);
    }
    file.close();
}

void Repository::readBacteriums() {
    ifstream file(bacteriums_file);
    if (!file.is_open()) {
        throw runtime_error("Could not open bacteriums file");
    }

    bacterium_list.clear();
    Bacterium bacterium;
    while (file >> bacterium) {
        bacterium_list.push_back(bacterium);
    }
    file.close();
}

void Repository::saveBacteriums() {
    ofstream file(bacteriums_file);
    if (!file.is_open()) {
        throw runtime_error("Could not open bacteriums file for writing");
    }

    for (const auto& bacterium : bacterium_list) {
        file << bacterium << "\n";
    }
    file.close();
}

void Repository::addBacterium(const Bacterium& bacterium) {
    if (findBacterium(bacterium.getName(), bacterium.getSpecies()) != nullptr) {
        throw runtime_error("Bacterium with same name and species already exists");
    }
    bacterium_list.push_back(bacterium);
}

void Repository::updateBacterium(const Bacterium& bacterium) {
    for (auto& b : bacterium_list) {
        if (b.getName() == bacterium.getName() && b.getSpecies() == bacterium.getSpecies()) {
            b = bacterium;
            return;
        }
    }
    throw runtime_error("Bacterium not found");
}

Bacterium* Repository::findBacterium(const string& name, const string& species) {
    for (auto& bacterium : bacterium_list) {
        if (bacterium.getName() == name && bacterium.getSpecies() == species) {
            return &bacterium;
        }
    }
    return nullptr;
}
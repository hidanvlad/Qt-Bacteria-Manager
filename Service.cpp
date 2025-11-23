#include "Service.h"

vector<Bacterium> Service::getBacteriaBySpecies(const string& species) const {
    vector<Bacterium> nameres;
    auto allBacteria = repository.getBacteriums();

    copy_if(allBacteria.begin(), allBacteria.end(), back_inserter(nameres),
            [&species](const Bacterium& b) { return b.getSpecies() == species; });

    sort(nameres.begin(), nameres.end(),
         [](const Bacterium& a, const Bacterium& b) { return a.getName() < b.getName(); });

    return nameres;
}

void Service::addBacterium(const Bacterium& bacterium) {
    if (repository.findBacterium(bacterium.getName(), bacterium.getSpecies()) != nullptr) {
        throw runtime_error("This bacteraium already exist!");
    }
    repository.addBacterium(bacterium);
}

void Service::updateBacterium(const Bacterium& bacterium) {
    repository.updateBacterium(bacterium);
}

void Service::addDiseaseToBacterium(const string& name, const string& species, const string& disease) {
    auto* bacterium = repository.findBacterium(name, species);
    if (bacterium == nullptr) {
        throw runtime_error("Bacterium not found");
    }
    
    auto diseases = bacterium->getDiseases();
    diseases.push_back(disease);
    bacterium->setDiseases(diseases);
}

vector<string> Service::getBiologistSpecies(const string& biologistName) const {
    for (const auto& biologist : repository.getBiologists()) {
        if (biologist.getName() == biologistName) {
            return biologist.getSpecies();
        }
    }
    return vector<string>();
}

Biologist Service::getBiologistByName(const string& name) const {
    for (const auto& biologist : repository.getBiologists()) {
        if (biologist.getName() == name) {
            return biologist;
        }
    }
    throw runtime_error("Biologist not found");
}
#ifndef SERVICE_H
#define SERVICE_H

#include "Bacterium.h"
#include "Biologist.h"
#include "Repository.h"
#include "Observer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class Service : public Subject {
private:
    Repository repository;
    vector<Observer*> observers;

public:
    Service() = default;
    explicit Service(Repository rep) : repository(rep) {
        repository.readBacteriums();
        repository.readBiologists();
    }


    void addObserver(Observer* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) override {
        observers.erase(
            remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notify() override {
        for (auto* obs : observers) {
            obs->update();
        }
    }

    // Bacteria operations
    vector<Bacterium> getBacteriaBySpecies(const string& species) const;
    void addBacterium(const Bacterium& bacterium);
    void updateBacterium(const Bacterium& bacterium);
    void addDiseaseToBacterium(const string& name, const string& species, const string& disease);

    // Biologist operations
    vector<Biologist> getAllBiologists() const { return repository.getBiologists(); }
    vector<string> getBiologistSpecies(const string& biologistName) const;
    Biologist getBiologistByName(const string& name) const;

    // File operations
    void saveToFile() {
        repository.saveBacteriums();
    }
};

#endif
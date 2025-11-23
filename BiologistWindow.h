#ifndef BIOLOGISTWINDOW_H
#define BIOLOGISTWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>


#include "Service.h"
#include "Observer.h"
#include "BacteriumTableModel.h"
#include "SpeciesVisualizer.h"

class BiologistWindow : public QMainWindow, public Observer {
    Q_OBJECT

private:
    Service& service;
    Biologist biologist;
    BacteriumTableModel* model;

    // GUI butoons/elems
    QTableView* tableView;
    QComboBox* speciesComboBox;
    QListWidget* diseaseList;
    QPushButton* addBacteriumButton;
    QPushButton* addDiseaseButton;
    QPushButton* viewButton;

    // Adding tyhe bacteriums
    QLineEdit* nameInput;
    QLineEdit* speciesInput;
    QLineEdit* sizeInput;
    QLineEdit* diseaseInput;

    void initializeGUI();
    void connectSignalsAndSlots();
    void populateSpeciesComboBox();  //populating the boxes
    void updateBacteriaList();       //upadting the list of bacterii
    void showAddBacteriumDialog();
    void handleBacteriumSelection();

public:
    BiologistWindow(Service& service, const Biologist& biologist);
    void update() override;
    ~BiologistWindow() override;

    private slots:
    void handleSpeciesFilter(const QString& species);
    void handleAddBacterium();
    void handleAddDisease();
    void handleViewSpecies();
};

#endif
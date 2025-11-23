#include "BiologistWindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <sstream>

BiologistWindow::BiologistWindow(Service& service, const Biologist& biologist)
    : service(service), biologist(biologist) {
    model = new BacteriumTableModel(this);
    service.addObserver(this);
    initializeGUI();
    connectSignalsAndSlots();
    populateSpeciesComboBox();
    updateBacteriaList();
    setWindowTitle(QString::fromStdString(biologist.getName()));
}

void BiologistWindow::initializeGUI() {
    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(centralWidget);

    // FILTU specii
    auto* filterLayout = new QHBoxLayout();
    speciesComboBox = new QComboBox();
    filterLayout->addWidget(new QLabel("Filter by species:"));
    filterLayout->addWidget(speciesComboBox);
    mainLayout->addLayout(filterLayout);

    ///Table bacteria
    tableView = new QTableView();
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(tableView);

    //list of disease
    diseaseList = new QListWidget();
    mainLayout->addWidget(new QLabel("Diseases:"));
    mainLayout->addWidget(diseaseList);

    // buttons
    auto* buttonLayout = new QHBoxLayout();
    addBacteriumButton = new QPushButton("Add Bacterium");
    addDiseaseButton = new QPushButton("Add Disease");
    viewButton = new QPushButton("View Species");
    buttonLayout->addWidget(addBacteriumButton);
    buttonLayout->addWidget(addDiseaseButton);
    buttonLayout->addWidget(viewButton);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
}


void BiologistWindow::connectSignalsAndSlots() {
    connect(speciesComboBox, &QComboBox::currentTextChanged, this, &BiologistWindow::handleSpeciesFilter);
     connect(addBacteriumButton, &QPushButton::clicked, this, &BiologistWindow::handleAddBacterium);
     connect(addDiseaseButton, &QPushButton::clicked, this, &BiologistWindow::handleAddDisease);
    connect(viewButton, &QPushButton::clicked, this, &BiologistWindow::handleViewSpecies);
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &BiologistWindow::handleBacteriumSelection);
}

void BiologistWindow::populateSpeciesComboBox() {
    speciesComboBox->clear();
     speciesComboBox->addItem("All");
     for (const auto& species : biologist.getSpecies()) {
        speciesComboBox->addItem(QString::fromStdString(species));
     }
}


void BiologistWindow::updateBacteriaList() {
    string selectedSpecies = speciesComboBox->currentText().toStdString();
    vector<Bacterium> bacteria;

    if (selectedSpecies == "All") {
        for (const auto& species : biologist.getSpecies()) {
            auto speciesBacteria = service.getBacteriaBySpecies(species);
            bacteria.insert(bacteria.end(), speciesBacteria.begin(), speciesBacteria.end());
        }
    } else {
        bacteria = service.getBacteriaBySpecies(selectedSpecies);
    }

    model->setBacteria(bacteria);
}

void BiologistWindow::update() {
    updateBacteriaList();
}

void BiologistWindow::handleSpeciesFilter(const QString& species) {
    updateBacteriaList();
}

void BiologistWindow::handleBacteriumSelection() {
    auto selection = tableView->selectionModel()->selectedRows();
      if (selection.empty()) return;

    int row = selection.first().row();
    const auto& bacteria = model->getBacteria();
    if (row >= 0 && row < bacteria.size()) {
        diseaseList->clear();
        for (const auto& disease : bacteria[row].getDiseases()) {
            diseaseList->addItem(QString::fromStdString(disease));
        }
    }
}

void BiologistWindow::handleAddBacterium() {
    QDialog dialog(this);
    auto* layout = new QFormLayout(&dialog);

    nameInput = new QLineEdit(&dialog);
    speciesInput = new QLineEdit(&dialog);
    sizeInput = new QLineEdit(&dialog);
    diseaseInput = new QLineEdit(&dialog);

    layout->addRow("Name:", nameInput);
    layout->addRow("Species:", speciesInput);
    layout->addRow("Size:", sizeInput);
    layout->addRow("Diseases (;-separated):", diseaseInput);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    // Set default values
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        try {
            vector<string> diseases;
            string diseasesStr = diseaseInput->text().toStdString();
            stringstream ss(diseasesStr);
            string disease;
            while (getline(ss, disease, ';')) {
                if (!disease.empty()) {
                    diseases.push_back(disease);
                }
            }

            Bacterium newBacterium(
                nameInput->text().toStdString(),
                speciesInput->text().toStdString(),
                sizeInput->text().toInt(),
                diseases
            );

            service.addBacterium(newBacterium);
            service.notify();
        } catch (const runtime_error& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void BiologistWindow::handleAddDisease() {
    auto selection = tableView->selectionModel()->selectedRows();
    if (selection.empty()) return;

    bool ok;
    QString disease = QInputDialog::getText(this, "Add Disease","Enter new disease:", QLineEdit::Normal,"", &ok);
    if (ok && !disease.isEmpty()) {
        int row = selection.first().row();
        const auto& bacteria = model->getBacteria();
        if (row >= 0 && row < bacteria.size()) {
            service.addDiseaseToBacterium(
                bacteria[row].getName(),
                bacteria[row].getSpecies(),
                disease.toStdString()
            );
            service.notify();
        }
    }
}

void BiologistWindow::handleViewSpecies() {
    auto* visualizer = new SpeciesVisualizer(service, biologist);
    visualizer->show();
}

BiologistWindow::~BiologistWindow() {
    service.removeObserver(this);
}
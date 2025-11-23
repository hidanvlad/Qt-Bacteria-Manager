#ifndef SPECIESVISUALIZER_H
#define SPECIESVISUALIZER_H

#include <QWidget>
#include "Service.h"
#include "Biologist.h"

class SpeciesVisualizer : public QWidget {
    Q_OBJECT

private:
    Service& service;
    Biologist biologist;

protected:
    void paintEvent(QPaintEvent* event) override;

public:
    SpeciesVisualizer(Service& service, const Biologist& biologist);
};

#endif
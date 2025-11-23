#include "SpeciesVisualizer.h"
#include <QPainter>

SpeciesVisualizer::SpeciesVisualizer(Service& service, const Biologist& biologist)
    : service(service), biologist(biologist) {
    setMinimumSize(600, 400);
    setWindowTitle("Species Visualization");
}

void SpeciesVisualizer::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    int y = 20;
    int shapeSize = 30;
    
    for (const auto& species : biologist.getSpecies()) {
        // draw the name
        painter.drawText(10, y, QString::fromStdString(species));
        y += 20;
        
        // Draw -> shape
        auto bacteria = service.getBacteriaBySpecies(species);
        int x = 10;
        for (const auto& bacterium : bacteria) {
            if (x + shapeSize > width()) {
                x = 10;
                y += shapeSize + 10;
            }
            
            // Alternating between circle and rectangle
            if (x % (shapeSize * 2) == 0) {
                painter.drawEllipse(x, y, shapeSize, shapeSize);
            } else {
                painter.drawRect(x, y, shapeSize, shapeSize);
            }
            x += shapeSize + 10;
        }
        y += shapeSize + 30;
    }
}
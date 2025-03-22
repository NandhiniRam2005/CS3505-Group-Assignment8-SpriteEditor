#include "layerbutton.h"


LayerButton::LayerButton(int givenLayerNumber, QWidget *parent) : QPushButton(parent), layerNumber(givenLayerNumber) {
    QString buttonText = "Layer " + QString::number(layerNumber);
    setText(buttonText);
}



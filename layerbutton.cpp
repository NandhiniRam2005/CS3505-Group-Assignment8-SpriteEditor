/*
* Checked by Joel Rodriguez
The cpp file for Layer Button.

This class represents a button associated with a specific layer number.
It also implemenyts methods for getting and setting a layer number.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "layerbutton.h"

LayerButton::LayerButton(int givenLayerNumber, QWidget *parent) : QPushButton(parent), layerNumber(givenLayerNumber) {
    QString buttonText = "Layer " + QString::number(layerNumber);
    setText(buttonText);
}

LayerButton::LayerButton(QWidget *parent) : QPushButton(parent){
    this->layerNumber = 1;
    QString buttonText = "Layer " + QString::number(layerNumber);
    setText(buttonText);
}

int LayerButton::getLayerNumber() const{
    return this->layerNumber;
}

void LayerButton::setLayerNumber(int newLayerNumber){
    this->layerNumber = newLayerNumber;
}


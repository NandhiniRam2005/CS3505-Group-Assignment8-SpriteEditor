#ifndef LAYERBUTTON_H
#define LAYERBUTTON_H

#include <QPushButton>

class LayerButton : public QPushButton
{
public:
    explicit LayerButton(int givenLayerNumber, QWidget *parent = nullptr) : QPushButton(parent), layerNumber(givenLayerNumber) {
        QString buttonText = "Layer " + QString::number(layerNumber);
        setText(buttonText);
    }

private:
    int layerNumber;
};

#endif // LAYERBUTTON_H

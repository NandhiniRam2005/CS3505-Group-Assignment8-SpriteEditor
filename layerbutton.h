#ifndef LAYERBUTTON_H
#define LAYERBUTTON_H

#include <QPushButton>

class LayerButton : public QPushButton
{
public:
    explicit LayerButton(int givenLayerNumber, QWidget *parent);

private:
    int layerNumber;
};

#endif // LAYERBUTTON_H

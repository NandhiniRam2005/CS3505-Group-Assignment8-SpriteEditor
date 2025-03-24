#ifndef LAYERBUTTON_H
#define LAYERBUTTON_H

#include <QPushButton>

class LayerButton : public QPushButton
{
    Q_OBJECT

public:
    explicit LayerButton(int givenLayerNumber, QWidget *parent);
    int getLayerNumber() const;
    void setLayerNumber(int newLayerNumber);

private:
    int layerNumber;
};

#endif // LAYERBUTTON_H

/*
The header file for Layer Button.

This class represents a button associated with a specific layer number.
It also provides functionality for getting and setting a layer number.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef LAYERBUTTON_H
#define LAYERBUTTON_H

#include <QPushButton>

class LayerButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * Constructs a LayerButton with a specified layer number
     * @param givenLayerNumber - layer number associated with this button
     * @param parent - parent widget of this button
     */
    explicit LayerButton(int givenLayerNumber, QWidget *parent);

    /**
     * Constructs a LayerButton with a default layer number.
     * @param parent - parent widget of this button.
     */
    LayerButton(QWidget *parent);

    /**
     * Gets the layer number of this button.
     * @return layer number of the button.
     */
    int getLayerNumber() const;

    /**
     * Sets the layer number for this button.
     * @param newLayerNumber - new layer number to assign.
     */
    void setLayerNumber(int newLayerNumber);

private:
    /**
     * layer number associated with this button
     */
    int layerNumber;
};

#endif

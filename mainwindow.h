/*
The header file for mainwindow.

A class which represents represents the main window of the application.
It is the view to the program (MVC).

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainmodel.h"
#include "layerbutton.h"
#include "mouselistener.h"
#include <QMainWindow>
#include <QPoint>
#include <QPushButton>
#include <QSlider>
#include <QToolBar>
#include <pixel.h>
#include <pixeldisplay.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructor that Initializes the MainWindow with an optional parent widget
     * @param parent - parent widget (default is nullptr)
     */
    MainWindow(MainModel *model, QWidget *parent = nullptr);

    /**
     * Destructor for the mainwindow class.
     */
    ~MainWindow();

public slots:
    /**
     * Slot to update the display color when the color changes
     * @param pixel - The pixel with the new color
     */
    void displayColorChange(Pixel pixel);

    /**
     * Slot to update the load status on the UI
     * @param status - The loading status
     */
    void displayLoadStatus(bool status);

    /**
     * Slot to update the save status on the UI
     * @param status - saving status
     */
    void displaySaveStatus(bool status);

    void openColorDialogue();

    void setFrameCopyVariable();

    void addFrameHelper();

    void deleteFrameHelper();

    void setToolToBrush();

    void setToolToBucket();

    void setToolToEraser();

    void setToolToEyeDropper();

    void onLayerButtonClicked(int layerNumber);

    void setBrushSize(int sizeOption);

    void updateGridSize(unsigned int gridSize);

    void changeGridSize(int sizeOption);

    void addLayerButton();

    void deleteLayerButton();

    void mapClickLocationToGridCoordinate(QPoint p);

    void handleMouseDrag(QPoint screenPoint);

    void openFileChooserLoad();

    void openFileChooserSave();

    void updateNumberOfLayerButtons(int numberOfLayerButtons);

    void updateNumberOfFrames(int numberOfFrames);

    void syncResizeComboBox(unsigned int gridSize);

signals:
    /**
     * Signal to load file
     * @param filepath - filepath to load from
     */
    void loadFile(QString filepath);

    /**
     * Signal to save file
     * @param filepath - filepath to save from
     */
    void saveFile(QString filepath);

    /**
     * Signal to go to the previous frame
     */
    void previousFrame();

    /**
     * Signal to go to the next frame
     */
    void nextFrame();

    /**
     * Signal to go to add a frame to the model
     */
    void addFrame(bool copyPrevious);

    /**
     * Signal to go to delete a frame
     */
    void deleteFrame();

    /**
     * Signal for chnaging the current layer
     * @param layerNumber - number/index of the layer to change
     */
    void changeLayer(int layerNumber);

    /**
     * Signal to add a layer in the model.
     */
    void addLayer();

    /**
     * Signal to delete a layer in the model at a certain index.
     * @param layerIndex - the index at which the layer lives at, for example layer at index one is
     *                    the bottom most layer
     */
    void deleteLayer(int layerIndex);

    /**
     * Signal to change the size of the brush in the model.
     *
     * @param brushSize - the new brush size in pixel coordinates
     */
    void changeBrushSize(unsigned int brushSize);

    /**
     * Signal to change the fps at which the animation frame show images in the model
     *
     * @param fps - the new fps
     */
    void changeFps(unsigned int fps);

    /**
     * Signals to the model that a new color has been chosen. Color is represented by pixels.
     *
     * @param color - The new color aquired from the view
     */
    void changeColor(Pixel color);

    /**
     * Signal that is able to send the current hover position of the mouse in widget coordinates
     *
     * @param x - The current x widget coordinate
     * @param y - The current y widget coordinate
     */
    void mouseHoverLocation(unsigned int x, unsigned int y);

    /**
     * Signal to the model that the image should be reflected vertically
     */
    void reflectVertical();

    /**
     * Signal to the model that the image should be reflected horizontally
     */
    void reflectHorizontal();

    /**
     * Signal to the model that the image should be rotated 90 degrees clockwise
     */
    void rotate90();

    /**
     * Alerts the model to return the current grid size in pixel coordinates.
     */
    void askGridSize();

    /**
     * Singals that the canvas has changed in size (8x8, 16x16, 32x32, or 64x64)
     *
     * @param newSize - The new size of the canvas
     */
    void resize(unsigned int newSize);

    /**
     * Signals that a pixel (in pixels coords) has been clicked.
     *
     * @param xCoord - The x coordinate that was clicked on.
     * @param yCoord - The y coordinate that was clicked on.
     */
    void pixelClicked(unsigned int xCoord, unsigned int yCoord);

    /**
     * Singals that a new tool has been selected.
     *
     * @param newTool - A tool enum which represents either an eyedropper, paintbucket, brush, or eraser.
     */
    void toolSelected(Tool newTool);

private:
    MouseListener mouseListener;
    PixelDisplay mainDrawing;
    PixelDisplay animationDisplay;
    PixelDisplay frameDisplay;
    QToolBar saveLoadBar;
    QPushButton brushButton;
    QPushButton paintBucketButton;
    QPushButton eraserButton;
    QPushButton colorButton;
    QPushButton refelectVerticalButton;
    QPushButton refelectHorizontalButton;
    QPushButton rotateButton;
    QPushButton* layerOne;
    QSlider fpsSlider;
    unsigned int width;
    unsigned int height;
    bool frameBeingCopied;
    unsigned int brushSize;
    unsigned int currentGridSize;
    int currentIndexOfLayerButtons;
    int numberOfLayerButtons;
    int numberOfFrameButtonClicks;
    bool deleteLayerDisabled;
    bool deleteFrameDisabled;
    QVector<LayerButton*> layerButtons;
    LayerButton* selectedLayerButton;
    LayerButton* previouslySelected;
    Ui::MainWindow *ui;
};

#endif

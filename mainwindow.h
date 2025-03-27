/*
The header file for mainwindow.

A class which represents represents the main window of the application.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 21, 2025
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QPushButton>
#include <QSlider>
#include <QToolBar>
#include "mainmodel.h"
#include "layerbutton.h"
#include "mouselistener.h"
#include <pixel.h>
#include <pixeldisplay.h>
#include <QColorDialog>

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

    // void displayLayerButtonSelection();

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
     * Signal to go to add a frame
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

    void addLayer();
    void deleteLayer(int layerIndex);
    void changeBrushSize(unsigned int brushSize);
    void changeFps(unsigned int fps);
    void changeColor(Pixel p);
    void mouseHoverLocation(unsigned int x, unsigned int y);
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();
    void askGridSize();
    void resize(unsigned int newSize);
    void pixelClicked(unsigned int xCoord, unsigned int yCoord);
    void toolSelected(Tool newTool);
    // void selectedLayerChanged();

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
    QSlider brushSizeSlider; // DO WE WANT A SLIDER FOR BRUSH SIZE????!!!!!
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
#endif // MAINWINDOW_H

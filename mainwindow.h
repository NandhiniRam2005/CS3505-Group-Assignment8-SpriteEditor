/*
 * Checked by Joseph Hamilton

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

    /**
     * Opens a color dialogue to display to the user.
     */
    void openColorDialogue();

    /**
     * Setter method for the frame copy variable, Alternates so this method will turn
     * from true to false and vice versa.
     */
    void setFrameCopyVariable();

    /**
     * Helper method for adding a frame to the model, this helper method is required as
     * the view needs to validate information such as the current state of the view
     * before sending information to the model.
     */
    void addFrameHelper();

    /**
     * Helper method for deleting a frame from the model, this helper method is required as
     * the view needs to validate information such as the current state of the view.
     * Our view practices some client-side validation in addition to server-side
     * validation. This method does that as well.
     */
    void deleteFrameHelper();

    /**
     * Sets the currently selected tool to a brush
     */
    void setToolToBrush();

    /**
     * Sets the currently selected tool to a bucket
     */
    void setToolToBucket();

    /**
     * Sets the currently selected tool to an eraser
     */
    void setToolToEraser();

    /**
     * Sets the currently selected tool to an eyedropper
     */
    void setToolToEyeDropper();

    /**
     * What should occur when a LayerButton has been clicked. This method emits a signal to the
     * model alerting of a layer change.
     *
     * @param layerNumber - The layer that should be switched too
     */
    void onLayerButtonClicked(int layerNumber);

    /**
     * Sets the current size of the brush
     *
     * @param sizeOption - The size option that was selected.
     */
    void setBrushSize(int sizeOption);

    /**
     * Updates the currently selecyed grid size variable. E.g.. 8x8 -> 32x32
     *
     * @param gridSize - The newly selected grid size.
     */
    void updateGridSize(unsigned int gridSize);

    /**
     * Does all visual work when a grid size has been updated such as updating the combo box
     *
     * @param sizeOption - The given grid size that was sent via the params.
     */
    void changeGridSize(int sizeOption);

    /**
     * Adds a layerbutton to the view and does all necessary connections.
     */
    void addLayerButton();

    /**
     * Deletes a layerbutton from the view and does all necessary memory handling.
     */
    void deleteLayerButton();

    /**
     * Takes coordinates that were in widget coordinates and converts them to pixel/grid coordinates
     *
     * @param p - the point in widget coordinates.
     */
    void mapClickLocationToGridCoordinate(QPoint p);

    /**
     * Handles all view related logic for when the mouse is dragged.
     *
     * @param widgetPoint - The point in which the mouse was dragged in widget coords.
     */
    void handleMouseDrag(QPoint widgetPoint);

    /**
     * Opens a file chooser dialouge in the event of a load.
     */
    void openFileChooserLoad();

    /**
     * Opens a file chooser dialouge in the event of a save.
     */
    void openFileChooserSave();

    /**
     * Updates the number of layerButtons that are present whenever next frame, previous frame, delete frame
     * and load are pressed.
     *
     * @param - The new number of layer buttons that should be present.
     */
    void updateNumberOfLayerButtons(int numberOfLayerButtons);

    /**
     * Updates the number of frames that are present.
     *
     * @param numberOfFrames - The new number of frames
     */
    void updateNumberOfFrames(int numberOfFrames);

    /**
     * Syncs the combo box with the model when necessary.
     *
     * @param gridSize - The current gridsize aquired from the model.
     */
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
    void resizeCanvas(unsigned int newSize);

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
    /**
     * MouseListener object functions as way to listen to where the mouse is in respect
     * to the widget.
     */
    MouseListener mouseListener;

    /**
     * The mainDrawing is the canvas for drawing on.
     */
    PixelDisplay mainDrawing;
    /**
     * The animation display is where the animation of all frames are shown.
     */
    PixelDisplay animationDisplay;

    /**
     * The frame display is where the current frame is shown.
     */
    PixelDisplay frameDisplay;

    /**
     * The save load bar is used for saving/loading purposes.
     */
    QToolBar saveLoadBar;

    /**
     * Button for switching to the brush tool.
     */
    QPushButton brushButton;

    /**
     * Button for switching to the paint bucket tool.
     */
    QPushButton paintBucketButton;

    /**
     * Button for switching to the eraser tool.
     */
    QPushButton eraserButton;

    /**
     * Button for switching colors.
     */
    QPushButton colorButton;

    /**
     * Button for doing a reflect vertical transformation.
     */
    QPushButton refelectVerticalButton;

    /**
     * Button for doing a reflect horizontal transformation.
     */
    QPushButton refelectHorizontalButton;

    /**
     * Button for doing a 90 degree clockwise transformation.
     */
    QPushButton rotateButton;

    /**
     * Pointer to the first layer button which is always present on intialization.
     */
    QPushButton* layerOne;

    /**
     * The fpsSlider for changing the fps of the animationDisplay.
     */
    QSlider fpsSlider;

    /**
     * Width of the widget.
     */
    unsigned int width;

    /**
     * Height of the widget.
     */
    unsigned int height;

    /**
     * Bool which represents whether the "CopyFrame?" radio button is clicked.
     */
    bool frameBeingCopied;

    /**
     * Current brush size selected in the view.
     */
    unsigned int brushSize;

    /**
     * Current grid size selected in the view.
     */
    unsigned int currentGridSize;

    /**
     * Current number of layer buttons displayed by the view.
     */
    int numberOfLayerButtons;

    /**
     * Current number of frame buttons displayed on the view.
     */
    int numberOfFrameButtonClicks;

    /**
     * Bool which represents whether the user should be allowed to delete a layer.
     */
    bool deleteLayerDisabled;

    /**
     * Bool which represents whether the user should be allowed to delete a frame.
     */
    bool deleteFrameDisabled;

    /**
     * Collection of all layer buttons, required for memory managment.
     */
    QVector<LayerButton*> layerButtons;

    /**
     * Currently selected layer button, required for memory managment.
     */
    LayerButton* selectedLayerButton;

    /**
     * The ui of the main window.
     */
    Ui::MainWindow *ui;
};

#endif

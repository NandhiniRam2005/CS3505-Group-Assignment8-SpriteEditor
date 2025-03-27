/*
The header file for mainmodel.

A class which represents the model for the sprite editor. It manages frames, layers,
brush size, animation speed, and pixel manipulations. The model sends updated pixel grids to
the display through signals and handles user interactions with frames and layers.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 21, 2025
*/

#ifndef MAINMODEL_H
#define MAINMODEL_H
#include <QObject>
#include <QVector>
#include <QString>
#include <QObject>
#include <QTimer>

#include "frame.h"
#include "pixel.h"

/*
 * Enumeration of all tools in the GUi.
 */
enum class Tool {
    Brush,
    PaintBucket,
    Eraser,
    EyeDropper,
    None
};

class MainModel : public QObject
{
    Q_OBJECT
public:

    /**
     * custom constructor for MainModel class.
     * Initializes the model with default values and parent object.
     * @param parent - parent QObject with default nullptr.
     */
    explicit MainModel(QObject *parent = nullptr);

signals:
    /**
     * Signal emitted when a new animation frame is available.
     * @param pixelGrid - Pointer to the new pixel grid of the animation frame.
     */
    void newAnimationFrame(const Pixel* pixelGrid);

    void newFrameImage(const Pixel* pixelGrid);

    /**
     * Signal emitted when a new display image is available.
     * @param pixelGrid - Pointer to the new pixel grid for display.
     */
    void newDisplayImage(const Pixel* pixelGrid);

    /**
     * Signal emitted when a new preview of the selected frame is available.
     * @param pixelGrid - Pointer to the new pixel grid for the selected frame preview.
     */
    void newSelectedFramePreview(const Pixel* pixelGrid);

    /**
     * Signal emitted when a new color is selected.
     * @param color - new selected color.
     */
    void newSelectedColor(Pixel color);


    /**
     * Signal emitted to indicate the whether loading was successful or not.
     * @param status - True if loading was successful, false otherwise.
     */
    void loadJSONStatus(bool status);

    /**
     * Signal emitted to indicate the whether saving was successful or not.
     * @param status - True if saving was successful, false otherwise.
     */
    void saveJSONStatus(bool status);

    void gridSizeUpdated(unsigned int gridSize);

public slots:
    /**
     * Loads a JSON file containing canvas' data.
     * @param filepath - path to the JSON file to load.
     */
   void loadJSON(const QString& filepath);

    /**
     * Saves the current canvas' data to a JSON file.
     * @param filepath - path to the JSON file where data will be saved.
     */
   void saveJSON(const QString& filepath);

    /**
     * Resizes the grid size for all frames.
     * @param newSize The new size for the grid.
     */
    void resize(unsigned int newSize);

    /**
     * Switches to the previous frame and updates the display.
     */
    void previousFrame();

    /**
     * Switches to the next frame and updates the display.
     */
    void nextFrame();

    /**
     * Adds a new frame. Also copies the previous frame’s data for duplication if wanted.
     * @param copyPrevious - if true, the previous frame is copied, otherwise, a new empty frame is added.
     */
    void addFrame(bool copyPrevious);

    /**
     * Deletes the current frame.
     * @throws run time error if this is the only frame.
     */
    void deleteFrame();

    /**
     * Changes the active layer in the selected frame.
     * @param layer - index of the new active layer.
     * @throws run time error if the layer index is invalid.
     */
    void changeLayer(unsigned int layer);

    /**
     * Adds a new layer to the selected frame.
     */
    void addLayer();

    /**
     * Deletes the active layer in the selected frame.
     */
    void deleteLayer(int layerIndex);

    /**
     * Changes the size of the brush used for painting and erasing.
     * @param newBrushSize - new brush size.
     */
    void changeBrushSize(unsigned int newBrushSize);


    /**
     * Changes the frames per second for the animation.
     * @param newFPS - new FPS value.
     */
    void changeAnimationFPS(unsigned int newFPS);

    /**
     * Changes the currently selected color.
     * @param newColor - new selected color.
     */
    void changeSelectedColor(Pixel newColor);

    /**
     * Updates the coordinates of the mouse hover position.
     * @param xCoord - new x-coordinate of the mouse.
     * @param yCoord - new y-coordinate of the mouse.
     */
    void mouseHovered(unsigned int xCoord, unsigned int yCoord);

    /**
     * Updates the currently selected Tool to a new Tool.
     * @param newTool the new Tool to select
     */
    void selectTool(Tool newTool);

    /**
     * Updates the model's state by drawing pixels or changing the selected color,
     * based on the currently selected tool.
     * @param xCoord The x coordinate of the pixel that was clicked
     * @param yCoord The y coordinate of the pixel that was clicked
     */
    void pixelClicked(unsigned int xCoord, unsigned int yCoord);

    /**
     * Reflects the selected frame vertically.
     */
    void reflectVertical();

    /**
     * Reflects the selected frame horizontally.
     */
    void reflectHorizontal();

    /**
     * Rotates the selected frame by 90 degrees clockwise.
     */
    void rotate90();

    void getGridSize();

    void mouseLeft();

private:
    /**
     * Sends the current display image to the display.
     */
    void sendDisplayImage();

    /**
     * Sends the next animation frame image to the animation preview.
     */
    void sendAnimationFrame();

    /**
     * Paints pixels on the selected frame at the specified location.
     * @param topLeftX - x-coordinate of the top-left corner of the region to paint.
     * @param topLeftY - y-coordinate of the top-left corner of the region to paint.
     */
    void paintPixels(unsigned int topLeftX, unsigned int topLeftY);

    /**
     * Erases pixels on the selected frame at the specified location.
     * @param topLeftX - x-coordinate of the top-left corner of the region to erase.
     * @param topLeftY - y-coordinate of the top-left corner of the region to erase.
     */
    void erasePixels(unsigned int topLeftX, unsigned int topLeftY);

    /**
     * Fills a region with the selected color using the bucket fill tool.
     * @param topLeftX - x-coordinate of the region to start filling.
     * @param topLeftY - y-coordinate of the region to start filling.
     */
    void bucketFill(unsigned int topLeftX, unsigned int topLeftY);

    /**
     * Sets the selected color to the color of a pixel at the specified coordinates.
     * @param x - x-coordinate of the pixel.
     * @param y - y-coordinate of the pixel.
     */
    void setSelectedColorToPixel(unsigned int x, unsigned int y);

    /**
     * The currently selected tool
     */
    Tool currentTool;

    /**
     * vector collection of frames in the animation.
     */
    QVector<Frame> frames;

    /**
     * index of the currently selected frame
     */
    qsizetype selectedFrame;

    /**
     * current brish size for painting and erasing
     */
    int brushSize;

    /**
     * frames per second of the animation
     */
    unsigned int animationFPS;

    /**
     * the timer for the animation preview
     */
    QTimer *animationTimer;

    /**
     * the current frame of the animation preview
     */
    unsigned int currentAnimationFrame;

    /**
     * currently selected color for painting
     */
    Pixel selectedColor;

    /**
     * size of the grid (square - width and height)
     */
    unsigned int gridSize;

    /**
     * x coordinate of the mouse position currently
     */
    int currentMouseX = -1;

    /**
     * y coordinate of the mouse position currently
     */
    int currentMouseY = -1;

};

#endif // MAINMODEL_H

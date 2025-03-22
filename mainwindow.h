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
#include <pixeldisplay.h>
#include <pixel.h>
#include <QToolBar>
#include <QPushButton>
#include <QPoint>
#include <QSlider>

/*
 * Enumeration of all tools in the GUi.
 */
enum Tool {
    Brush,
    PaintBucket,
    Eraser,
    Eyedropper,
};

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
    MainWindow(QWidget *parent = nullptr);

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
    void addFrame();

    /**
     * Signal to go to delete a frame
     */
    void deleteFrame();

    /**
     * Signal for chnaging the current layer
     * @param layerNumber - number/index of the layer to change
     */
    void changeLayer(unsigned int layerNumber);

    void addLayer();
    void deleteLayer();
    void changeBrushSize(unsigned int brushSize);
    void changeFps(unsigned int fps);
    void changeColor(Pixel p);
    void mouseHoverLocation(unsigned int x, unsigned int y);
    void paintPixels(unsigned int topLeftX, unsigned int topLeftY);
    void erasePixels(unsigned int topLeftX, unsigned int topLeftY);
    void bucketFill(unsigned int topLeftX, unsigned int topLeftY);
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();
    void setSelectedColortoPixel(unsigned int x, unsigned int y);

private:
    QWidget mouseListener;
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
    QSlider fpsSlider;
    Tool selectedTool;
    unsigned int width;
    unsigned int height;

    QPoint mapClickLocationToGridCoordinate(unsigned int x, unsigned int y);

    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H



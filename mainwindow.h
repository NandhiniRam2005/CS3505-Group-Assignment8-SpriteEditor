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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void displayColorChange(Pixel p);
    void displayLoadStatus(bool status);
    void displaySaveStatus(bool status);


signals:
    void loadFile(QString filepath);
    void saveFile(QString filepath);
    void previousFrame();
    void nextFrame();
    void addFrame();
    void deleteFrame();
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



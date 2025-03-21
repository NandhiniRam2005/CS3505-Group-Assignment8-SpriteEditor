#ifndef MAINMODEL_H
#define MAINMODEL_H
#include <QObject>
#include <QVector>
#include <QString>
#include <QObject>

#include "frame.h"
#include "pixel.h"

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr);

signals:
    Pixel* newAnimationFrame();
    Pixel* newDisplayImage();
    Pixel* newSelectedFramePreview();
    Pixel newSelectedColor();
    bool loadJSONStatus();
    bool saveJSONStatus();

public slots:
    void loadJSON(QString& filepath);
    void saveJSON(QString& filepath);
    void resize(unsigned int newSize);

    void previousFrame();
    void nextFrame();
    void addFrame(bool copyPrevious);
    void deleteFrame();
    void changeLayer(unsigned int layer);
    void addLayer();
    void deleteLayer();
    void changeBrushSize(unsigned int newBrushSize);
    void changeAnimationFPS(unsigned int newFPS);
    void changeSelectedColor(Pixel newColor);
    void mouseHovered(unsigned int xCoord, unsigned int yCoord);

    void paintPixels(unsigned int topLeftX, unsigned int topLeftY);
    void erasePixels(unsigned int topLeftX, unsigned int topLeftY);
    void bucketFill(unsigned int topLeftX, unsigned int topLeftY);
    void reflectVertical();
    void reflectHorizontal();
    void rotate90();
    void setSelectedColorToPixel(unsigned int x, unsigned int y);

private:
    QVector<Frame> frames;
    qsizetype selectedFrame;
    unsigned int brushSize;
    unsigned int animationFPS;
    Pixel selectedColor;
    unsigned int gridSize;
    unsigned int currentMouseX;
    unsigned int currentMouseY;
};

#endif // MAINMODEL_H

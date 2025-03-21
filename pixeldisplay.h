#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include <QWidget>

class PixelDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit PixelDisplay(QWidget *parent = nullptr);

signals:
};

#endif // PIXELDISPLAY_H

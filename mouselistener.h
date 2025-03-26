#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <QWidget>
#include <QMouseEvent>

class MouseListener : public QWidget
{
    Q_OBJECT
public:
    explicit MouseListener(QWidget *parent = nullptr);

signals:
    void mouseClicked(QPoint p);
    void mouseMoved(QPoint screenCoords);
    void mouseReleased();

private:
    bool isMousePressed = false;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

};

#endif // MOUSELISTENER_H

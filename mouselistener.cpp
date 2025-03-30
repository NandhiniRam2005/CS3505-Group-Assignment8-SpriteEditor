#include "mouselistener.h"

MouseListener::MouseListener(QWidget *parent): QWidget{parent}
{
    setMouseTracking(true);
}

void MouseListener::mousePressEvent(QMouseEvent* event){
    QPoint screenCoords = event->pos();
    emit mouseClicked(screenCoords);
    isMousePressed = true;
}

void MouseListener::mouseMoveEvent(QMouseEvent* event) {
    QPoint screenCoords = event->pos();
    emit mouseMoved(screenCoords);
}

void MouseListener::mouseReleaseEvent(QMouseEvent* event) {
    isMousePressed = false;
    emit mouseReleased();
}

void MouseListener::leaveEvent(QEvent *event)
{
    emit mouseLeft();
    QWidget::leaveEvent(event);
}

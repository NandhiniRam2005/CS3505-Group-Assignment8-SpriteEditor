#include "mouselistener.h"

MouseListener::MouseListener(QWidget *parent)
    : QWidget{parent}
{}

void MouseListener::mousePressEvent(QMouseEvent* event){
    QPoint screenCoords = event->pos();
    emit mouseClicked(screenCoords);
    isMousePressed = true;
}

void MouseListener::mouseMoveEvent(QMouseEvent* event) {
    if (isMousePressed) {
        QPoint screenCoords = event->pos();
        emit mouseMoved(screenCoords);
    }
}

void MouseListener::mouseReleaseEvent(QMouseEvent* event) {
    isMousePressed = false;
    emit mouseReleased();
}

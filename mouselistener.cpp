#include "mouselistener.h"

MouseListener::MouseListener(QWidget *parent)
    : QWidget{parent}
{}

void MouseListener::mousePressEvent(QMouseEvent* event){
    QPoint screenCoords = event->pos();
    emit mouseClicked(screenCoords);
}

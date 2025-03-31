/*
* Checked by Joel Rodriguez and Jake Heairld
The cpp file for mouseListener.

This class implements methods to handle mouse interactions, including clicks, movement,
release, and when the mouse leaves the widget area.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "mouselistener.h"

MouseListener::MouseListener(QWidget *parent): QWidget{parent} {
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

void MouseListener::leaveEvent(QEvent *event) {
    emit mouseLeft();
    QWidget::leaveEvent(event);
}

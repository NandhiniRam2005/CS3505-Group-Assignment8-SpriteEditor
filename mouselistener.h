/*
The header file for mouseListener.

This class handles mouse interactions, including clicks, movement,
release, and when the mouse leaves the widget area.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <QWidget>
#include <QMouseEvent>

class MouseListener : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructs a MouseListener object.
     * @param parent - parent widget
     */
    explicit MouseListener(QWidget *parent = nullptr);

signals:
    /**
     * Signal emitted when the mouse is clicked.
     * @param point - The point where the mouse click occured.
     */
    void mouseClicked(QPoint point);

    /**
     * Signal emitted when the mouse is moved.
     * @param screenCoords - the Point where the mouse is on the screen.
     */
    void mouseMoved(QPoint screenCoords);

    /**
     * Signal emitted when the mouse button is released.
     */
    void mouseReleased();

    /**
     * Signal emitted when the mouse leaves the widget area.
     */
    void mouseLeft();

private:
    /**
     * Tracks whether the mouse is currently pressed.
     */
    bool isMousePressed = false;

    /**
     * Handles mouse press events.
     * @param event - QMouseEvent describing the the press event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Handles mouse move events.
     * @param event - QMouseEvent describing the movement.
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * Handles mouse release events.
     * @param event - QMouseEvent describing the release.
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * Handles the event when the mouse leaves the widget area.
     * @param event - QEvent when the mouse leaves the widget.
     */
    void leaveEvent(QEvent *event) override;
};

#endif

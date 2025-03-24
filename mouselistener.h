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

private:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // MOUSELISTENER_H

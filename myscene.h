#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "constants.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = nullptr);
    void set_color(QColor c);
    void set_primitive(Primitives p);
    void set_border_color(QColor c);
    void set_border_width(int width);

signals:
    void mouse_moved(double x, double y);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//     void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//     void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
     void keyPressEvent(QKeyEvent *event);

private:
     Primitives _current_primitive;
     QColor _fill_color;
     int _border_width;
     QColor _border_color;
     QGraphicsItem *_current_item;
     QPointF _start_pos;

     // QGraphicsScene interface

};

#endif // MYSCENE_H

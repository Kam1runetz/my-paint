#include "myscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
  , _fill_color(Qt::white)
  ,_border_width(1)
  ,_border_color(Qt::white)
  ,_current_item(nullptr)
  ,_start_pos()
{
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_current_item) {
        switch (_current_item->type()) {
        case QGraphicsRectItem::Type:
        {
          QGraphicsRectItem *rect_item = (QGraphicsRectItem *) _current_item;

          QPointF p1 = _start_pos;
          QPointF p2 = event->scenePos();

          QRectF new_rect(QPointF(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y())),
                          QPointF(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y())));


          rect_item->setRect(new_rect);
          break;
        }

        case QGraphicsEllipseItem::Type:
        {
          QGraphicsEllipseItem *ellipse = (QGraphicsEllipseItem *) _current_item;

          QRectF rect = ellipse->rect();
          rect.setBottomRight(event->scenePos());

          ellipse->setRect(rect);
          break;
        }

        default:
          break;
        }
        return;
      }
      QGraphicsScene::mouseMoveEvent(event);
//    emit mouse_moved(event->scenePos().x(), event->scenePos().y());
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (_current_primitive!= none) {
      if (event->button() == Qt::LeftButton) {
        if (_current_item == nullptr) {
          _start_pos = event->scenePos();
          switch (_current_primitive) {
          case rectangle:
          {
            QGraphicsRectItem *item = new QGraphicsRectItem(
                                        event->scenePos().x(),
                                        event->scenePos().y(),
                                        0,
                                        0);
            item->setBrush(_fill_color);

            QPen p(_border_color);
            p.setWidth(_border_width);
            item->setPen(p);

            addItem(item);
            _current_item = item;
            break;
          }

          case ellipse:
          {
            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(
                                           event->scenePos().x(),
                                           event->scenePos().y(),
                                           0,
                                           0);
            item->setBrush(_fill_color);
            QPen p(_border_color);
            p.setWidth(_border_width);
            item->setPen(p);

            addItem(item);
            _current_item = item;        
            break;
          }

          default:
            break;
          }
         if (_current_item) _current_item->setFlag(QGraphicsItem::ItemIsSelectable);
         if (_current_item) _current_item->setFlag(QGraphicsItem::ItemIsMovable);
        }
      } else if (event->button() == Qt::RightButton) {
        if (_current_item) {
          delete _current_item;
          _current_item = nullptr;
        }
      }
      return;
  }
  QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if (_current_item) {
    _current_item = nullptr;
  }
  QGraphicsScene::mouseReleaseEvent(event);
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        for (auto & item : this->selectedItems())
            if (item) delete item;
    } else if (event->key() == Qt::Key_Q) {
        for (auto & item : this->selectedItems()) {
            if (item) item->setZValue(item->zValue() + 1);
        }
    } else if (event->key() == Qt::Key_Escape) {
        if (_current_item) delete _current_item;
        _current_item = nullptr;
    }
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsScene::mouseDoubleClickEvent(event);
}

void MyScene::set_primitive(Primitives p)
{
    _current_primitive = p;
}

void MyScene::set_border_color(QColor c)
{
    _border_color = c;
}

void MyScene::set_border_width(int width)
{
   _border_width = width;
}

void MyScene::set_color(QColor c)
{
  _fill_color = c;
}

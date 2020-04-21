#include "scene.h"


Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(!itemAt(event->scenePos(), QTransform())){
            if (nextItem == Geometry::RECTANGLE){
                QGraphicsRectItem * item = addRect(0, 0, 100, 50, QPen(),
                                     QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setPos(event->scenePos());
                nextItem = Geometry::ELLIPS;
            }else if(nextItem == Geometry::ELLIPS){
                QGraphicsEllipseItem * item = addEllipse(0, 0, 100, 50, QPen(),
                                     QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setPos(event->scenePos());
                nextItem = Geometry::STAR;
            }else if(nextItem == Geometry::STAR){
                QGraphicsPolygonItem *item = addPolygon(makeStar(),QPen(),
                                     QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setPos(event->scenePos());
                nextItem = Geometry::RECTANGLE;

            }
        }
    }else if (event->button() == Qt::RightButton)
    {
        if(itemAt(event->scenePos(), QTransform())){
            removeItem(itemAt(event->scenePos(), QTransform()));
        }
    }else if (event->button() == Qt::MidButton)
    {
        if(itemAt(event->scenePos(), QTransform())){
            QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
            qint32 angle = item->rotation();
            item->setTransformOriginPoint(50, 25);
            item->setRotation(angle + 20);
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    double delta = event->delta();

       if (delta > 0)
       {
           emit scaleUp();
       }else {
           emit scaleDown();
       }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Plus)
    {
        emit scaleUp();
    } else if(event->key() == Qt::Key::Key_Minus){
        emit scaleDown();
    }

    QGraphicsScene::keyPressEvent(event);
}

QPolygonF Scene::makeStar() const
{
    QPolygonF polygon;
    const qint32 m_radius = 40;
    size_t small_radius = m_radius/2;
    double step = 360./5, angle_deg = 55;
    for (size_t count = 0; count < 5; ++count) {
        double angle_rad = angle_deg*M_PI/180;
        QPointF outerPoint(m_radius*cos(angle_rad), m_radius*sin(angle_rad));
        QPointF innerPoint(small_radius*cos(angle_rad+10), small_radius*sin(angle_rad+10));
        polygon << outerPoint << innerPoint;
        angle_deg += step;
    }
    return polygon;

}

#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QGraphicsObject>
#include <QtMath>
#include <QKeyEvent>
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);
    enum Geometry {RECTANGLE, ELLIPS, STAR};
    Geometry nextItem = Geometry::RECTANGLE;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    QPolygonF makeStar() const;
signals:
    void scaleUp();
    void scaleDown();
};

#endif // SCENE_H

#include "Walker.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>


constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;


static qreal normalizeAngle(qreal angle)
{
    while (angle < 0) {
        angle += TwoPi;
    }
    while (angle >= TwoPi) {
        angle -= TwoPi;
    }
    return angle;
}


Walker::Walker() :
    angle(0.0),
    speed(0.0),
    mouseEyeDirection(0.0),
    color(QRandomGenerator::global()->bounded(256),
          QRandomGenerator::global()->bounded(256),
          QRandomGenerator::global()->bounded(256))
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    for(int i = 0; i < 100; ++i) {
        setPos(mapToParent(QRandomGenerator::global()->bounded(10),
                           QRandomGenerator::global()->bounded(10)));
    }
}
Walker::Walker(qreal x, qreal y) :
    Walker()
{
    setPos(x, y);
}

QRectF Walker::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}
QPainterPath Walker::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Walker::advance(int step)
{
    if (!step) {
        return;
    }
}
void Walker::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));
}
#ifndef WALKER_H
#define WALKER_H


#include <QGraphicsItem>

//! [0]
class walker : public QGraphicsItem
{
public:
    walker();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
};

#endif // WALKER_H

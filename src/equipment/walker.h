#pragma once


#include <QGraphicsItem>


//! [0]
class Walker : public QGraphicsItem
{
private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    QColor color;

protected:
    void advance(int step) override;

public:
    Walker();
    Walker(qreal x, qreal y);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

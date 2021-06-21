#pragma once


#include <QGraphicsItem>


//! [0]
class Walker : public QGraphicsItem
{
private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
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

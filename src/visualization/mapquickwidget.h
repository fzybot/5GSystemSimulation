#ifndef MAPQUICKWIDGET_H
#define MAPQUICKWIDGET_H

#include <QQuickWidget>

class MapQuickWidget: public QQuickWidget
{
public:
    MapQuickWidget(QWidget *parent = Q_NULLPTR):QQuickWidget(parent){
        setSource(QUrl("qrc://src/qml/map.qml"));
        setResizeMode(QQuickWidget::SizeRootObjectToView);
    }
};

#endif // MAPQUICKWIDGET_H

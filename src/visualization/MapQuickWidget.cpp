#include "MapQuickWidget.h"


MapQuickWidget::MapQuickWidget(QWidget* parent) :
    QQuickWidget(parent)
{
    setSource(QUrl("qrc://src/qml/map.qml"));
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

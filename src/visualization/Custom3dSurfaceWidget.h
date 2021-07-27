#pragma once

#include <QWidget>

#include "src/visualization/Custom3dSurface.h"

class Custom3dSurfaceWidget : public QWidget
{
    Q_OBJECT

private:
    Custom3dSurface* surface_;

public:
    explicit Custom3dSurfaceWidget(QWidget *parent = nullptr);

};


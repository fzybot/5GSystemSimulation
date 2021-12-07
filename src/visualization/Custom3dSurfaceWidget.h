#pragma once

#include <QWidget>

#include "src/visualization/Custom3dSurface.h"

class Custom3dSurfaceWidget : public QWidget
{
    Q_OBJECT

private:
    Custom3dSurface* surface_;
    QGroupBox *gradientGroupBox_;
    QLabel *label_;

public:
    explicit Custom3dSurfaceWidget(QWidget *parent = nullptr);

public slots:
    void changeGradient();
    void changeSettings(void*);

signals:
    void settingsChanged(void*);

};


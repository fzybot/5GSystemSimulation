    /*///////////////////////////////////////
   // Author: Bondarenko Sergey Ivanovich //
  // Email: kosrotoff2002@gmail.com      //
*/////////////////////////////////////////


#pragma once


#include <QWidget>

#include "src/visualization/MapQuickWidget.h"
#include "src/visualization/Heatmap.h"


class Map : public QWidget
{
    Q_OBJECT

private:
    MapQuickWidget* mapQuickWidget_;
    Heatmap* heatmap_;

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;

public:
    explicit Map(QWidget* parent = Q_NULLPTR);

public slots:
    void startSim();
    void stopSim();
    void changeSettings(int*);

signals:
    void changedSettings(int*);
};


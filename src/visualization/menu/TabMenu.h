#pragma once

#include <QDialog>
#include "src/visualization/Map.h"
#include "src/visualization/Custom3dSurfaceWidget.h"
#include "src/visualization/ChartGroupWidget.h"

class QTabWidget;

class TabMenu : public QDialog
{
    Q_OBJECT

private:
    QTabWidget *tabWidget;
    Map* map_;
    Custom3dSurfaceWidget* surfaceWidget_;
    ChartGroupWidget *chartsWidget_;

public:
    explicit TabMenu(QWidget *parent = nullptr);

public slots:
    void changeNumberOfUe(int);

signals:
    void changedNumberOfUe(int);

};


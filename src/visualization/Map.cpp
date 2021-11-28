#include "Map.h"

#include <QPainter>
#include <QGridLayout>
#include <QPushButton>


// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Map::Map(QWidget *parent) :
    QWidget(parent),
    mapQuickWidget_(new MapQuickWidget),
    heatmap_(new Heatmap(mapQuickWidget_))
{
    heatmap_->resize(1600, 1200);
    connect(this, &Map::changedNumberOfUe, mapQuickWidget_, &MapQuickWidget::changeNumberOfUe);
}

void Map::startSim()
{
    mapQuickWidget_->startSim();
}

void Map::stopSim()
{
    mapQuickWidget_->stopSim();
}

void Map::changeNumberOfUe(int number)
{
    qDebug() << "Map gets it :" << number;
    emit changedNumberOfUe(number);
}



// ----- [ PROTECTED METHODS ] -----------------------------------------------------------------------------------------

void Map::paintEvent(QPaintEvent*)
{
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(mapQuickWidget_, 0, 0);

    mapQuickWidget_->getPosition();

    QPushButton *startButton = new QPushButton("START");
    QPushButton *stopButton = new QPushButton("STOP");
    const QSize buttonSize = QSize(50, 20);
    startButton->setFixedSize(buttonSize);
    stopButton->setFixedSize(buttonSize);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    buttonLayout->setAlignment(Qt::AlignTop);

    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);

    connect(startButton, &QPushButton::pressed, this, &Map::startSim);
    connect(stopButton, &QPushButton::pressed, this, &Map::stopSim);

    mapQuickWidget_->getPosition();
}
void Map::resizeEvent(QResizeEvent* event)
{
    mapQuickWidget_->resize(event->size());
}

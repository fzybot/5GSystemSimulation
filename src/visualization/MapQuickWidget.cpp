#include "MapQuickWidget.h"
#include <QDebug>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include <QCoreApplication>


MapQuickWidget::MapQuickWidget(QWidget* parent) :
    QQuickWidget(parent),
    manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &MapQuickWidget::findAddress);

    ueModel_ = new UEModel;

    connect(this, &MapQuickWidget::changedSettings, ueModel_, &UEModel::changeSettings);

    this->engine()->rootContext()->setContextProperty("_ueModel", ueModel_);
    this->engine()->rootContext()->setContextProperty("PixelMap", QString("file://").append(QString(QCoreApplication::applicationDirPath()).append("/pixelMap.bmp")));

    setSource(QUrl("qrc://src/qml/map.qml"));

    setResizeMode(QQuickWidget::SizeRootObjectToView);

    getAddress("55°00'46.3N", "82°57'01.5E");
    //getAddress("80°00'47.5N", "82°57'01.9E");
    //getAddress("60°00'47.5N", "52°57'01.9E");
    //getAddress("34°00'47.5N", "12°57'01.9E");
    //getAddress("27°00'47.5N", "02°57'01.9E");

}

void MapQuickWidget::getAddress(QString latitude, QString longitude)
{
    latitude_1 = latitude.left(latitude.length() - 1);
    latitude_2 = latitude.back();
    longitude_1 = longitude.left(longitude.length() - 1);
    longitude_2 = longitude.back();

    QUrl url("https://www.google.ru/maps/place/" + latitude_1 + "\"" + latitude_2 + "+" + longitude_1 + "\"" + longitude_2);
    manager->get(QNetworkRequest(url));
}

void MapQuickWidget::findAddress(QNetworkReply* reply)
{
    QString data(reply->readAll());

    QString search(latitude_1 + "\\\"" + latitude_2 + " " + longitude_1 + "\\\"" + longitude_2);
    QString result("");

    int index = data.lastIndexOf(search) + search.length() + 3;
    while (data[index] != '\"') {
        result.push_back(data[index]);
        ++index;
    }
    qDebug() << result << Qt::endl;

    reply->deleteLater();
}
void MapQuickWidget::getPosition()
{


}

void MapQuickWidget::startSim()
{
    ueModel_->startSim();
}

void MapQuickWidget::stopSim()
{
    ueModel_->stopSim();
}

void MapQuickWidget::changeSettings(int* number)
{
    qDebug() << "MapQuick gets it: " << number;
    emit changedSettings(number);
}

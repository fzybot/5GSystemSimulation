#include "MapQuickWidget.h"
#include "MapToCpp.h"

#include <QDebug>
#include <QQmlComponent>

#include <QGuiApplication>
#include <QQmlProperty>
#include <QQuickView>
#include <QQuickItem>
#include <QMetaObject>
#include "UEModel.h"
#include <QQmlEngine>
#include <QQmlContext>

MapQuickWidget::MapQuickWidget(QWidget* parent) :
    QQuickWidget(parent),
    manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &MapQuickWidget::findAddress);

    UEModel* ueModel = new UEModel;

    this->engine()->rootContext()->setContextProperty("_ueModel", ueModel);
    setSource(QUrl("qrc://src/qml/map.qml"));

    ueModel->setData(ueModel->index(0),55.023902, UEModel::MoveToLatRole);
    ueModel->setData(ueModel->index(0),82.960326, UEModel::MoveToLonRole);

    ueModel->insertRows(ueModel->rowCount(), 10);
    ueModel->removeRows(0, 4);

    setResizeMode(QQuickWidget::SizeRootObjectToView);

    //getAddress("55°00'46.3N", "82°57'01.5E");

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

#pragma once


#include <QQuickWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class MapQuickWidget: public QQuickWidget
{
    Q_OBJECT

private:
    QNetworkAccessManager* manager;
    QString latitude_1;
    QString latitude_2;
    QString longitude_1;
    QString longitude_2;

    void findAddress(QNetworkReply* reply);

public:
    MapQuickWidget(QWidget* parent = Q_NULLPTR);

    void getAddress(QString latitude, QString longitude);
    void getPosition();
};

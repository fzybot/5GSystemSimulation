#ifndef UEMODEL_H
#define UEMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QTimer>
#include "src/equipment/mobility/Mobility.h"
#include "src/core/CartesianCoordinates.h"
#include "src/visualization/settingsTemplate.h"

struct mapObjectData {
    mapObjectData() {}
    mapObjectData( const QString& name, double lat, double lon, double moveToLat, double moveToLon)
        : name(name), lat(lat), lon(lon) , moveToLat(moveToLat), moveToLon(moveToLon){}
    QString name;
    double lat;
    double lon;
    double moveToLat;
    double moveToLon;
};


class UEModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles {
        NameRole = Qt::UserRole,
        LatRole,
        LonRole,
        MoveToLatRole,
        MoveToLonRole
    };

    explicit UEModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool addData(mapObjectData);
    bool removeDataByName(QString);

    Mobility::Model getModelBySettings();

public slots:
    void testUpdateModel();
    void startSim();
    void stopSim();
    void changeSettings(void*);

private:
    QVector <mapObjectData> m_data;
    QVector <Mobility> m_mobility;
    QTimer m_timer;
    int ueNumber_ = 0;
    int mobilityModelSettings = 0;
    int txPower;
    int feederLos;
    int antennaGain;
    int noiseFigure;
};

#endif // UEMODEL_H

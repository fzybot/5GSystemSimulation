#ifndef UEMODEL_H
#define UEMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QTimer>

struct Data {
    Data() {}
    Data( const QString& name, double lat, double lon, double moveToLat, double moveToLon)
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

    bool addData(Data);
    bool removeDataByName(QString);

public slots:
    void testUpdateModel();

private:
    QVector <Data> m_data;
    QTimer m_timer;
};

#endif // UEMODEL_H

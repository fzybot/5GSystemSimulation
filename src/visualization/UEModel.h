#ifndef UEMODEL_H
#define UEMODEL_H

#include <QAbstractListModel>

struct Data {
    Data() {}
    Data( const QString& name, double lat, double lon )
        : name(name), lat(lat), lon(lon) {}
    QString name;
    double lat;
    double lon;
};


class UEModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles {
        NameRole = Qt::UserRole,
        LatRole,
        LonRole
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

private:
    QVector <Data> m_data;
};

#endif // UEMODEL_H

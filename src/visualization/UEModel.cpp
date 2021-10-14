#include "UEModel.h"

UEModel::UEModel(QObject *parent)
    : QAbstractListModel(parent)
{

    m_data << Data("user1", 55.012902, 82.950326, 55.022902, 82.960326)
           << Data("user2", 55.013902, 82.951326, 55.023902, 82.961326);
}

int UEModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return m_data.count();
}

QVariant UEModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!

    const Data &data = m_data.at(index.row());
    if ( role == NameRole )
        return data.name;
    else if ( role == LatRole )
        return data.lat;
    else if ( role == LonRole)
        return data.lon;
    else if ( role == MoveToLatRole)
        return data.moveToLat;
    else if ( role == MoveToLonRole)
        return data.moveToLon;
    else return QVariant();


}

QHash<int, QByteArray> UEModel::roleNames() const
{
    static QHash<int, QByteArray> mapping{
        {NameRole, "name"},
        {LatRole, "lat"},
        {LonRole, "lon"},
        {MoveToLatRole, "moveToLat"},
        {MoveToLonRole, "moveToLon"}
    };

    return mapping;
}

bool UEModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Data& data = m_data[ index.row() ];

        if ( role == NameRole )
            data.name = value.toString();
        else if ( role == LatRole )
            data.lat = value.toDouble();
        else if ( role == LonRole)
            data.lon = value.toDouble();
        else if ( role == MoveToLatRole)
            data.moveToLat = value.toDouble();
        else if ( role == MoveToLonRole)
            data.moveToLon = value.toDouble();

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags UEModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}


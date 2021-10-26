#include "UEModel.h"

UEModel::UEModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(testUpdateModel()));
    m_timer.start(1200);
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

bool UEModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    int k=1;
    for (int index = row; index < row + count; ++index){
        m_data.insert(index, Data("new" + QString::number(k), 55.012902, 82.950326, 55.012902, 82.950326));
        k++;
    }
    endInsertRows();
    return true;
}

bool UEModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    int index = row;
    for (int k = row; k < row + count; ++k){
        m_data.removeAt(index);
    }
    endRemoveRows();
    return true;
}

bool UEModel::addData(Data data)
{
    m_data << data;
    return true;
}

bool UEModel::removeDataByName(QString)
{

    return true;
}

void UEModel::testUpdateModel()
{
    srand(time(NULL));
    //qDebug()<<"move...";
    int row = 0;
    insertRows(rowCount(), 1);
    for (Data ue : m_data){
        setData(index(row), ((float)rand()/(float)RAND_MAX)*0.009063 + 55.009088, UEModel::MoveToLatRole);
        setData(index(row), ((float)rand()/(float)RAND_MAX)*0.026839 + 82.933401, UEModel::MoveToLonRole);
        row++;
    }

}

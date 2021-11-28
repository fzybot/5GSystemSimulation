#include "UEModel.h"

UEModel::UEModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(testUpdateModel()));
    m_timer.stop();
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

    const mapObjectData &data = m_data.at(index.row());
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
        mapObjectData& data = m_data[ index.row() ];

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
        m_data.insert(index, mapObjectData("new" + QString::number(k), 55.012902, 82.950326, 55.012902, 82.950326));
        Mobility mobility;
        mobility.setModel(Mobility::Model::CONSTANT_POSITION);
        m_mobility.insert(index, mobility);
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
        m_mobility.removeAt(index);
    }
    endRemoveRows();
    return true;
}

bool UEModel::addData(mapObjectData data)
{
    m_data << data;
    return true;
}

bool UEModel::removeDataByName(QString)
{

    return true;
}

Mobility::Model UEModel::getModelBySettings()
{
    if(mobilityModelSettings == 0){
        switch (rand()%3 + 1) {
            case 1:{
                return Mobility::Model::RANDOM_WALK;
            }
            case 2:{
                return Mobility::Model::RANDOM_WAYPOINT;
            }
            case 3:{
                return Mobility::Model::GAUSS_MARKOV;
            }
        }
    }
    if(mobilityModelSettings == 1){
        return Mobility::Model::RANDOM_WALK;
    }
    if(mobilityModelSettings == 2){
        return Mobility::Model::RANDOM_WAYPOINT;
    }
    if(mobilityModelSettings == 3){
        return Mobility::Model::GAUSS_MARKOV;
    }
}

void UEModel::testUpdateModel()
{
    srand(time(NULL));
    //qDebug()<<"move...";
    int row = 0;
    double randLat = 0, randLon = 0;
    //if(rowCount() == 0) insertRows(rowCount(), 1);
    if(rowCount() < ueNumber_){
        for (int i = rowCount(); i < ueNumber_; ++i){
            randLat = ((float)rand()/(float)RAND_MAX)*0.009063 + 55.009088;
            randLon = ((float)rand()/(float)RAND_MAX)*0.026839 + 82.933401;
            insertRows(rowCount(),1);
            setData(index(rowCount()-1), randLat, LatRole);
            setData(index(rowCount()-1), randLon, LonRole);
            setData(index(rowCount()-1), randLat, MoveToLatRole);
            setData(index(rowCount()-1), randLon, MoveToLonRole);
            m_mobility[i].setAngle(((float)rand()/(float)RAND_MAX)*2*M_PI + 0);
            m_mobility[i].setSpeed(rand()%10 + 1);
            m_mobility[i].setModel(getModelBySettings());
            m_mobility[i].setAlpha(0.75);
            m_mobility[i].setBorders(55.018151, 55.009088, 82.933401, 82.960240);
            m_mobility[i].setBorderZone(0.000100);
            m_mobility[i].setMinSpeed(1);
            m_mobility[i].setMaxSpeed(10);
            m_mobility[i].setPauseTime(0.00003);
        }
    }
    if(rowCount() > ueNumber_){
        removeRows(ueNumber_, rowCount()-ueNumber_);
    }

    for (mapObjectData ue : m_data){
            CartesianCoordinates* coord = new CartesianCoordinates(ue.moveToLon, ue.moveToLat, 0);
            m_mobility[row].setPosition(coord);
            m_mobility[row].updatePosition(m_mobility[row].getPositionLastUpdate() + 0.00001);
            randLon = m_mobility[row].getPosition()->getCoordinateX();
            randLat = m_mobility[row].getPosition()->getCoordinateY();
            setData(index(row), randLat, UEModel::LatRole);
            setData(index(row), randLon, UEModel::LonRole);
            setData(index(row), randLat, UEModel::MoveToLatRole);
            setData(index(row), randLon, UEModel::MoveToLonRole);
        row++;
    }

}

void UEModel::startSim()
{
    m_timer.start(34);
}

void UEModel::stopSim()
{
    m_timer.stop();
}

void UEModel::changeSettings(int* settings)
{
    ueNumber_ = settings[6];
    mobilityModelSettings = settings[7];
}

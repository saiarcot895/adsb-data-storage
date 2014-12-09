#include "aircraftmodel.h"

AircraftModel::AircraftModel(QList<Aircraft> aircrafts, QObject *parent) :
    QAbstractListModel(parent),
    aircrafts(aircrafts)
{
}

QHash<int, QByteArray> AircraftModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AircraftModel::HexCode] = "hexCode";
    roles[AircraftModel::PositionCount] = "positionCount";
    return roles;
}

int AircraftModel::rowCount(const QModelIndex &parent) const {
    return aircrafts.size();
}

QVariant AircraftModel::data(const QModelIndex &index, int role) const {
    const Aircraft aircraft = aircrafts.at(index.row());
    if (role == AircraftModel::HexCode) {
        return aircraft.getHexCode();
    } else if (role == AircraftModel::PositionCount) {
        return aircraft.getPositionData().size();
    }
    return QVariant();
}

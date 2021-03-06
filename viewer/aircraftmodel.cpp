#include "aircraftmodel.h"
#include <QtAlgorithms>

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
        return aircraft.getReports().size();
    }
    return QVariant();
}

void AircraftModel::sort(int column, Qt::SortOrder order) {
    emit layoutAboutToBeChanged();
    if (column == 0) {
        if (order == Qt::AscendingOrder) {
            std::sort(aircrafts.begin(), aircrafts.end(), &AircraftModel::sortHexCodeAscending);
        } else {
            std::sort(aircrafts.begin(), aircrafts.end(), &AircraftModel::sortHexCodeDescending);
        }
    } else if (column == 1) {
        if (order == Qt::AscendingOrder) {
            std::sort(aircrafts.begin(), aircrafts.end(), &AircraftModel::sortPositionCountAscending);
        } else {
            std::sort(aircrafts.begin(), aircrafts.end(), &AircraftModel::sortPositionCountDescending);
        }
    }
    emit layoutChanged();
}

bool AircraftModel::sortHexCodeAscending(const Aircraft left, const Aircraft right) {
    return left.getHexCode() < right.getHexCode();
}

bool AircraftModel::sortPositionCountAscending(const Aircraft left, const Aircraft right) {
    return left.getReports().size() < right.getReports().size();
}

bool AircraftModel::sortHexCodeDescending(const Aircraft left, const Aircraft right) {
    return left.getHexCode() > right.getHexCode();
}

bool AircraftModel::sortPositionCountDescending(const Aircraft left, const Aircraft right) {
    return left.getReports().size() > right.getReports().size();
}

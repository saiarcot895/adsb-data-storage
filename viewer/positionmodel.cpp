#include "positionmodel.h"

PositionModel::PositionModel(QList<Position> positions, QObject *parent) :
    QAbstractListModel(parent),
    positions(positions)
{
}

void PositionModel::setPositions(QList<Position> positions) {
    emit layoutAboutToBeChanged();
    this->positions = positions;
    emit layoutChanged();
}

QHash<int, QByteArray> PositionModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PositionModel::ReportingTime] = "reportingTime";
    roles[PositionModel::MessageType] = "messageType";
    roles[PositionModel::Latitude] = "latitude";
    roles[PositionModel::Longitude] = "longitude";
    roles[PositionModel::Altitude] = "altitude";
    return roles;
}

int PositionModel::rowCount(const QModelIndex &parent) const {
    return positions.size();
}

QVariant PositionModel::data(const QModelIndex &index, int role) const {
    Position position = positions.at(index.row());
    if (role == PositionModel::ReportingTime) {
        return position.getReportingTime();
    } else if (role == PositionModel::MessageType) {
        return position.getMessageType();
    }
    return QVariant();
}

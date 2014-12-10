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
    roles[PositionModel::VerticalRate] = "verticalRate";
    roles[PositionModel::Speed] = "speed";
    roles[PositionModel::Track] = "track";
    roles[PositionModel::Squawk] = "squawk";
    return roles;
}

int PositionModel::rowCount(const QModelIndex &parent) const {
    return positions.size();
}

QVariant PositionModel::data(const QModelIndex &index, int role) const {
    const Position position = positions.at(index.row());
    if (role == PositionModel::ReportingTime) {
        return position.getReportingTime();
    } else if (role == PositionModel::MessageType) {
        return position.getMessageType();
    } else if (role == PositionModel::Latitude) {
        return position.getLatitude();
    } else if (role == PositionModel::Longitude) {
        return position.getLongitude();
    } else if (role == PositionModel::Altitude) {
        return position.getAltitude();
    }
    return QVariant();
}

QVariant PositionModel::data(int row, QString role) const {
    const QHash<int, QByteArray> roles = roleNames();
    int roleInt = roles.key(role.toLocal8Bit());
    return data(index(row), roleInt);
}

#ifndef POSITIONMODEL_H
#define POSITIONMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include "position.h"

class PositionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PositionModel(QList<Position> positions, QObject *parent = 0);

    enum Roles {
        ReportingTime,
        MessageType,
        Latitude,
        Longitude,
        Altitude,
        VerticalRate,
        Speed,
        Track,
        Squawk,
        Callsign
    };

    void setPositions(QList<Position> positions);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<Position> positions;

};

#endif // POSITIONMODEL_H

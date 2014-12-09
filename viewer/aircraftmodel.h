#ifndef AIRCRAFTMODEL_H
#define AIRCRAFTMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QHash>
#include "aircraft.h"

class AircraftModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AircraftModel(QList<Aircraft> aircrafts, QObject *parent = 0);

    enum Roles {
        HexCode,
        PositionCount
    };

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<Aircraft> aircrafts;

};

#endif // AIRCRAFTMODEL_H

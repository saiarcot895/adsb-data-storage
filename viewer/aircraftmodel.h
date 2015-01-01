#ifndef AIRCRAFTMODEL_H
#define AIRCRAFTMODEL_H

#include <QAbstractListModel>
#include <QList>
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
    Q_INVOKABLE void sort(int column, Qt::SortOrder order);
private:
    QList<Aircraft> aircrafts;

    static bool sortHexCodeAscending(const Aircraft left, const Aircraft right);
    static bool sortPositionCountAscending(const Aircraft left, const Aircraft right);
    static bool sortHexCodeDescending(const Aircraft left, const Aircraft right);
    static bool sortPositionCountDescending(const Aircraft left, const Aircraft right);

};

#endif // AIRCRAFTMODEL_H

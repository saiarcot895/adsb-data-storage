#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QObject>

#include <QSharedDataPointer>
#include <QList>
#include "position.h"

class AircraftData;

class Aircraft : public QObject
{
public:
    Aircraft();
    Aircraft(const Aircraft &);
    Aircraft &operator=(const Aircraft &);
    ~Aircraft();

    quint32 getHexCode() const;
    QList<Position> getPositionData() const;

    void addPosition(const Position position);
private:
    QSharedDataPointer<AircraftData> data;
};

#endif // AIRCRAFT_H

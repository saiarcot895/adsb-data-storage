#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QObject>

#include <QExplicitlySharedDataPointer>
#include <QList>
#include "position.h"

class AircraftData;

class Aircraft : public QObject
{
public:
    Aircraft(quint32 hexCode = 0);
    Aircraft(const Aircraft &);
    Aircraft &operator=(const Aircraft &);
    ~Aircraft();

    quint32 getHexCode() const;
    QList<Position> getPositionData() const;

    void addPosition(const Position position);

    friend QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft);
    friend QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft);
private:
    QExplicitlySharedDataPointer<AircraftData> data;
};

#endif // AIRCRAFT_H

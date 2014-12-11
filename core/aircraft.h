#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "core_global.h"

#include <QObject>

#include <QExplicitlySharedDataPointer>
#include <QList>
#include "position.h"

class AircraftData;

class CORESHARED_EXPORT Aircraft : public QObject
{
public:
    Aircraft(quint32 hexCode = 0);
    Aircraft(const Aircraft &);
    Aircraft &operator=(const Aircraft &);
    ~Aircraft();

    quint32 getHexCode() const;
    QList<Position> getPositionData() const;
    Position getPositionData(const QDateTime time) const;

    void addPosition(const Position position);

    friend CORESHARED_EXPORT QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft);
    friend CORESHARED_EXPORT QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft);
private:
    QExplicitlySharedDataPointer<AircraftData> data;
};

#endif // AIRCRAFT_H

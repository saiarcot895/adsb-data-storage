#include "aircraft.h"
#include <QSharedData>
#include <QDataStream>

class AircraftData : public QSharedData {
public:
    quint32 hexCode;
    QList<Position> positions;
};

Aircraft::Aircraft(quint32 hexCode) : data(new AircraftData)
{
    data->hexCode = hexCode;
}

Aircraft::Aircraft(const Aircraft &rhs) : data(rhs.data)
{
}

quint32 Aircraft::getHexCode() const {
    return data->hexCode;
}

QList<Position> Aircraft::getPositionData() const {
    return data->positions;
}

void Aircraft::addPosition(const Position position) {
    data->positions.append(position);
}

Aircraft &Aircraft::operator=(const Aircraft &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft) {
    stream << aircraft.data->hexCode;
    stream << aircraft.data->positions;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft) {
    aircraft = Aircraft();

    stream >> aircraft.data->hexCode;
    stream >> aircraft.data->positions;

    return stream;
}

Aircraft::~Aircraft()
{
}

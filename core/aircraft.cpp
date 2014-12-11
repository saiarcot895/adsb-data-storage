#include "aircraft.h"
#include <QSharedData>
#include <QDataStream>
#include <QMap>

class AircraftData : public QSharedData {
public:
    quint32 hexCode;
    QMap<QDateTime, Position> positions;
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
    return data->positions.values();
}

Position Aircraft::getPositionData(const QDateTime time) const {
    return data->positions.value(time);
}

void Aircraft::addPosition(const Position position) {
    data->positions.insert(position.getReportingTime(), position);
}

Aircraft &Aircraft::operator=(const Aircraft &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft) {
    stream << aircraft.data->hexCode;
    stream << aircraft.data->positions.values();

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft) {
    aircraft = Aircraft();

    stream >> aircraft.data->hexCode;

    QList<Position> positions;
    stream >> positions;

    for (int i = 0; i < positions.size(); i++) {
        const Position position = positions.at(i);
        aircraft.data->positions.insert(position.getReportingTime(), position);
    }

    return stream;
}

Aircraft::~Aircraft()
{
}

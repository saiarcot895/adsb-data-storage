#include "aircraft.h"
#include <QSharedData>
#include <QDataStream>
#include <QMap>

class AircraftData : public QSharedData {
public:
    quint32 hexCode;
    QMap<QDateTime, Report> reports;
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

QList<Report> Aircraft::getReports() const {
    return data->reports.values();
}

Report Aircraft::getReports(const QDateTime time) const {
    return data->reports.value(time);
}

void Aircraft::addReport(const Report report) {
    data->reports.insert(report.getReportingTime(), report);
}

Aircraft &Aircraft::operator=(const Aircraft &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft) {
    stream << aircraft.data->hexCode;
    stream << aircraft.data->reports.values();

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft) {
    aircraft = Aircraft();

    stream >> aircraft.data->hexCode;

    QList<Report> positions;
    stream >> positions;

    for (int i = 0; i < positions.size(); i++) {
        const Report position = positions.at(i);
        aircraft.data->reports.insert(position.getReportingTime(), position);
    }

    return stream;
}

Aircraft::~Aircraft()
{
}

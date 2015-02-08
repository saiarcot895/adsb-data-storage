#include "aircraft.h"
#include <QSharedData>
#include <QDataStream>
#include <QMap>

Aircraft::Version Aircraft::dataVersion = Aircraft::Adsb_Data_Default;

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

Aircraft::Version Aircraft::getDataVersion() {
    return Aircraft::dataVersion;
}

void Aircraft::setDataVersion(Version dataVersion) {
    Aircraft::dataVersion = dataVersion;
}

Aircraft &Aircraft::operator=(const Aircraft &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Aircraft operator+(const Aircraft& aircraft1, const Aircraft& aircraft2) {
    if (aircraft1.data->hexCode == aircraft2.data->hexCode) {
        Aircraft aircraft3(aircraft1.data->hexCode);
        aircraft3.data->reports.unite(aircraft1.data->reports);
        aircraft3.data->reports.unite(aircraft2.data->reports);
        return aircraft3;
    } else {
        return aircraft1;
    }
}

Aircraft operator+=(const Aircraft& aircraft1, const Aircraft& aircraft2) {
    return aircraft1 + aircraft2;
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

    foreach (Report position, positions) {
        aircraft.data->reports.insert(position.getReportingTime(), position);
    }

    return stream;
}

Aircraft::~Aircraft()
{
}

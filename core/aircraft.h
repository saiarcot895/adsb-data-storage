#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "core_global.h"

#include <QObject>

#include <QExplicitlySharedDataPointer>
#include <QList>
#include "report.h"

class AircraftData;

class CORESHARED_EXPORT Aircraft : public QObject
{
public:
    Aircraft(quint32 hexCode = 0);
    Aircraft(const Aircraft &);
    Aircraft &operator=(const Aircraft &);
    ~Aircraft();

    enum Version {
        Adsb_Data_1_0 = 1,

        Adsb_Data_Default = Adsb_Data_1_0
    };

    quint32 getHexCode() const;
    QList<Report> getReports() const;
    Report getReports(const QDateTime time) const;

    void addReport(const Report report);

    static Version getDataVersion();
    static void setDataVersion(Version dataVersion);

    friend CORESHARED_EXPORT Aircraft operator+(const Aircraft& aircraft1, const Aircraft& aircraft2);
    friend CORESHARED_EXPORT Aircraft operator+=(const Aircraft& aircraft1, const Aircraft& aircraft2);

    friend CORESHARED_EXPORT QDataStream& operator<<(QDataStream& stream, const Aircraft& aircraft);
    friend CORESHARED_EXPORT QDataStream& operator>>(QDataStream& stream, Aircraft& aircraft);
private:
    static Version dataVersion;
    QExplicitlySharedDataPointer<AircraftData> data;
};

#endif // AIRCRAFT_H

#ifndef POSITION_H
#define POSITION_H

#include <QObject>

#include <QSharedDataPointer>
#include <QDateTime>
#include <QtPositioning/QGeoCoordinate>

class PositionData;

class Position : public QObject
{
public:
    Position();
    Position(const Position &);
    Position &operator=(const Position &);
    ~Position();

    QDateTime getReportingTime() const;
    bool areCoordinatesSet() const;
    qreal getLatitude() const;
    qreal getLongitude() const;
    bool isAltitudeSet() const;
    qint32 getAltitude() const;
    bool isSpeedSet() const;
    quint16 getSpeed() const;
    bool isTrackSet() const;
    quint16 getTrack() const;
    bool isSquawkSet() const;
    quint16 getSquawk() const;

    void setReportingTime(QDateTime reportingTime);
    void setCoordinates(qreal latitude, qreal longitude);
    void setAltitude(qint32 altitude);
    void setSpeed(quint16 speed);
    void setTrack(quint16 track);
    void setSquawk(quint16 squawk);

private:
    QSharedDataPointer<PositionData> data;
};

#endif // POSITION_H

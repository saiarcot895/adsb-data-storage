#include "position.h"
#include <QSharedData>

class PositionData : public QSharedData {
public:
    QDateTime reportingTime;
    bool coordinatesSet = false;
    qreal latitude;
    qreal longitude;
    bool altitudeSet = false;
    qint32 altitude;
    bool speedSet = false;
    quint16 speed;
    bool trackSet = false;
    quint16 track;
    bool squawkSet = false;
    quint16 squawk;
};

Position::Position() : data(new PositionData)
{
}

Position::Position(const Position &rhs) : data(rhs.data)
{
}

QDateTime Position::getReportingTime() const {
    return data->reportingTime;
}

bool Position::areCoordinatesSet() const {
    return data->coordinatesSet;
}

qreal Position::getLatitude() const {
    return data->coordinatesSet ? data->latitude : 0;
}

qreal Position::getLongitude() const {
    return data->coordinatesSet ? data->longitude : 0;
}

bool Position::isAltitudeSet() const {
    return data->altitudeSet;
}

qint32 Position::getAltitude() const {
    return data->altitude;
}

bool Position::isSpeedSet() const {
    return data->speedSet;
}

quint16 Position::getSpeed() const {
    return data->speed;
}

bool Position::isTrackSet() const {
    return data->trackSet;
}

quint16 Position::getTrack() const {
    return data->track;
}

bool Position::isSquawkSet() const {
    return data->squawkSet;
}

quint16 Position::getSquawk() const {
    return data->squawk;
}

void Position::setReportingTime(QDateTime reportingTime) {
    data->reportingTime = reportingTime;
}

void Position::setCoordinates(qreal latitude, qreal longitude) {
    data->latitude = latitude;
    data->longitude = longitude;
    data->coordinatesSet = true;
}

void Position::setAltitude(qint32 altitude) {
    data->altitude = altitude;
    data->altitudeSet = true;
}

void Position::setSpeed(quint16 speed) {
    data->speed = speed;
    data->speedSet = true;
}

void Position::setTrack(quint16 track) {
    data->track = track;
    data->trackSet = true;
}

void Position::setSquawk(quint16 squawk) {
    data->squawk = squawk;
    data->squawkSet = true;
}

Position &Position::operator=(const Position &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Position::~Position()
{
}

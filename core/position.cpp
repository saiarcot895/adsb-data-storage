#include "position.h"
#include <QSharedData>
#include <QDataStream>

class PositionData : public QSharedData {
public:
    QDateTime reportingTime;
    Position::MessageType messageType = Position::Unknown;
    qreal latitude = 0;
    qreal longitude = 0;
    qint32 altitude = 0;
    qint32 verticalRate = 0;
    quint16 speed = 0;
    quint16 track = 0;
    quint16 squawk = 0;
    QString callsign;
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

Position::MessageType Position::getMessageType() const {
    return data->messageType;
}

qreal Position::getLatitude() const {
    return data->latitude;
}

qreal Position::getLongitude() const {
    return data->longitude;
}

qint32 Position::getAltitude() const {
    return data->altitude;
}

qint32 Position::getVerticalRate() const {
    return data->verticalRate;
}

quint16 Position::getSpeed() const {
    return data->speed;
}

quint16 Position::getTrack() const {
    return data->track;
}

quint16 Position::getSquawk() const {
    return data->squawk;
}

QString Position::getCallsign() const {
    return data->callsign;
}

void Position::setReportingTime(QDateTime reportingTime) {
    data->reportingTime = reportingTime;
}

void Position::setMessageType(Position::MessageType messageType) {
    data->messageType = messageType;
}

void Position::setCoordinates(qreal latitude, qreal longitude) {
    data->latitude = latitude;
    data->longitude = longitude;
}

void Position::setAltitude(qint32 altitude) {
    data->altitude = altitude;
}

void Position::setVerticalRate(qint32 verticalRate) {
    data->verticalRate = verticalRate;
}

void Position::setSpeed(quint16 speed) {
    data->speed = speed;
}

void Position::setTrack(quint16 track) {
    data->track = track;
}

void Position::setSquawk(quint16 squawk) {
    data->squawk = squawk;
}

void Position::setCallsign(QString callsign) {
    data->callsign = callsign;
}

Position &Position::operator=(const Position &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const Position& position) {
    stream << position.data->reportingTime;
    stream << position.data->messageType;
    if (position.data->messageType == Position::ESIdentificationAndCategory) {
        stream << position.data->callsign;
    } else if (position.data->messageType == Position::ESSurfacePositionMessage) {
        stream << position.data->altitude;
        stream << position.data->speed;
        stream << position.data->track;
        stream << position.data->latitude;
        stream << position.data->longitude;
    } else if (position.data->messageType == Position::ESAirbornePositionMessage) {
        stream << position.data->altitude;
        stream << position.data->latitude;
        stream << position.data->longitude;
    } else if (position.data->messageType == Position::ESAirborneVelocityMessage) {
        stream << position.data->speed;
        stream << position.data->track;
        stream << position.data->verticalRate;
    } else if (position.data->messageType == Position::SurveillanceAltMessage || position.data->messageType == Position::AirToAirMessage) {
        stream << position.data->altitude;
    } else if (position.data->messageType == Position::SurveillanceIDMessage) {
        stream << position.data->altitude;
        stream << position.data->squawk;
    } else if (position.data->messageType == Position::AllCallReply) {
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Position& position) {
    position = Position();

    stream >> position.data->reportingTime;
    stream >> position.data->messageType;
    if (position.data->messageType == Position::ESIdentificationAndCategory) {
        stream >> position.data->callsign;
    } else if (position.data->messageType == Position::ESSurfacePositionMessage) {
        stream >> position.data->altitude;
        stream >> position.data->speed;
        stream >> position.data->track;
        stream >> position.data->latitude;
        stream >> position.data->longitude;
    } else if (position.data->messageType == Position::ESAirbornePositionMessage) {
        stream >> position.data->altitude;
        stream >> position.data->latitude;
        stream >> position.data->longitude;
    } else if (position.data->messageType == Position::ESAirborneVelocityMessage) {
        stream >> position.data->speed;
        stream >> position.data->track;
        stream >> position.data->verticalRate;
    } else if (position.data->messageType == Position::SurveillanceAltMessage || position.data->messageType == Position::AirToAirMessage) {
        stream >> position.data->altitude;
    } else if (position.data->messageType == Position::SurveillanceIDMessage) {
        stream >> position.data->altitude;
        stream >> position.data->squawk;
    } else if (position.data->messageType == Position::AllCallReply) {
    }

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Position::MessageType& messageType) {
    stream << (quint8) messageType;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Position::MessageType& messageType) {
    quint8 messageTypeInt;

    stream >> messageTypeInt;

    messageType = static_cast<Position::MessageType>(messageTypeInt);

    return stream;
}

Position::~Position()
{
}

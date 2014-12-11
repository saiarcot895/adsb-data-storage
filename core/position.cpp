#include "position.h"
#include <QSharedData>
#include <QDataStream>

class PositionData : public QSharedData {
public:
    QDateTime reportingTime;
    QSet<Position::MessageType> messageTypes;
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

QSet<Position::MessageType> Position::getMessageTypes() const {
    return data->messageTypes;
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

void Position::addMessageType(MessageType messageType) {
    data->messageTypes.insert(messageType);
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
    stream << position.data->messageTypes;

    if (position.data->messageTypes.contains(Position::ESIdentificationAndCategory)) {
        stream << position.data->callsign;
    }
    if (position.data->messageTypes.contains(Position::SurveillanceAltMessage)
            || position.data->messageTypes.contains(Position::AirToAirMessage)
            || position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirbornePositionMessage)
            || position.data->messageTypes.contains(Position::SurveillanceIDMessage)) {
        stream << position.data->altitude;
    }
    if (position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirborneVelocityMessage)) {
        stream << position.data->speed;
        stream << position.data->track;
    }
    if (position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirbornePositionMessage)) {
        stream << position.data->latitude;
        stream << position.data->longitude;
    }
    if (position.data->messageTypes.contains(Position::ESAirborneVelocityMessage)) {
        stream << position.data->verticalRate;
    }
    if (position.data->messageTypes.contains(Position::SurveillanceIDMessage)) {
        stream << position.data->squawk;
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Position& position) {
    position = Position();

    stream >> position.data->reportingTime;
    stream >> position.data->messageTypes;

    if (position.data->messageTypes.contains(Position::ESIdentificationAndCategory)) {
        stream >> position.data->callsign;
    }
    if (position.data->messageTypes.contains(Position::SurveillanceAltMessage)
            || position.data->messageTypes.contains(Position::AirToAirMessage)
            || position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirbornePositionMessage)
            || position.data->messageTypes.contains(Position::SurveillanceIDMessage)) {
        stream >> position.data->altitude;
    }
    if (position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirborneVelocityMessage)) {
        stream >> position.data->speed;
        stream >> position.data->track;
    }
    if (position.data->messageTypes.contains(Position::ESSurfacePositionMessage)
            || position.data->messageTypes.contains(Position::ESAirbornePositionMessage)) {
        stream >> position.data->latitude;
        stream >> position.data->longitude;
    }
    if (position.data->messageTypes.contains(Position::ESAirborneVelocityMessage)) {
        stream >> position.data->verticalRate;
    }
    if (position.data->messageTypes.contains(Position::SurveillanceIDMessage)) {
        stream >> position.data->squawk;
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

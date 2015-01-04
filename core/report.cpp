#include "report.h"
#include <QSharedData>
#include <QDataStream>

class ReportData : public QSharedData {
public:
    QDateTime reportingTime;
    Report::MessageTypes messageTypes;
    qreal latitude = 0;
    qreal longitude = 0;
    qint32 altitude = 0;
    qint32 verticalRate = 0;
    quint16 speed = 0;
    quint16 track = 0;
    quint16 squawk = 0;
    QString callsign;
};

Report::Report() : data(new ReportData)
{
}

Report::Report(const Report &rhs) : data(rhs.data)
{
}

QDateTime Report::getReportingTime() const {
    return data->reportingTime;
}

Report::MessageTypes Report::getMessageTypes() const {
    return data->messageTypes;
}

qreal Report::getLatitude() const {
    return data->latitude;
}

qreal Report::getLongitude() const {
    return data->longitude;
}

qint32 Report::getAltitude() const {
    return data->altitude;
}

qint32 Report::getVerticalRate() const {
    return data->verticalRate;
}

quint16 Report::getSpeed() const {
    return data->speed;
}

quint16 Report::getTrack() const {
    return data->track;
}

quint16 Report::getSquawk() const {
    return data->squawk;
}

QString Report::getCallsign() const {
    return data->callsign;
}

void Report::setReportingTime(QDateTime reportingTime) {
    data->reportingTime = reportingTime;
}

void Report::addMessageType(MessageType messageType) {
    data->messageTypes |= messageType;
}

void Report::setCoordinates(qreal latitude, qreal longitude) {
    data->latitude = latitude;
    data->longitude = longitude;
}

void Report::setAltitude(qint32 altitude) {
    data->altitude = altitude;
}

void Report::setVerticalRate(qint32 verticalRate) {
    data->verticalRate = verticalRate;
}

void Report::setSpeed(quint16 speed) {
    data->speed = speed;
}

void Report::setTrack(quint16 track) {
    data->track = track;
}

void Report::setSquawk(quint16 squawk) {
    data->squawk = squawk;
}

void Report::setCallsign(QString callsign) {
    data->callsign = callsign;
}

Report &Report::operator=(const Report &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QDataStream& operator<<(QDataStream& stream, const Report& position) {
    stream << position.data->reportingTime;
    stream << position.data->messageTypes;

    if (position.data->messageTypes & Report::ESIdentificationAndCategory) {
        stream << position.data->callsign;
    }
    if (position.data->messageTypes & (Report::SurveillanceAltMessage
                                       | Report::AirToAirMessage | Report::ESSurfacePositionMessage
                                       | Report::ESAirbornePositionMessage
                                       | Report::SurveillanceIDMessage)) {
        stream << position.data->altitude;
    }
    if (position.data->messageTypes & (Report::ESSurfacePositionMessage | Report::ESAirborneVelocityMessage)) {
        stream << position.data->speed;
        stream << position.data->track;
    }
    if (position.data->messageTypes & (Report::ESSurfacePositionMessage | Report::ESAirbornePositionMessage)) {
        stream << position.data->latitude;
        stream << position.data->longitude;
    }
    if (position.data->messageTypes & Report::ESAirborneVelocityMessage) {
        stream << position.data->verticalRate;
    }
    if (position.data->messageTypes & Report::SurveillanceIDMessage) {
        stream << position.data->squawk;
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Report& position) {
    position = Report();

    int messageTypeFlags;

    stream >> position.data->reportingTime;
    stream >> messageTypeFlags;

    if (messageTypeFlags & Report::ESIdentificationAndCategory) {
        position.data->messageTypes |= Report::ESIdentificationAndCategory;
    }
    if (messageTypeFlags & Report::SurveillanceAltMessage) {
        position.data->messageTypes |= Report::SurveillanceAltMessage;
    }
    if (messageTypeFlags & Report::SurveillanceAltMessage) {
        position.data->messageTypes |= Report::SurveillanceAltMessage;
    }
    if (messageTypeFlags & Report::AirToAirMessage) {
        position.data->messageTypes |= Report::AirToAirMessage;
    }
    if (messageTypeFlags & Report::ESSurfacePositionMessage) {
        position.data->messageTypes |= Report::ESSurfacePositionMessage;
    }
    if (messageTypeFlags & Report::ESAirbornePositionMessage) {
        position.data->messageTypes |= Report::ESAirbornePositionMessage;
    }
    if (messageTypeFlags & Report::ESAirborneVelocityMessage) {
        position.data->messageTypes |= Report::ESAirborneVelocityMessage;
    }
    if (messageTypeFlags & Report::SurveillanceIDMessage) {
        position.data->messageTypes |= Report::SurveillanceIDMessage;
    }

    if (position.data->messageTypes & Report::ESIdentificationAndCategory) {
        stream >> position.data->callsign;
    }
    if (position.data->messageTypes & (Report::SurveillanceAltMessage
                                       | Report::AirToAirMessage | Report::ESSurfacePositionMessage
                                       | Report::ESAirbornePositionMessage
                                       | Report::SurveillanceIDMessage)) {
        stream >> position.data->altitude;
    }
    if (position.data->messageTypes & (Report::ESSurfacePositionMessage | Report::ESAirborneVelocityMessage)) {
        stream >> position.data->speed;
        stream >> position.data->track;
    }
    if (position.data->messageTypes & (Report::ESSurfacePositionMessage | Report::ESAirbornePositionMessage)) {
        stream >> position.data->latitude;
        stream >> position.data->longitude;
    }
    if (position.data->messageTypes & Report::ESAirborneVelocityMessage) {
        stream >> position.data->verticalRate;
    }
    if (position.data->messageTypes & Report::SurveillanceIDMessage) {
        stream >> position.data->squawk;
    }

    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Report::MessageType& messageType) {
    stream << (quint8) messageType;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Report::MessageType& messageType) {
    quint8 messageTypeInt;

    stream >> messageTypeInt;

    messageType = static_cast<Report::MessageType>(messageTypeInt);

    return stream;
}

Report::~Report()
{
}

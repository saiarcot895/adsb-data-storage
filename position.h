#ifndef POSITION_H
#define POSITION_H

#include <QObject>

#include <QExplicitlySharedDataPointer>
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

    enum MessageType {
        Unknown = 0,
        ESIdentificationAndCategory = 1,
        ESSurfacePositionMessage,
        ESAirbornePositionMessage,
        ESAirborneVelocityMessage,
        SurveillanceAltMessage,
        SurveillanceIDMessage,
        AirToAirMessage,
        AllCallReply
    };

    QDateTime getReportingTime() const;
    MessageType getMessageType() const;
    qreal getLatitude() const;
    qreal getLongitude() const;
    qint32 getAltitude() const;
    qint32 getVerticalRate() const;
    quint16 getSpeed() const;
    quint16 getTrack() const;
    quint16 getSquawk() const;
    QString getCallsign() const;

    void setReportingTime(QDateTime reportingTime);
    void setMessageType(MessageType mssageType);
    void setCoordinates(qreal latitude, qreal longitude);
    void setAltitude(qint32 altitude);
    void setVerticalRate(qint32 verticalRate);
    void setSpeed(quint16 speed);
    void setTrack(quint16 track);
    void setSquawk(quint16 squawk);
    void setCallsign(QString callsign);

    friend QDataStream& operator<<(QDataStream& stream, const Position& position);
    friend QDataStream& operator>>(QDataStream& stream, Position& position);
private:
    QExplicitlySharedDataPointer<PositionData> data;
};

QDataStream& operator<<(QDataStream& stream, const Position::MessageType& messageType);
QDataStream& operator>>(QDataStream& stream, Position::MessageType& messageType);

#endif // POSITION_H

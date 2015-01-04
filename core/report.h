#ifndef REPORT_H
#define REPORT_H

#include "core_global.h"

#include <QObject>

#include <QExplicitlySharedDataPointer>
#include <QDateTime>
#include <QSet>

class ReportData;

class CORESHARED_EXPORT Report : public QObject
{
public:
    Report();
    Report(const Report &);
    Report &operator=(const Report &);
    ~Report();

    enum MessageType {
        Unknown = 0,
        ESIdentificationAndCategory = 1 << 1,
        ESSurfacePositionMessage = 1 << 2,
        ESAirbornePositionMessage = 1 << 3,
        ESAirborneVelocityMessage = 1 << 4,
        SurveillanceAltMessage = 1 << 5,
        SurveillanceIDMessage = 1 << 6,
        AirToAirMessage = 1 << 7,
        AllCallReply = 1 << 8
    };
    Q_DECLARE_FLAGS(MessageTypes, MessageType)

    QDateTime getReportingTime() const;
    MessageTypes getMessageTypes() const;
    qreal getLatitude() const;
    qreal getLongitude() const;
    qint32 getAltitude() const;
    qint32 getVerticalRate() const;
    quint16 getSpeed() const;
    quint16 getTrack() const;
    quint16 getSquawk() const;
    QString getCallsign() const;

    void setReportingTime(QDateTime reportingTime);
    void addMessageType(MessageType messageType);
    void setCoordinates(qreal latitude, qreal longitude);
    void setAltitude(qint32 altitude);
    void setVerticalRate(qint32 verticalRate);
    void setSpeed(quint16 speed);
    void setTrack(quint16 track);
    void setSquawk(quint16 squawk);
    void setCallsign(QString callsign);

    friend CORESHARED_EXPORT QDataStream& operator<<(QDataStream& stream, const Report& position);
    friend CORESHARED_EXPORT QDataStream& operator>>(QDataStream& stream, Report& position);
private:
    QExplicitlySharedDataPointer<ReportData> data;
};

QDataStream& operator<<(QDataStream& stream, const Report::MessageType& messageType);
QDataStream& operator>>(QDataStream& stream, Report::MessageType& messageType);

Q_DECLARE_OPERATORS_FOR_FLAGS(Report::MessageTypes)

#endif // REPORT_H

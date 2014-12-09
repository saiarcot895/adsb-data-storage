#include "reader.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

Reader::Reader(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    timer(new QTimer(this))
{
    loadData();

    QObject::connect(timer, &QTimer::timeout, this, &Reader::saveData);
    timer->start(60000);

    QObject::connect(socket, &QTcpSocket::readyRead, this, &Reader::readData);
    socket->connectToHost("127.0.0.1", 30003, QIODevice::ReadOnly);
}

void Reader::loadData() {
    QFile file("adsbData.dat");
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QDataStream stream(&file);
        stream >> aircrafts;
        file.close();
    }
}

void Reader::readData() {
    while (socket->canReadLine()) {
        QString message = socket->readLine();
        const QStringList values = message.split(QChar(','));
        Position::MessageType messageType = static_cast<Position::MessageType>(values.at(1).toInt());
        quint32 hexCode = values.at(4).toInt(NULL, 16);
        if (!hexCode) {
            continue;
        }
        QDateTime reportingTime = QDateTime::fromString(values.at(6) + " " + values.at(7),
                                                        QStringLiteral("yyyy/MM/dd HH:mm:ss.zzz"));

        Aircraft aircraft = aircrafts.value(hexCode, Aircraft(hexCode));
        Position position;
        position.setReportingTime(reportingTime);
        position.setMessageType(messageType);

        if (messageType == Position::ESIdentificationAndCategory) {
            position.setCallsign(values.at(10));
        } else if (messageType == Position::ESSurfacePositionMessage) {
            position.setAltitude(values.at(11).toInt());
            position.setSpeed(values.at(12).toUShort());
            position.setTrack(values.at(13).toUShort());
            position.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == Position::ESAirbornePositionMessage) {
            position.setAltitude(values.at(11).toInt());
            position.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == Position::ESAirborneVelocityMessage) {
            position.setSpeed(values.at(12).toUShort());
            position.setTrack(values.at(13).toUShort());
            position.setVerticalRate(values.at(16).toInt());
        } else if (messageType == Position::SurveillanceAltMessage || messageType == Position::AirToAirMessage) {
            position.setAltitude(values.at(11).toInt());
        } else if (messageType == Position::SurveillanceIDMessage) {
            position.setAltitude(values.at(11).toInt());
            position.setSquawk(values.at(17).toUInt());
        }
        aircraft.addPosition(position);

        aircrafts.insert(hexCode, aircraft);
    }
}

void Reader::saveData() {
    QFile file("adsbData.dat");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&file);
    stream << aircrafts;
    file.close();
}

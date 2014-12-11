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

        Report::MessageType messageType = static_cast<Report::MessageType>(values.at(1).toInt());
        quint32 hexCode = values.at(4).toInt(NULL, 16);
        if (!hexCode) {
            continue;
        }

        QString date = values.at(6);
        QString time = values.at(7);
        time = time.remove(8, 4);
        QDateTime reportingTime = QDateTime::fromString(date + " " + time,
                                                        QStringLiteral("yyyy/MM/dd HH:mm:ss"));
        reportingTime.toTimeSpec(Qt::LocalTime);

        Aircraft aircraft = aircrafts.value(hexCode, Aircraft(hexCode));
        Report report = aircraft.getReports(reportingTime);
        report.setReportingTime(reportingTime);
        report.addMessageType(messageType);

        if (messageType == Report::ESIdentificationAndCategory) {
            report.setCallsign(values.at(10));
        } else if (messageType == Report::ESSurfacePositionMessage) {
            report.setAltitude(values.at(11).toInt());
            report.setSpeed(values.at(12).toUShort());
            report.setTrack(values.at(13).toUShort());
            report.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == Report::ESAirbornePositionMessage) {
            report.setAltitude(values.at(11).toInt());
            report.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == Report::ESAirborneVelocityMessage) {
            report.setSpeed(values.at(12).toUShort());
            report.setTrack(values.at(13).toUShort());
            report.setVerticalRate(values.at(16).toInt());
        } else if (messageType == Report::SurveillanceAltMessage || messageType == Report::AirToAirMessage) {
            report.setAltitude(values.at(11).toInt());
        } else if (messageType == Report::SurveillanceIDMessage) {
            report.setAltitude(values.at(11).toInt());
            report.setSquawk(values.at(17).toUInt());
        }
        aircraft.addReport(report);

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

#include "reader.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

Reader::Reader(QString host, quint16 port, double offset, QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    timer(new QTimer(this)),
    currentDate(QDate()),
    host(host),
    port(port),
    offset(offset)
{
    loadData();

    connect(timer, &QTimer::timeout, this, &Reader::saveData);
    timer->start(60000);

    connect(socket, &QTcpSocket::readyRead, this, &Reader::readData);
    connect(socket, &QTcpSocket::disconnected, this, &Reader::reconnect);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(reconnect()));
    socket->connectToHost(host, port, QIODevice::ReadOnly);
}

void Reader::loadData() {
    if (!currentDate.isValid()) {
        currentDate = QDate::currentDate();
    }
    QFile file(QString("adsbData.%1.dat").arg(currentDate.toString(Qt::ISODate)));
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
        if (message == QStringLiteral("\r\n")) {
            return;
        }

        const QStringList values = message.split(QChar(','));
        if (values.length() < 18) {
            qWarning() << "Invalid message:" << message;
            continue;
        }

        Report::MessageType messageType = static_cast<Report::MessageType>(1 << values.at(1).toInt());
        quint32 hexCode = values.at(4).toInt(NULL, 16);
        if (!hexCode) {
            continue;
        }

        QString date = values.at(6);
        QString time = values.at(7);
        time = time.remove(8, 4);
        QDateTime reportingTime = QDateTime::fromString(date + " " + time,
                                                        QStringLiteral("yyyy/MM/dd HH:mm:ss"));
        reportingTime = reportingTime.addMSecs(-offset * 3600 * 1000);
        reportingTime.setTimeSpec(Qt::UTC);

        if (!currentDate.isValid() || reportingTime.date() != currentDate) {
            saveData();
            aircrafts.clear();
            currentDate = reportingTime.date();
        }

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
    if (!currentDate.isValid()) {
        return;
    }
    QFile file(QString("adsbData.%1.dat").arg(currentDate.toString(Qt::ISODate)));
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QDataStream stream(&file);
        stream << aircrafts;
        file.close();
    }
}

void Reader::reconnect() {
    if (socket->state() != QAbstractSocket::ConnectedState) {
        QTimer::singleShot(10000, Qt::CoarseTimer, this, SLOT(doReconnection()));
    }
}

void Reader::doReconnection() {
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socket->connectToHost(host, port, QIODevice::ReadOnly);
    }
}

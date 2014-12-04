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

    connect(timer, SIGNAL(timeout()), this, SLOT(saveData()));
    timer->start(30000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
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
        int messageType = values.at(1).toInt();
        quint32 hexCode = values.at(4).toInt(NULL, 16);
        QDateTime reportingTime = QDateTime::fromString(values.at(6) + " " + values.at(7),
                                                        QStringLiteral("yyyy/MM/dd HH:mm:ss.zzz"));

        Aircraft aircraft = aircrafts.value(hexCode, Aircraft(hexCode));
        Position position;
        position.setReportingTime(reportingTime);

        if (messageType == 2) {
            position.setAltitude(values.at(11).toInt());
            position.setSpeed(values.at(12).toUInt());
            position.setTrack(values.at(13).toUInt());
            position.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == 3) {
            position.setAltitude(values.at(11).toInt());
            position.setCoordinates(values.at(14).toDouble(), values.at(15).toDouble());
        } else if (messageType == 5 || messageType == 7) {
            position.setAltitude(values.at(11).toInt());
        } else if (messageType == 6) {
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

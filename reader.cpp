#include "reader.h"
#include <QDebug>

Reader::Reader(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost("127.0.0.1", 30003, QIODevice::ReadOnly);
}

void Reader::readData() {
    while (socket->canReadLine()) {
        QString message = socket->readLine();
        const QStringList values = message.split(QChar(','));
        int messageType = values.at(1).toInt();
        quint32 hexCode = values.at(4).toInt(NULL, 16);
        QDateTime reportingTime = QDateTime::fromString(values.at(6) + " " + values.at(7),
                                                        QStringLiteral("yyyy/MM/dd HH:mm:ss"));

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

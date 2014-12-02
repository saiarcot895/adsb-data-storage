#include "reader.h"
#include <QDebug>

Reader::Reader(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost("192.168.0.1", 30003, QIODevice::ReadOnly);
}

void Reader::readData() {
    while (socket->canReadLine()) {
        QString message = socket->readLine();
        qDebug() << message;
    }
}

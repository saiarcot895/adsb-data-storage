#ifndef READER_H
#define READER_H

#include "aircraft.h"

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <QTimer>

#define MAGIC_BYTES 0xAD8BDA7A

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QString host, quint16 port, double offset, QObject *parent = 0);

private slots:
    void readData();
    void saveData();
    void reconnect();
    void doReconnection();
private:
    QTcpSocket* socket;
    QMap<quint32, Aircraft> aircrafts;
    QTimer* timer;
    QDate currentDate;
    QString host;
    quint16 port;
    double offset;

    void loadData();

};

#endif // READER_H

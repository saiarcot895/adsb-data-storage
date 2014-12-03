#ifndef READER_H
#define READER_H

#include "aircraft.h"

#include <QObject>
#include <QTcpSocket>
#include <QMap>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);

private slots:
    void readData();
private:
    QTcpSocket* socket;
    QMap<quint32, Aircraft> aircrafts;

};

#endif // READER_H

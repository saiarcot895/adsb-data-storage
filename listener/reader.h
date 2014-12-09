#ifndef READER_H
#define READER_H

#include "aircraft.h"

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <QTimer>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);

private slots:
    void readData();
    void saveData();
private:
    QTcpSocket* socket;
    QMap<quint32, Aircraft> aircrafts;
    QTimer* timer;

    void loadData();

};

#endif // READER_H

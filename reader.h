#ifndef READER_H
#define READER_H

#include <QObject>
#include <QTcpSocket>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);

private slots:
    void readData();
private:
    QTcpSocket* socket;

};

#endif // READER_H

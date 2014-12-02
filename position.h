#ifndef POSITION_H
#define POSITION_H

#include <QObject>

#include <QSharedDataPointer>
#include <QDateTime>
#include <QtPositioning/QGeoCoordinate>

class PositionData;

class Position : public QObject
{
public:
    Position();
    Position(const Position &);
    Position &operator=(const Position &);
    ~Position();

private:
    QSharedDataPointer<PositionData> data;
};

#endif // POSITION_H

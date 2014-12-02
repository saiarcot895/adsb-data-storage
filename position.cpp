#include "position.h"
#include <QSharedData>

class PositionData : public QSharedData {
public:
    QDateTime reportingTime;
    QGeoCoordinate coordinate;
    quint32 speed;
    quint32 track;
    quint16 squawk;
};

Position::Position() : data(new PositionData)
{
}

Position::Position(const Position &rhs) : data(rhs.data)
{
}

Position &Position::operator=(const Position &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Position::~Position()
{
}

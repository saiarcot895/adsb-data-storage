#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include "report.h"

class ReportModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ReportModel(QList<Report> reports, QObject *parent = 0);

    enum Roles {
        ReportingTime,
        MessageType,
        Latitude,
        Longitude,
        Altitude,
        VerticalRate,
        Speed,
        Track,
        Squawk,
        Callsign
    };

    void setReports(QList<Report> reports);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QVariant data(int row, QString role) const;
private:
    QList<Report> reports;

};

#endif // REPORTMODEL_H

#include "reportmodel.h"

ReportModel::ReportModel(QList<Report> reports, QObject *parent) :
    QAbstractListModel(parent),
    reports(reports)
{
}

void ReportModel::setReports(QList<Report> positions) {
    emit layoutAboutToBeChanged();
    this->reports = positions;
    emit layoutChanged();
}

QHash<int, QByteArray> ReportModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ReportModel::ReportingTime] = "reportingTime";
    roles[ReportModel::MessageType] = "messageType";
    roles[ReportModel::Latitude] = "latitude";
    roles[ReportModel::Longitude] = "longitude";
    roles[ReportModel::Altitude] = "altitude";
    roles[ReportModel::VerticalRate] = "verticalRate";
    roles[ReportModel::Speed] = "speed";
    roles[ReportModel::Track] = "track";
    roles[ReportModel::Squawk] = "squawk";
    return roles;
}

int ReportModel::rowCount(const QModelIndex &parent) const {
    return reports.size();
}

QVariant ReportModel::data(const QModelIndex &index, int role) const {
    const Report report = reports.at(index.row());
    if (role == ReportModel::ReportingTime) {
        return report.getReportingTime();
    } else if (role == ReportModel::MessageType) {
        QList<Report::MessageType> messageTypes = report.getMessageTypes().toList();
        QString messageTypeString;
        for (int i = 0; i < messageTypes.size(); i++) {
            messageTypeString += QString::number(messageTypes.at(i));
            if (i != messageTypes.size() - 1) {
                messageTypeString += ", ";
            }
        }
        return messageTypeString;
    } else if (role == ReportModel::Latitude) {
        return report.getLatitude();
    } else if (role == ReportModel::Longitude) {
        return report.getLongitude();
    } else if (role == ReportModel::Altitude) {
        return report.getAltitude();
    }
    return QVariant();
}

QVariant ReportModel::data(int row, QString role) const {
    const QHash<int, QByteArray> roles = roleNames();
    int roleInt = roles.key(role.toLocal8Bit());
    return data(index(row), roleInt);
}

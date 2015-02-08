#include "mainwindow.h"
#include <QQmlContext>
#include <QQmlComponent>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QObject *parent) :
    QObject(parent),
    engine(new QQmlApplicationEngine(this))
{
    loadData();

    engine->rootContext()->setContextProperty("mainWindow", this);
    engine->rootContext()->setContextProperty("aircraftModel", aircraftModel);
    engine->rootContext()->setContextProperty("positionModel", reportModel);
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    rootObject = component.create();
}

void MainWindow::loadData() {
    QDir directory = QDir::current();
    directory.setFilter(QDir::Files);
    directory.setSorting(QDir::Name);
    QStringList filters;
    filters << "adsbData.*.dat";
    directory.setNameFilters(filters);

    QStringList files = directory.entryList();
    for (int i = 0; i < files.size(); i++) {
        QMap<quint32, Aircraft> localAircrafts;

        QFile file(directory.absolutePath() + "/" + files.at(i));
        file.open(QIODevice::ReadOnly);
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_0);
        quint32 magicBytes;
        stream >> magicBytes;
        if (magicBytes != MAGIC_BYTES) {
            //qCritical() << "Invalid file header for" << files.at(i);
            file.close();
            continue;
        }
        quint16 dataVersionInt;
        stream >> dataVersionInt;
        Aircraft::setDataVersion(static_cast<Aircraft::Version>(dataVersionInt));
        stream >> localAircrafts;
        file.close();

        const QList<Aircraft> localAircraftValues = localAircrafts.values();
        for (int j = 0; j < localAircraftValues.size(); j++) {
            Aircraft aircraft = localAircraftValues.at(j);
            if (aircrafts.contains(aircraft.getHexCode())) {
                aircraft = aircrafts.value(aircraft.getHexCode()) + aircraft;

            }
            aircrafts.insert(aircraft.getHexCode(), aircraft);
        }
    }

    aircraftModel = new AircraftModel(aircrafts.values());
    reportModel = new ReportModel(QList<Report>());
}

void MainWindow::displayAircraftHistory(int index) {
    Aircraft aircraft = aircrafts.values().at(index);
    reportModel->setReports(aircraft.getReports());
}

#include "mainwindow.h"
#include <QQmlContext>
#include <QQmlComponent>
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
    engine->rootContext()->setContextProperty("positionModel", positionModel);
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    rootObject = component.create();
}

void MainWindow::loadData() {
    QFile file("adsbData.dat");
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QDataStream stream(&file);
        stream >> aircrafts;
        file.close();
    }

    aircraftModel = new AircraftModel(aircrafts.values());
    positionModel = new PositionModel(QList<Position>());
}

void MainWindow::displayAircraftHistory(int index) {
    Aircraft aircraft = aircrafts.values().at(index);
    positionModel->setPositions(aircraft.getPositionData());
    engine->rootContext()->setContextProperty("positionModel", NULL);
    engine->rootContext()->setContextProperty("positionModel", positionModel);
}

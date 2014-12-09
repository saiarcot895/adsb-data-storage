#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QMap>
#include "aircraft.h"
#include "aircraftmodel.h"
#include "positionmodel.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);

    Q_INVOKABLE void displayAircraftHistory(int index);

private:
    QQmlApplicationEngine* engine;
    QObject* rootObject;
    QMap<quint32, Aircraft> aircrafts;
    AircraftModel* aircraftModel;
    PositionModel* positionModel;

    void loadData();

};

#endif // MAINWINDOW_H

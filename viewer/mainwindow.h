#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QMap>
#include "aircraft.h"
#include "aircraftmodel.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);

private:
    QQmlApplicationEngine* engine;
    QObject* rootObject;
    QMap<quint32, Aircraft> aircrafts;
    AircraftModel* aircraftModel;

    void loadData();

};

#endif // MAINWINDOW_H

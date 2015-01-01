#include <QCoreApplication>
#include <QCommandLineParser>
#include "reader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("ADS-B data recorder");
    parser.addHelpOption();

    QCommandLineOption hostOption("host",
                                  QStringLiteral("Set the hostname of the ADS-B receiver."),
                                  QStringLiteral("hostname"),
                                  QStringLiteral("localhost"));
    parser.addOption(hostOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  QStringLiteral("Set the port to listen on."),
                                  QStringLiteral("port"),
                                  QStringLiteral("30003"));
    parser.addOption(portOption);

    QCommandLineOption offsetOption("offset",
                                    QStringLiteral("Set the offset from UTC (in hours) of the times being received from the receiver."),
                                    QStringLiteral("offset"),
                                    QStringLiteral("0"));
    parser.addOption(offsetOption);

    // Process the actual command line arguments given by the user
    parser.process(a);

    QString host = parser.value(hostOption);
    bool* validPort;
    quint16 port = parser.value(portOption).toUShort(validPort);
    if (!*validPort || !port) {
        return 2;
    }
    int offset = parser.value(offsetOption).toInt();

    Reader reader(host, port, offset);

    return a.exec();
}

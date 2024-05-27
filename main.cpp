#include <QCoreApplication>
#include "pump.h"
#include <QObject>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Pump pump(&a);
    QObject::connect(&pump.m_runTimer,&QTimer::timeout,&pump,&Pump::machineDataChange);
    // QObject::connect(&pump.m_runTimer,&QTimer::timeout,&pump,&Pump::funcPower);
    // QObject::connect(&pump.m_runTimer,&QTimer::timeout,&pump,&Pump::funcSpeed);
    QObject::connect(&pump.m_runTimer,&QTimer::timeout,&pump,&Pump::TimeOut);
    QObject::connect(&pump.m_standbyTimer,&QTimer::timeout,&pump,&Pump::machineDataChange);
    // QObject::connect(&pump.m_standbyTimer,&QTimer::timeout,&pump,&Pump::funcPower);
    // QObject::connect(&pump.m_standbyTimer,&QTimer::timeout,&pump,&Pump::funcSpeed);
    return a.exec();
}

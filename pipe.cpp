#include "pipe.h"
#include <QMutexLocker>
Pipe::Pipe(QObject *parent,qfloat16 pressure)
    : QObject{parent} , m_pressure(pressure)
{}

qfloat16 Pipe::getPressure() const
{
    QMutexLocker lock(&m_mtx);
    return m_pressure;
}

void Pipe::setPressure(qfloat16 newPressure)
{
    QMutexLocker lock(&m_mtx);
    m_pressure = newPressure;
}

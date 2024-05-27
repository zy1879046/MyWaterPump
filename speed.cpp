#include "speed.h"

Speed::Speed(QObject *parent,qfloat16 speed)
    : QObject{parent},m_speed(speed)
{}

void Speed::setSpeed(qfloat16 newSpeed)
{
    QMutexLocker lock(&m_mtx);
    m_speed = newSpeed;
}

qfloat16 Speed::getSpeed() const
{
    QMutexLocker lock(&m_mtx);
    return m_speed;
}

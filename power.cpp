#include "power.h"

Power::Power(QObject *parent,qfloat16 power)
    : QObject{parent},m_power(power)
{}

void Power::setPower(qfloat16 newPower)
{
    QMutexLocker lock(&m_mtx);
    m_power = newPower;
}

qfloat16 Power::getPower() const
{
    QMutexLocker lock(&m_mtx);
    return m_power;
}

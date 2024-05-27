#include "switch.h"
#include <QMutexLocker>
Switch::Switch(QObject *parent,SWITCH::STATE state)
    : QObject{parent},m_state(state)
{}

SWITCH::STATE Switch::getState() const
{
    QMutexLocker lock(&m_mtx);
    return m_state;
}

void Switch::setState(SWITCH::STATE newState)
{
    QMutexLocker lock(&m_mtx);
    m_state = newState;
}

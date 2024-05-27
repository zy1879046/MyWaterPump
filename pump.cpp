#include "pump.h"
#include <QDebug>
Pump::Pump(QObject *parent)
    : QObject{parent}
{
    m_pipe = std::make_shared<Pipe>(this);
    m_speed = std::make_shared<Speed>(this);
    m_switch = std::make_shared<Switch>(this);
    m_power = std::make_shared<Power>(this);
    setState(PUMP::STANDBY);
    m_standbyTimer.start(100);
    m_standbyElapseTimer.start();
}

void Pump::funcPipe()
{
    if(getState() == PUMP::STANDBY){
        double t = standByTime();
        double press = linerInterpolation(t,m_pipe->getPressure(),m_pipe->MinPressure,m_pipe->StandbyNeed);
        m_pipe->setPressure(press);
        if(m_switch->getState() == SWITCH::OPEN && press <= m_pipe->Threshold)
            setState(PUMP::RUNNING);
    }else if(getState() == PUMP::RUNNING){
        double t = runningTime();
        double press = linerInterpolation(t,m_pipe->getPressure(),m_pipe->MaxPressure,m_pipe->RunningNeed);
        m_pipe->setPressure(press);
    }

    qDebug() << "cuurent Pressure: " << m_pipe->getPressure() << " MPa";
}

void Pump::funcSpeed()
{
    if(getState() == PUMP::STANDBY){
        double t = standByTime();
        double speed = linerInterpolation(t,m_speed->getSpeed(),m_speed->MinSpeed,m_speed->FallTime);
        m_speed->setSpeed(speed);
    }else if(getState() == PUMP::RUNNING){
        double t = runningTime();
        double speed = linerInterpolation(t,m_speed->getSpeed(),m_speed->MaxSpeed,m_speed->RiseTime);
        m_speed->setSpeed(speed);
    }
    qDebug() << "cuurent Speed: " << m_speed->getSpeed() << " rad/s";
}

void Pump::funcPower()
{
    if(getState() == PUMP::STANDBY){
        double t = standByTime();
        double power = linerInterpolation(t,m_power->getPower(),m_power->MinPower,m_power->FallTime);
        m_power->setPower(power);
    }else if(getState() == PUMP::RUNNING){
        double t = runningTime();
        double power = linerInterpolation(t,m_power->getPower(),m_power->MaxPower,m_power->RiseTime);
        m_power->setPower(power);
    }
    qDebug() << "cuurent Power: " << m_power->getPower() << " Hz";
}

void Pump::funcSwitch()
{
    //监听从前端来的开关变化的状态
    // newState =
    //状态变换
    // m_switch->setState(newState);
}

void Pump::TimeOut()
{
    if(m_switch->getState() == SWITCH::OPEN && runningTime() >= AutoTime){
        setState(PUMP::STANDBY);
    }
}

PUMP::STATE Pump::getState() const
{
    QMutexLocker lock(&m_mtx);
    return m_state;
}

void Pump::setState(PUMP::STATE newState)
{
    QMutexLocker lock(&m_mtx);
    //变为待机态时计时器和定时器的变化
    if(m_state == PUMP::RUNNING && newState == PUMP::STANDBY){
        m_runTimer.stop();
        m_runElapseTimer.invalidate();
        m_standbyTimer.start(interval);
        m_standbyElapseTimer.start();
    }
    m_state = newState;
    qDebug() << "Pump state set to:" << newState;
    //刚变为运行态时计时器和定时器的变化
    if(m_state == PUMP::RUNNING && !m_runTimer.isActive()){
        m_standbyTimer.stop();
        m_standbyElapseTimer.invalidate();
        m_runTimer.start(interval);
        m_runElapseTimer.start();
    }
}

double Pump::standByTime() const
{
    return m_standbyElapseTimer.elapsed() / 1000.0;
}

double Pump::runningTime() const
{
    return m_runElapseTimer.elapsed() /1000.0;
}

double Pump::linerInterpolation(double t, double initial , double final,double duration)
{
    if(t <= 0){
        return initial;
    }else if(t >= duration){
        return final;
    }else{
        return initial + (final - initial) * (t / duration);
    }
}

void Pump::machineDataChange()
{
    funcPipe();
    funcSpeed();
    funcPower();
    m_send_data.reset(new data(m_switch->getState(),getState(),m_power->getPower(),m_speed->getSpeed(),m_pipe->getPressure()));
    //将数据发送出去

}

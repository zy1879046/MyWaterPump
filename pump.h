#ifndef PUMP_H
#define PUMP_H

#include <QObject>
#include "pipe.h"
#include "speed.h"
#include "power.h"
#include "switch.h"
#include <QTimer>

// 水泵的状态
struct PUMP{
    enum STATE{
        STANDBY = 0, //表示待机
        RUNNING = 1,//表示运行中
        ERROR = 2 //表示故障
    };
};

struct data{
    using ptr = std::shared_ptr<data>;
    explicit data(SWITCH::STATE switch_state,PUMP::STATE pump_state,double power,double speed,double press)
        : m_switch_state(switch_state),m_pump_state(pump_state),m_power(power),m_speed(speed),m_press(press)
    {}
    SWITCH::STATE m_switch_state;
    PUMP::STATE m_pump_state;
    double m_power;
    double m_speed;
    double m_press;
};

class Pump : public QObject
{
    Q_OBJECT

    const qint64 interval = 200;
    const double AutoTime = 120;
public:
    explicit Pump(QObject *parent = nullptr);

    //该函数用来监听开关状态变化
    void funcSwitch();
    void funcPipe();
    void funcSpeed();
    void funcPower();
    PUMP::STATE getState() const;
    void setState(PUMP::STATE newState);

private:
    //计算当前待机的时间
    double standByTime()const;
    //计算当前运行时间
    double runningTime()const;
    // 线性差值计算当前水管压力下降到的位置
    double linerInterpolation(double t, double initial, double final, double duration);
public:
    QTimer m_runTimer;//运行定时器
    QElapsedTimer m_runElapseTimer;//运行态计时器
    QTimer m_standbyTimer;//待机时定时器
    QElapsedTimer m_standbyElapseTimer; //待机时计时器
private:
    mutable QMutex m_mtx;
    Pipe::ptr m_pipe;
    Speed::ptr m_speed;
    Power::ptr m_power;
    Switch::ptr m_switch;
    PUMP::STATE m_state = PUMP::STANDBY;
    data::ptr m_send_data;

signals:

public slots:
    void machineDataChange();
    void TimeOut();
};

#endif // PUMP_H

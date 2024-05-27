#ifndef POWER_H
#define POWER_H

#include <QObject>
#include <QMutex>
#include <memory>
class Power : public QObject
{
    Q_OBJECT
public:
    using ptr = std::shared_ptr<Power>;
    const double MaxPower = 50;
    const double MinPower = 0;
    const double RiseTime = 30;
    const double FallTime = 5;
public:
    explicit Power(QObject *parent = nullptr,qfloat16 power = 0);

    void setPower(qfloat16 newPower);
    qfloat16 getPower()const;
private:
    qfloat16 m_power;
    mutable QMutex m_mtx;
signals:
};

#endif // POWER_H

#ifndef SPEED_H
#define SPEED_H

#include <QObject>
#include <QMutex>
class Speed : public QObject
{
    Q_OBJECT
public:
    using ptr = std::shared_ptr<Speed>;
    const double MaxSpeed = 2000;
    const double MinSpeed = 0;
    const double RiseTime = 30;
    const double FallTime = 5;
public:
    explicit Speed(QObject *parent = nullptr,qfloat16 speed = 0);

    void setSpeed(qfloat16 newSpeed);
    qfloat16 getSpeed()const;
private:
    qfloat16 m_speed;
    mutable QMutex m_mtx;
signals:
};

#endif // SPEED_H

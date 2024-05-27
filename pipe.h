#ifndef PIPE_H
#define PIPE_H

#include <QObject>
#include <QMutex>
#include <memory>
class Pipe : public QObject
{
    Q_OBJECT
public:
    using ptr = std::shared_ptr<Pipe>;
    const double MinPressure = 0.1;
    const double MaxPressure = 2;
    const double Threshold = 0.2;
    const double StandbyNeed = 10;
    const double RunningNeed = 20;
public:
    explicit Pipe(QObject *parent = nullptr,qfloat16 pressure = 1);

    qfloat16 getPressure() const;
    void setPressure(qfloat16 newPressure);

private:
    mutable QMutex m_mtx;
    qfloat16 m_pressure;
signals:
};

#endif // PIPE_H

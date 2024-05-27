#ifndef SWITCH_H
#define SWITCH_H

#include <QObject>
#include <QMutex>
#include <memory>
struct SWITCH{
    enum STATE{
        CLOSE = 0,
        OPEN = 1
    };
};

class Switch : public QObject
{
    Q_OBJECT
public:
    using ptr = std::shared_ptr<Switch>;
public:
    explicit Switch(QObject *parent = nullptr,SWITCH::STATE state = SWITCH::OPEN);

    SWITCH::STATE getState() const;
    void setState(SWITCH::STATE newState);
private:
    mutable QMutex m_mtx;
    SWITCH::STATE m_state;
signals:
};

#endif // SWITCH_H

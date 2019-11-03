#ifndef SYSTEMCMD_H
#define SYSTEMCMD_H

#include <QObject>
#include <QProcess>

class SystemCmd: public QObject
{
    Q_OBJECT
public:
    SystemCmd();
    void start();
    QProcess process_;

signals:

public slots:
    void readOutput();
    void readErrors();
};

#endif // SYSTEMCMD_H

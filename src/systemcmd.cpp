#include "systemcmd.h"
#include <QString>
#include "log.h"

SystemCmd::SystemCmd()
{
    // Signals
    connect( &process_,
             SIGNAL( readyReadStandardOutput() ),
            this, SLOT ( readOutput()) );

    connect( &process_,
             SIGNAL( readyReadStandardError() ),
            this, SLOT ( readErrors()) );

    connect(&process_, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exitCode, QProcess::ExitStatus exitStatus)
    {
        LOG(logWARNING) << "process finished=" << exitCode;
    });

    //QProcess process;


    //process.waitForFinished(-1); // will wait forever until finished


    //SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput())
}

void SystemCmd::start()
{
    process_.start("ssh ubuntu@192.168.0.103 -x \"journalctl -b\"");
}

void SystemCmd::readOutput()
{
    QString stdoutdata = process_.readAllStandardOutput();
    LOG(logWARNING) << "process output=" << stdoutdata.toStdString();
}

void SystemCmd::readErrors()
{
    QString stdoutdata = process_.readAllStandardError();
    LOG(logWARNING) << "process errors=" << stdoutdata.toStdString();
}

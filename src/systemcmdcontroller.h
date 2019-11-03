#ifndef SYSTEMCMDCONTROLLER_H
#define SYSTEMCMDCONTROLLER_H

#include <QMap>
#include "systemcmd.h"
#include "systemcmdstorage.h"

class SystemCmdController
{
public:
    SystemCmdController();
private:
    struct SysCmdDataClip
    {
        SystemCmdStorage::SystemCmdData data;
        SystemCmd process;
    };

    QMap<QString,SysCmdDataClip> mSysCmds;
};

#endif // SYSTEMCMDCONTROLLER_H

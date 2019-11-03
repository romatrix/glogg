#include "systemcmdstorage.h"
#include "persistentinfo.h"
#include "log.h"

SystemCmdStorage::SystemCmdStorage()
{

}

void SystemCmdStorage::saveToStorage(QSettings &settings) const
{
    LOG(logDEBUG) << __PRETTY_FUNCTION__;

    settings.beginGroup( "SystemCmdStorage" );
    // Remove everything in case the array is shorter than the previous one
    settings.remove("");
    settings.setValue( "version", VERSION );
    settings.beginWriteArray( "sessions" );

    const QList<QString> names = getNames();

    for (int i = 0; i < names.count(); ++i) {
        settings.setArrayIndex(i);
        mCommands[names[i]].saveToStorage( settings );
    }
    settings.endArray();
    settings.endGroup();
}

void SystemCmdStorage::retrieveFromStorage(QSettings &settings)
{
    LOG(logDEBUG) << __PRETTY_FUNCTION__;

    mCommands.clear();

    if ( settings.contains( "SystemCmdStorage/version" ) ) {
        settings.beginGroup( "SystemCmdStorage" );
        const int ver = settings.value( "version" ).toInt();
        if ( VERSION == ver) {
            int size = settings.beginReadArray( "sessions" );

            for (int i = 0; i < size; ++i) {
                settings.setArrayIndex(i);
                SystemCmdData scd;
                scd.retrieveFromStorage(settings);
                mCommands[scd.name] = scd;
            }

            settings.endArray();
        }
        else {
            LOG(logERROR) << "Unknown version of SystemCmdStorage, ignoring it...";
        }
        settings.endGroup();
    }
}

bool SystemCmdStorage::addCommand(const SystemCmdStorage::SystemCmdData &cmd)
{
    if(mCommands.contains(cmd.name)){
        return false;
    } else {
        mCommands[cmd.name] = cmd;
        return true;
    }
}

bool SystemCmdStorage::removeCommand(const QString &cmd)
{
    if(mCommands.contains(cmd)){
        mCommands.remove(cmd);
        return true;
    } else {
        return false;
    }
}

bool SystemCmdStorage::updateCommand(const SystemCmdStorage::SystemCmdData &cmd)
{
    if(mCommands.contains(cmd.name)){
        mCommands[cmd.name] = cmd;
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<SystemCmdStorage> SystemCmdStorage::getStoredInstance()
{
    std::shared_ptr<SystemCmdStorage> systeSessionInfomCmdStorage =
        Persistent<SystemCmdStorage>( "systemCmdStorage" );

    systeSessionInfomCmdStorage->load();

    return systeSessionInfomCmdStorage;
}

void SystemCmdStorage::save()
{
    GetPersistentInfo().save( QString( "systemCmdStorage" ) );
}

void SystemCmdStorage::load()
{
    GetPersistentInfo().retrieve(QString( "systemCmdStorage" ));
}

void SystemCmdStorage::SystemCmdData::saveToStorage(QSettings &settings) const
{
    LOG(logDEBUG) << __PRETTY_FUNCTION__;

    settings.setValue( "name", name );
    settings.setValue( "command", command );
    settings.setValue( "regex", regex );
    settings.setValue( "repeatAtFail", repeatAtFail );
    settings.setValue( "append", append );
    settings.setValue( "keepLog", keepLog);
}

void SystemCmdStorage::SystemCmdData::retrieveFromStorage(QSettings &settings)
{
    LOG(logDEBUG) << __PRETTY_FUNCTION__;

    name = settings.value("name").toString();
    command = settings.value("command").toString();
    regex = settings.value("regex").toString();
    repeatAtFail = settings.value("regex").toBool();
    append = settings.value("append").toBool();
    keepLog = settings.value("keepLog").toBool();
}

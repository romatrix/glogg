#ifndef SYSTEMCMDSTORAGE_H
#define SYSTEMCMDSTORAGE_H

#include <QString>
#include <QMap>
#include <QList>
#include "persistable.h"
#include <memory>

class SystemCmdStorage: public Persistable
{
public:
    SystemCmdStorage();
    virtual ~SystemCmdStorage() = default;
    static std::shared_ptr<SystemCmdStorage> getStoredInstance();
    void save();
    void load();

    void saveToStorage(QSettings &settings) const;
    void retrieveFromStorage(QSettings &settings);

    static constexpr int VERSION = 1;

    QString mDirectory;
    struct SystemCmdData: public Persistable
    {
        QString name;
        QString command;
        QString regex;
        bool repeatAtFail;
        bool append;
        bool keepLog;

        // Persistable interface
    public:
        void saveToStorage(QSettings &settings) const;
        void retrieveFromStorage(QSettings &settings);
    };

    bool addCommand(const SystemCmdData& cmd);
    bool removeCommand(const QString &cmd);
    bool updateCommand(const SystemCmdData& cmd);
    int getCommandCount() const { return mCommands.size(); }
    const SystemCmdData getCommand(const QString& name) const { return mCommands[name]; }
    const QList<QString> getNames() const { return mCommands.keys(); }

    QMap<QString, SystemCmdData> mCommands;

    // Persistable interface
public:
};

#endif // SYSTEMCMDSTORAGE_H

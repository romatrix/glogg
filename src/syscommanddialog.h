#ifndef SYSCOMMANDDIALOG_H
#define SYSCOMMANDDIALOG_H

#include <QDialog>
#include "ui_syscommanddialog.h"
#include <QMap>
#include <QString>
#include "systemcmdstorage.h"
#include <boost/optional.hpp>

class SysCommandDialog : public QDialog, private Ui::SysCommandDialog
{
    Q_OBJECT
public:
    explicit SysCommandDialog(QDialog *parent = nullptr);

signals:

public slots:
private slots:
    void on_OkCloseButtonBox_accepted();
    void on_OkCloseButtonBox_rejected();
    void on_executeButton_clicked();
    void on_regexButton_clicked();
    void on_directoryButton_clicked();
    void on_addCommandButton_clicked();
    void on_removeCommandButton_clicked();
    void on_runButton_clicked();
    void on_commandListWidget_currentRowChanged(int currentRow);

private:
    SystemCmdStorage::SystemCmdData getFormData();
    void setFormData(const SystemCmdStorage::SystemCmdData &cmd);

    std::shared_ptr<SystemCmdStorage> mCmdStorage;
    boost::optional<SystemCmdStorage::SystemCmdData> mCurrentCmd;
};

#endif // SYSCOMMANDDIALOG_H

#ifndef SYSCOMMANDDIALOG_H
#define SYSCOMMANDDIALOG_H

#include <QDialog>
#include "ui_syscommanddialog.h"
#include <QMap>
#include <QString>
#include "systemcmdstorage.h"
#include <boost/optional.hpp>
#include "mainwindow.h"

class SysCommandDialog : public QDialog, private Ui::SysCommandDialog
{
    Q_OBJECT
public:
    explicit SysCommandDialog(MainWindow& mainWnd, QDialog *parent = nullptr);

signals:
  void loadFile( const QString& file_name );

public slots:
private slots:
    void on_executeButton_clicked();
    void on_regexButton_clicked();
    void on_directoryButton_clicked();
    void on_addCommandButton_clicked();
    void on_removeCommandButton_clicked();
    void on_runButton_clicked();
    void on_commandListWidget_currentRowChanged(int currentRow);

    void on_OkCloseButtonBox_clicked(QAbstractButton *button);

private:
    SystemCmdStorage::SystemCmdData getFormData();
    void setFormData(const SystemCmdStorage::SystemCmdData &cmd);
    void saveCurrent(bool saveStorage);

    std::shared_ptr<SystemCmdStorage> mCmdStorage;
    boost::optional<SystemCmdStorage::SystemCmdData> mCurrentCmd;
    MainWindow& mMainWnd;
};

#endif // SYSCOMMANDDIALOG_H

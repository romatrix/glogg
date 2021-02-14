#ifndef PLUGINSDIALOG_H
#define PLUGINSDIALOG_H

#include <QDialog>
#include "persistentinfo.h"
#include "pluginset.h"
#include "ui_PluginsDialog.h"
#include "PythonPluginInterface.h"


class PythonPlugin;

namespace Ui {
class PluginsDialog;
}

class PluginsDialog : public QDialog
{
    Q_OBJECT

protected:
    signals:
    void pluginsOptionsChanged(string pluginName, bool state);
public:
    explicit PluginsDialog(PythonPluginInterface *pyPlugin, QWidget *parent = nullptr);
    ~PluginsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_pluginSystemEnabled_clicked(bool checked);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_itemChanged(QListWidgetItem *item);

private:
    Ui::PluginsDialog *ui;
private:
    void createPluginClassList();

    std::shared_ptr<PluginSet> pluginSet_;
    PythonPluginInterface* pythonPlugin_;
    bool enableItemChangeHandler = false;
};

#endif // PLUGINSDIALOG_H

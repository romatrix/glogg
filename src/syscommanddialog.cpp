#include "syscommanddialog.h"
#include "multilineinputdialog.h"
#include <QFileDialog>


SysCommandDialog::SysCommandDialog(QDialog *parent) :
    QDialog(parent),
    mCmdStorage(SystemCmdStorage::getStoredInstance())
{
    setupUi(this);

    for(const QString& name: mCmdStorage->getNames()){
        commandListWidget->addItem(name);
    }
}


void SysCommandDialog::on_OkCloseButtonBox_accepted()
{
    mCmdStorage->save();
    accept();
    close();
}

void SysCommandDialog::on_OkCloseButtonBox_rejected()
{
    reject();
    close();
}

void updateTextWithMultilineInput(const QString& title, QLineEdit* edit)
{
    MultilineInputDIalog mid(title, edit->text());

    mid.exec();
    mid.show();
    edit->setText(mid.getText());
}

void SysCommandDialog::on_executeButton_clicked()
{
    updateTextWithMultilineInput("Command to execute", executeLineEdit);
}

void SysCommandDialog::on_regexButton_clicked()
{
    updateTextWithMultilineInput("Initial regex", regexEdit);
}

void SysCommandDialog::on_directoryButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                directoryEdit->text(),
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

    directoryEdit->setText(dir);
}

bool getState(const QCheckBox* checkBox)
{
    return checkBox->checkState() == Qt::CheckState::Checked;
}

void setState(QCheckBox* checkBox, bool state)
{
    checkBox->setCheckState(state ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

SystemCmdStorage::SystemCmdData SysCommandDialog::getFormData()
{
    SystemCmdStorage::SystemCmdData cmd;
    cmd.name = nameEdit->text();
    cmd.command = executeLineEdit->text();
    cmd.regex = regexEdit->text();
    cmd.repeatAtFail = getState(repeatOnFailCheck);
    cmd.append = getState(appendLogFileCheck);
    cmd.keepLog = getState(keepFileAfterClosingSessionCheck);

    return cmd;
}

void SysCommandDialog::setFormData(const SystemCmdStorage::SystemCmdData& cmd)
{
    nameEdit->setText(cmd.name);
    executeLineEdit->setText(cmd.command);
    regexEdit->setText(cmd.regex);
    setState(repeatOnFailCheck, cmd.repeatAtFail);
    setState(appendLogFileCheck, cmd.append);
    setState(keepFileAfterClosingSessionCheck, cmd.keepLog);
}

void SysCommandDialog::on_addCommandButton_clicked()
{
    SystemCmdStorage::SystemCmdData cmd = getFormData();

    if(mCmdStorage->addCommand(cmd)){
        commandListWidget->addItem(cmd.name);
        mCurrentCmd = cmd;
    } else {
        mCurrentCmd = boost::none;
    }
}

void SysCommandDialog::on_removeCommandButton_clicked()
{
    mCmdStorage->removeCommand(nameEdit->text());
    delete commandListWidget->takeItem(commandListWidget->currentRow());

    mCurrentCmd = boost::none;
}

void SysCommandDialog::on_runButton_clicked()
{

}

void SysCommandDialog::on_commandListWidget_currentRowChanged(int currentRow)
{
    if(mCurrentCmd){
        mCurrentCmd = getFormData();
        mCmdStorage->updateCommand(*mCurrentCmd);
    }

    const QString name = commandListWidget->item(currentRow)->text();
    const SystemCmdStorage::SystemCmdData cmd = mCmdStorage->getCommand(name);

    setFormData(cmd);
    mCurrentCmd = cmd;
}

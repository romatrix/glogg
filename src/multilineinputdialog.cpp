#include "multilineinputdialog.h"
#include "ui_multilineinputdialog.h"

MultilineInputDIalog::MultilineInputDIalog(const QString& title, const QString& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultilineInputDIalog),
    mData(data)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->textEdit->setPlainText(mData);
}

MultilineInputDIalog::~MultilineInputDIalog()
{
    delete ui;
}

void MultilineInputDIalog::on_buttonBox_accepted()
{
    mData = ui->textEdit->toPlainText();
    close();
}

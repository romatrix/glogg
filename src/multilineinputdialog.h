#ifndef MULTILINEINPUTDIALOG_H
#define MULTILINEINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class MultilineInputDIalog;
}

class MultilineInputDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit MultilineInputDIalog(const QString& title, const QString& data, QWidget *parent = 0);
    ~MultilineInputDIalog();
    QString getText() { return mData; }

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MultilineInputDIalog *ui;
    QString mData;
};

#endif // MULTILINEINPUTDIALOG_H

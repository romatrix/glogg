#ifndef QACTIONEXTENDED_H
#define QACTIONEXTENDED_H

#include <QAction>
#include <iostream>
#include <functional>

using namespace std;
class QActionExtended: public QAction
{
    Q_OBJECT

public:

    QActionExtended(string pluginName, function<void(string, bool)> action, QObject *parent = nullptr):QAction(tr(""), parent),action_(action),pluginName_(pluginName)
    {
    }
    string getName()
    {
        return pluginName_;
    }
    void hide(){ showPluginUI(false); }
private slots:
    void showPluginUI(bool checked)
    {
        cout << __FUNCTION__ << "\n";
        action_(pluginName_, checked);
    }
private:
    function<void(string, bool)> action_;
    string pluginName_;
};

#endif // QACTIONEXTENDED_H
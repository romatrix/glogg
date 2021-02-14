#ifndef QACTIONEXTENDED_QActionPluginMenu_H
#define QACTIONEXTENDED_QActionPluginMenu_H

#include <QAction>
#include <iostream>
#include <functional>

using namespace std;
class QActionPluginMenu: public QAction
{
    Q_OBJECT

public:

    QActionPluginMenu(const string& pluginName,
                      const string& menuString,
                      const string& viewName,
                      function<void(string, string)> action,
                      QObject *parent = nullptr):QAction(tr(menuString.c_str()), parent),
                                                 pluginName_(pluginName),
                                                 viewName_(viewName),
                                                 action_(action)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(execute()));
    }
    const string& getName() const
    {
        return pluginName_;
    }
private slots:
    void execute()
    {
        cout << __FUNCTION__ << "\n";
        action_(pluginName_, viewName_);
    }
private:
    function<void(string, string)> action_;
    string pluginName_;
    string viewName_;
};

#endif // QACTIONEXTENDED_QActionPluginMenu_H
#ifndef PYTHONPLUGIN_H
#define PYTHONPLUGIN_H

#include <vector>
#include <map>
#pragma push_macro("slots")
#undef slots
//#undef override
#include <boost/python.hpp>
#pragma pop_macro("slots")
#include <string>
#include "Handler.h"
#include "data/search_result.h"
#include "pluginset.h"
#include <memory>
#include <functional>
#include <PythonPluginInterface.h>

using namespace std;

class PyHandler;
class AbstractLogView;


struct PyGIL {
  PyGILState_STATE state;
  PyGIL() {
    state = PyGILState_Ensure();
  }

  ~PyGIL() {
    PyGILState_Release(state);
  }
};

class PythonPlugin: public PythonPluginInterface
{
public:
    PythonPlugin(const string& path, bool disablePlugins);
    void createInstances(const string &fileName);
    void onPopupMenu(AbstractLogView* alv);
    void onCreateMenu(AbstractLogView *alv);
    bool isOnSearcAvailable();
    SearchResultArray doSearch(const string &fileName, const string &pattern, int initialLine);
    void doGetExpandedLines(string &line, const string &fileName);

    map<string, bool> getConfig() const;
    void setPluginState(const string& typeName, bool state, const string &fileName);
    void enable(bool set);
    bool isEnabled() override;
    void registerUpdateViewsFunction(function<void ()> updateViewsFun, const string& fileName) override;
    void updateAppViews(const string& fileName) override;

private:

    const string mPath;

    struct PythonPluginImpl: public PythonPluginInterface
    {
        struct PythonGlobalInitialization
        {
            PythonGlobalInitialization()
            {
                Py_Initialize();
            }

            ~PythonGlobalInitialization()
            {
                Py_Finalize();
            }
        };

        PythonPluginImpl() = default;
        PythonPluginImpl(const map<string, bool>& config, const string& path);
        ~PythonPluginImpl();
        void createInstance(boost::optional<boost::python::object> type, const string &typeName, const string &fileName);

        struct DerivedType
        {
            DerivedType() = default;
            ~DerivedType();
            DerivedType(const string& name_, boost::python::object& type_): name(name_), type(type_){}
            string name;
            boost::python::object type;
        };

        template<typename T>
        static shared_ptr<T> create(T* obj)
        {
            return shared_ptr<T>(obj, [](T* o){ o->del(); });
        }
        vector<DerivedType> mDerivedClassContainer;
        map<pair<string,string>, shared_ptr<PyHandler>> mHandlers;
        PyThreadState *threadState = nullptr;
        map<string, bool> mInitialConfig;
        std::map<const string, function<void ()>> mUpdateViewsFun;
        function<void (string, string, string, function<void (string, bool)>)> mCreateAction;
        string mCurrentFileName;
        map<string, bool> mShowGui;

        void onShowUI(string pluginName, const string &fileName);
        void onHideAllUI(const string &pluginName);

        // PythonPluginInterface interfaces
    public:
        void createInstances(const string &fileName) override;
        void onPopupMenu(AbstractLogView *alv) override;
        void onCreateMenu(AbstractLogView *alv) override;
        bool isOnSearcAvailable() override;
        SearchResultArray doSearch(const string &fileName, const string &pattern, int initialLine) override;
        void doGetExpandedLines(string &line, const string &fileName) override;
        map<string, bool> getConfig() const override;
        void setPluginState(const string &typeName, bool state, const string &fileName) override;
        void registerUpdateViewsFunction(function<void ()> updateViewsFun, const string &fileName) override;
        bool isEnabled() override;
        void enable(bool set) override;
        void updateAppViews(const string& fileName) override;

        // PythonPluginInterface interface
    public:
        void onCreateToolBars(function<void(string, string, string, function<void (string, bool)>)> createAction) override;
        void onCreateToolBarItem(string pluginName, const string &fileName);
        void onShowLogView(const string &fileName) override;
    };

    unique_ptr<PythonPluginImpl> mPluginImpl;

    // PythonPluginInterface interface

    // PythonPluginInterface interface
public:
    void onCreateToolBars(function<void (string, string, string, function<void (string, bool)>)> createAction) override;
    void onCreateToolBarItem(string pluginName, const string &fileName);
    void onShowLogView(const string &fileName) override;
    //void doGetExpandedLines(string &line, const string &fileName) override;

    // PythonPluginInterface interface
public:
};


#endif // PYTHONPLUGIN_H

#ifndef HSIM_PLUGIN_INCLUDED
#define HSIM_PLUGIN_INCLUDED

#include <stdexcept>
#include <string>

#include <dlfcn.h>

#include "plugin_api.hh"

namespace hsim {

class Plugin final {
  public:
    Plugin(const std::string &pluginPath, const std::string &options = "")
        : m_pluginName{pluginPath}, m_options{options} {
        m_dlhandle = dlopen(pluginPath.c_str(), RTLD_NOW);
        if (m_dlhandle == nullptr) {
            std::string dlErrorMsg = dlerror();
            std::string fullErrorMsg = "Unable to load plugin: " + pluginPath +
                                       ". Error: " + dlErrorMsg;
            throw std::runtime_error(fullErrorMsg);
        }

        auto loadFunc = reinterpret_cast<LoadFunc>(
            dlsym(m_dlhandle, kLoadFuncName.c_str()));
        if (loadFunc == nullptr) {
            std::string dlErrorMsg = dlerror();
            std::string fullErrorMsg =
                "Unable to load : " + pluginPath + ". Error: " + dlErrorMsg;
            throw std::runtime_error(fullErrorMsg);
        }

        LoadablePlugin plugin = loadFunc(options.c_str());
        m_pluginMem = plugin.pluginMem;
        m_notify = plugin.notify;
        m_unload = plugin.unload;
    }

    ~Plugin() {
        m_unload(m_pluginMem);

        dlclose(m_dlhandle);
    }

    void notify() { m_notify(m_pluginMem); }

  private:
    std::string m_pluginName;
    std::string m_options;

    void *m_dlhandle;
    void *m_pluginMem;
    NotifyFunc m_notify;
    UnloadFunc m_unload;
};

} // namespace hsim

#endif // HSIM_PLUGIN_INCLUDED

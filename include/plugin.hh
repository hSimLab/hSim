#ifndef HSIM_PLUGIN_INCLUDED
#define HSIM_PLUGIN_INCLUDED

#include <filesystem>
#include <string>

#include <dlfcn.h>

#include "machine_event.hh"
#include "so_loader.hh"

namespace hsim {

class IPlugin {
  public:
    virtual ~IPlugin() = default;
    virtual void update() = 0;
};

using LoadPLuginFunc = hsim::IPlugin *(*)(const char *options);
using UnloadPluginFunc = void (*)(IPlugin *plugin);

class PluginConsumer : public IEventConsumer {
  public:
    PluginConsumer(const std::filesystem::path &path,
                   const std::string &options)
        : m_sharedLib{path, kLazy} {
        auto loadFunc = m_sharedLib.get<LoadPLuginFunc>("loadPlugin");
        m_plugin = loadFunc(options.c_str());
    }
    ~PluginConsumer() override {
        auto unloadFunc = m_sharedLib.get<UnloadPluginFunc>("unloadPlugin");
        unloadFunc(m_plugin);
    }
    void update() override { m_plugin->update(); }

  private:
    IPlugin *m_plugin;
    SharedLib m_sharedLib;
};

} // namespace hsim

#endif // HSIM_PLUGIN_INCLUDED

#ifndef HSIM_PLUGIN_INCLUDED
#define HSIM_PLUGIN_INCLUDED

#include <filesystem>
#include <memory>
#include <string>

#include <dlfcn.h>

#include "machine_event.hh"
#include "so_loader.hh"
#include "support.hh"

namespace hsim {

class IPlugin {
  public:
    virtual ~IPlugin() = default;
    virtual void handle(MemRead event, Addr addr) = 0;
    virtual void handle(MemWrite event, Addr addr, Word value) = 0;
    virtual void handle(PreInsn event, Word insn) = 0;
    virtual void handle(PostInsn event, Word insn) = 0;
};

using LoadPluginFunc = IPlugin *(*)(const std::string &options);
using UnloadPluginFunc = void (*)(IPlugin *plugin);

constexpr std::string kLoadPluginFuncName = "loadPlugin";
constexpr std::string kUnloadPluginFuncName = "unloadPlugin";

// NOTE plugins should use this defines when declaring a function
#define HSIM_LOAD_PLUGIN_FUNC extern "C" hsim::IPlugin *loadPlugin
#define HSIM_UNLOAD_PLUGIN_FUNC extern "C" void unloadPlugin

class PluginConsumer : public IEventConsumer {
  public:
    PluginConsumer(const std::filesystem::path &path,
                   const std::string &options)
        : m_sharedLib{path, kLazy}, m_plugin{nullptr, nullptr} {
        auto loadFunc = m_sharedLib.get<LoadPluginFunc>(kLoadPluginFuncName);
        auto unloadFunc =
            m_sharedLib.get<UnloadPluginFunc>(kUnloadPluginFuncName);

        m_plugin = std::unique_ptr<IPlugin, UnloadPluginFunc>(loadFunc(options),
                                                              unloadFunc);
    }

    void handle(MemRead event, Addr addr) override {
        m_plugin->handle(event, addr);
    }
    void handle(MemWrite event, Addr addr, Word value) override {
        m_plugin->handle(event, addr, value);
    }
    void handle(PreInsn event, Word insn) override {
        m_plugin->handle(event, insn);
    }
    void handle(PostInsn event, Word insn) override {
        m_plugin->handle(event, insn);
    }

  private:
    SharedLib m_sharedLib;
    std::unique_ptr<IPlugin, UnloadPluginFunc> m_plugin;
};

} // namespace hsim

#endif // HSIM_PLUGIN_INCLUDED

#ifndef HSIM_PLUGIN_INCLUDED
#define HSIM_PLUGIN_INCLUDED

#include <filesystem>
#include <memory>
#include <string>
#include <utility>

#include <dlfcn.h>

#include "machine_event.hh"
#include "so_loader.hh"

namespace hsim {

using IPlugin = IEventConsumer;

// class IPlugin : public IEventConsumer {
//   public:
//     IPlugin(SharedLib so_lib) : m_sharedLib(std::move(so_lib)) {}
//     ~IPlugin() override = default;
//     // SharedLib getSOLib() { return m_sharedLib; }

//   private:
//     // SharedLib m_sharedLib;
// };

using LoadPLuginFunc = hsim::IPlugin *(*)(const char *options);

// using IPluginHandler = std::unique_ptr<IPlugin, void (*)(IPlugin*)>;
// auto loadPluginFromSO(const std::filesystem::path& path, const std::string&
// options) {
//     SharedLib sharedLib{path, kLazy};
//     auto loadPluginFunc = sharedLib.get<LoadPLuginFunc>("loadPlugin");
//
//     // NOTE reason for custom deleter:
//     //      when ~IPlugin is called it first calls ~SharedLib and then
//     ~SimplePlugin(wich is already unloaded) auto pluginDeleter = [lib =
//     SharedLib{sharedLib}](IPlugin* plugin) mutable { delete plugin; };

//     IPlugin* plugin = loadPluginFunc(options.c_str(), sharedLib);
//     return std::unique_ptr<IPlugin, decltype(pluginDeleter)>{plugin,
//     pluginDeleter};
// }

// // NOTE reason for custom deleter:
// //      when ~IPlugin is called it first calls ~SharedLib and then
// ~SimplePlugin(wich is already unloaded) void ipluginDeleter(IPlugin* plugin)
// {
//     SharedLib soLib = plugin->getSOLib();
//     soLib.~SharedLib();
// }

// using IPluginHandler = std::unique_ptr<IPlugin, void (*)(IPlugin*)>;
// IPluginHandler loadPluginFromSO(const std::filesystem::path& path, const
// std::string& options) {
//     SharedLib sharedLib{path, kLazy};
//     auto loadPluginFunc = sharedLib.get<LoadPLuginFunc>("loadPlugin");
//
//     IPlugin* plugin = loadPluginFunc(options.c_str(), sharedLib);
//     return IPluginHandler{plugin, ipluginDeleter};
// }

// using IPluginHandler = std::unique_ptr<IPlugin>;
// IPluginHandler loadPluginFromSO(const std::filesystem::path& path, const
// std::string& options) {
//     SharedLib sharedLib{path, kLazy};
//     auto loadPluginFunc = sharedLib.get<LoadPLuginFunc>("loadPlugin");
//
//     IPlugin* plugin = loadPluginFunc(options.c_str(), sharedLib);
//     return IPluginHandler{plugin};
// }

using IPluginHandler = std::unique_ptr<IPlugin>;
IPluginHandler loadPluginFromSO(SharedLib sharedLib,
                                const std::string &options) {
    auto loadPluginFunc = sharedLib.get<LoadPLuginFunc>("loadPlugin");

    IPlugin *plugin = loadPluginFunc(options.c_str());
    return IPluginHandler{plugin};
}

} // namespace hsim

#endif // HSIM_PLUGIN_INCLUDED

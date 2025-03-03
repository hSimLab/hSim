#ifndef HSIM_PLUGIN_MANAGER_INCLUDED
#define HSIM_PLUGIN_MANAGER_INCLUDED

#include <string>
#include <vector>

#include "plugin.hh"

namespace hsim {

class PluginManager final {
  public:
    void loadPlugin(const std::string &pluginPath,
                    const std::string &options = "") {
        m_plugins.emplace_back(pluginPath, options);
    }

    void notify() {
        for (auto &plugin : m_plugins) {
            plugin.notify();
        }
    }

  private:
    std::vector<Plugin> m_plugins;
};

} // namespace hsim

#endif // HSIM_PLUGIN_MANAGER_INCLUDED

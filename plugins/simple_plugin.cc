#include "plugin_api.hh"

#include <iostream>

void notify(void* pluginMem);
void unload(void* pluginMem);

HSIM_PLUGIN_API_ATTR hsim::LoadablePlugin loadPlugin([[maybe_unused]] const char* options) {
    hsim::LoadablePlugin plugin = {};
    plugin.pluginMem = nullptr;
    plugin.notify = notify;
    plugin.unload = unload;

    std::cout << "load plugin" << std::endl;

    return plugin;
}

void notify([[maybe_unused]] void* pluginMem) {
    std::cout << "notify plugin" << std::endl;   
}

void unload([[maybe_unused]] void* pluginMem) {
    std::cout << "unload plugin" << std::endl;
} 

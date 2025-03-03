#ifndef HSIM_PLUGIN_API_INCLUDED
#define HSIM_PLUGIN_API_INCLUDED

#include <string>

#define HSIM_PLUGIN_API_ATTR extern "C"

namespace hsim {

static const std::string kLoadFuncName = "loadPlugin";

struct LoadablePlugin;

extern "C" {

using LoadFunc = LoadablePlugin (*)(const char *options);
using NotifyFunc = void (*)(void *pluginMem);
using UnloadFunc = void (*)(void *pluginMem);

} // extern "C"

struct LoadablePlugin {
    void *pluginMem;
    NotifyFunc notify;
    UnloadFunc unload;
};

}; // namespace hsim

#endif // HSIM_PLUGIN_API_INCLUDED

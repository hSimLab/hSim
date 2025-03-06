#ifndef HSIM_SO_LOADER_INCLUDED
#define HSIM_SO_LOADER_INCLUDED

#include <cstdint>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>

#include <dlfcn.h>

namespace hsim {

enum SharedLibMode : std::uint16_t {
    kLazy = RTLD_LAZY,
    kNow = RTLD_NOW,
    kGlobal = RTLD_GLOBAL,
    kLocal = RTLD_LOCAL,
};

class SharedLib {
  public:
    SharedLib(const std::filesystem::path &libPath, SharedLibMode mode)
        : m_handle{dlopen(libPath.c_str(), mode), [](void *handle) {
                       if (handle != nullptr) {
                           dlclose(handle);
                       }
                   }} {
        if (m_handle == nullptr) {
            throw std::runtime_error{dlerror()};
        }
    }
    template <typename T> T get(const std::string &symbol) {
        void *loadedSymbol = dlsym(m_handle.get(), symbol.c_str());
        if (loadedSymbol == nullptr) {
            throw std::runtime_error{dlerror()};
        }

        return reinterpret_cast<T>(loadedSymbol);
    }

  private:
    std::shared_ptr<void> m_handle;
};

} // namespace hsim

#endif // HSIM_SO_LOADER_INCLUDED

#ifndef HSIM_SO_LOADER_INCLUDED
#define HSIM_SO_LOADER_INCLUDED

#include <cstdint>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <dlfcn.h>

namespace hsim {

enum SharedLibMode : std::uint16_t {
    kLazy = RTLD_LAZY,
    kNow = RTLD_NOW,
    kGlobal = RTLD_GLOBAL,
    kLocal = RTLD_LOCAL,
};

template <typename T>
concept PointerT = std::is_pointer_v<T>;

class SharedLib {
  private:
    struct DlCloser {
        void operator()(void *handle) { dlclose(handle); }
    };

  public:
    SharedLib(const std::filesystem::path &libPath, SharedLibMode mode)
        : m_handle{dlopen(libPath.c_str(), mode)} {
        if (m_handle == nullptr) {
            throw std::runtime_error{dlerror()};
        }
    }
    template <PointerT T> T get(const std::string &symbol) {
        void *loadedSymbol = dlsym(m_handle.get(), symbol.c_str());
        if (loadedSymbol == nullptr) {
            throw std::runtime_error{dlerror()};
        }

        return reinterpret_cast<T>(loadedSymbol);
    }

  private:
    std::unique_ptr<void, DlCloser> m_handle;
};

} // namespace hsim

#endif // HSIM_SO_LOADER_INCLUDED

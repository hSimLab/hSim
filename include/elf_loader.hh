#ifndef HSIM_ELF_LOADER_INCLUDED
#define HSIM_ELF_LOADER_INCLUDED

#include <filesystem>

#include "memory.hh"
#include "support.hh"

namespace hsim {

/**
 * @brief Driver to load ELF files with little-endianness
 *
 */
struct ElfLoader final {
  public:
    explicit ElfLoader(std::filesystem::path path) : m_path(std::move(path)) {}
    //
    void load(Memory &memory);
    Addr entryPoint() const { return m_entryPoint; }

  private:
    std::filesystem::path m_path;
    uint64_t m_entryPoint{};
};

} // namespace hsim

#endif // HSIM_ELF_LOADER_INCLUDED

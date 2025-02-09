#ifndef HSIM_ELF_LOADER_INCLUDED
#define HSIM_ELF_LOADER_INCLUDED

#include <filesystem>
#include <stdexcept>

#include "memory.hh"
#include "support.hh"

namespace hSim {

/**
 * @brief Driver to load ELF files with little-endianness
 *
 */
struct ElfLoader final {
  public:
    explicit ElfLoader(std::filesystem::path path) : m_path(path) {}
    //
    void load(Memory &memory);
    Addr entry_point() const { return m_entry_point; }

  private:
    std::filesystem::path m_path;
    uint64_t m_entry_point{};
};

} // namespace hSim

#endif // HSIM_ELF_LOADER_INCLUDED
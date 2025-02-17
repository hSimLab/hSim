#ifndef HSIM_CONFIG_INCLUDED
#define HSIM_CONFIG_INCLUDED

#include <filesystem>

namespace hsim {

/**
 * @brief Simulator config with/ different useful data
 *
 */
struct Config final {
    std::filesystem::path elf_path{};
    std::filesystem::path log_path{};
    //
    bool dump_exec{true};
};

} // namespace hsim

#endif // HSIM_CONFIG_INCLUDED

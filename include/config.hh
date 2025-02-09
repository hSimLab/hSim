#ifndef HSIM_CONFIG_INCLUDED
#define HSIM_CONFIG_INCLUDED

#include <filesystem>

namespace hSim {

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

} // namespace hSim

#endif // HSIM_CONFIG_INCLUDED
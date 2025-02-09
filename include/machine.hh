#ifndef HSIM_MACHINE_INCLUDED
#define HSIM_MACHINE_INCLUDED

#include "config.hh"
#include "elf_loader.hh"
#include "memory.hh"

namespace hSim {

/**
 * @brief Driver to inialize all state & run execution
 *
 */
class Machine final {
  public:
    Machine(const Config &config) {
        ElfLoader loader{config.elf_path};

        loader.load(m_mem);
        // m_state.set_pc(loader.entry_point());
    }

    void run() {
        // while (!m_state.finished) {
        //     step();
        // }
    }

  private:
    bool m_finished{false};

    Memory m_mem{};
    // CpuState m_state{nullptr};
};

} // namespace hSim

#endif // HSIM_MACHINE_INCLUDED
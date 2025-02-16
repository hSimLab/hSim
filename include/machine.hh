#ifndef HSIM_MACHINE_INCLUDED
#define HSIM_MACHINE_INCLUDED

#include <memory>

#include "config.hh"
#include "cpu_state.hh"
#include "elf_loader.hh"
#include "executors.hh"
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
        m_state =
            std::make_unique<hSim::CpuState>(loader.entry_point(), &m_mem);
    }

    void step() { execute(m_state.get(), 0, 0, 0); }

    void run() {
        while (!m_state->finished()) {
            step();
        }
    }

  private:
    std::unique_ptr<hSim::CpuState> m_state;
    Memory m_mem{};
};

} // namespace hSim

#endif // HSIM_MACHINE_INCLUDED

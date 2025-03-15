#ifndef HSIM_MACHINE_INCLUDED
#define HSIM_MACHINE_INCLUDED

#include <memory>
#include <string>
#include <utility>

#include "config.hh"
#include "cpu_state.hh"
#include "elf_loader.hh"
#include "executors.hh"
#include "machine_event.hh"
#include "memory.hh"

namespace hsim {

/**
 * @brief Driver to inialize all state & run execution
 *
 */
class Machine final {
  public:
    Machine(const Config &config) {
        ElfLoader loader{config.elf_path};

        loader.load(m_mem);
        m_state = std::make_unique<CpuState>(loader.entryPoint(), &m_mem);
    }

    void step() { execute(m_state.get(), 0, 0, 0); }

    void run() {
        while (!m_state->finished()) {
            step();
        }
    }

    void addEventConsumer(IEventConsumerHandle consumer) {
        m_eventManager.attach(std::move(consumer));
    }

    template <typename Event, typename... Args> void notify(Args &&...args) {
        m_eventManager.notify<Event>(std::forward<Args>(args)...);
    }

  private:
    std::unique_ptr<CpuState> m_state;
    Memory m_mem{};
    EventManager m_eventManager;
};

} // namespace hsim

#endif // HSIM_MACHINE_INCLUDED

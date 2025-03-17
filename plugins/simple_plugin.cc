#include <iostream>
#include <string>
#include <utility>

#include "machine_event.hh"
#include "plugin.hh"
#include "support.hh"

namespace hsim {

class SimplePlugin : public hsim::IPlugin {
  public:
    SimplePlugin(std::string name) : m_name{std::move(name)} {
        std::cout << "SimplePlugin: " << m_name << std::endl;
    }

    ~SimplePlugin() override {
        std::cout << "~SimplePlugin: " << m_name << std::endl;
    }

    void handle([[maybe_unused]] MemRead event, Addr addr) override {
        std::cout << m_name << " MemRead: " << std::hex << addr << std::endl;
    }

    void handle([[maybe_unused]] MemWrite event, Addr addr,
                Word value) override {
        std::cout << m_name << " MemWrite: " << std::hex << addr << " " << value
                  << std::endl;
    }

    void handle([[maybe_unused]] PreInsn event, Word insn) override {
        std::cout << m_name << " PreInsn: " << std::hex << insn << std::endl;
    }

    void handle([[maybe_unused]] PostInsn event, Word insn) override {
        std::cout << m_name << " PostInsn: " << std::hex << insn << std::endl;
    }

  private:
    std::string m_name;
};

HSIM_LOAD_PLUGIN_FUNC(const std::string &options) {
    return new SimplePlugin{options};
}

HSIM_UNLOAD_PLUGIN_FUNC(SimplePlugin *plugin) { delete plugin; }

} // namespace hsim

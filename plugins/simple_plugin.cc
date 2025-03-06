#include <iostream>
#include <string>
#include <utility>

#include "plugin.hh"
#include "so_loader.hh"

class SimplePlugin : public hsim::IPlugin {
  public:
    SimplePlugin(std::string name, hsim::SharedLib so_lib)
        : IPlugin{std::move(so_lib)}, m_name{std::move(name)} {
        std::cout << "SimplePlugin: " << m_name << std::endl;
    }

    ~SimplePlugin() override {
        std::cout << "~SimplePlugin: " << m_name << std::endl;
    }

    void update() override {
        std::cout << "SimplePlugin name is : " << m_name << std::endl;
    }

  private:
    std::string m_name;
};

extern "C" hsim::IPlugin *loadPlugin(const char *options,
                                     hsim::SharedLib so_lib) {
    return new SimplePlugin{options, std::move(so_lib)};
}

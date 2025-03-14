#include <iostream>
#include <string>
#include <utility>

#include "plugin.hh"

class SimplePlugin : public hsim::IPlugin {
  public:
    SimplePlugin(std::string name) : m_name{std::move(name)} {
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

HSIM_LOAD_PLUGIN_FUNC(const std::string &options) {
    return new SimplePlugin{options};
}

HSIM_UNLOAD_PLUGIN_FUNC(SimplePlugin *plugin) { delete plugin; }

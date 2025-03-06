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

extern "C" hsim::IPlugin *loadPlugin(const char *options) {
    return new SimplePlugin{options};
}

extern "C" void unloadPlugin(SimplePlugin *plugin) { delete plugin; }

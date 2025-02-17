#include <iostream>
#include <stdexcept>
//
#include <CLI/CLI.hpp>

#include "config.hh"
#include "machine.hh"

int main(int argc, char **argv) try {
    CLI::App app("hSim: high Performance CPU Simulator");
    hsim::Config config{};

    app.add_option("--elf", config.elf_path, "Path to ELF file")
        ->required()
        ->check(CLI::ExistingFile);

    app.add_option("--log", config.log_path, "Path to log file")
        ->required()
        ->check(CLI::ExistingFile);

    app.add_flag("--dump-exec", config.dump_exec,
                 "Option to enable dump of state on execution")
        ->default_val(true);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }
    //
    hsim::Machine machine{config};

    machine.run();

    return 0;
} catch (const std::exception &e) {
    std::cout << e.what() << '\n';
    return 1;
}

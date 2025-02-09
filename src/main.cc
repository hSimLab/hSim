#include <iostream>
#include <stdexcept>
//
#include <CLI/CLI.hpp>

int main(int argc, char **argv) try {
    CLI::App cli_app("hSim: high Perfomance CPU Simulator");

    try {
        cli_app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return cli_app.exit(e);
    }
    //
    return 0;
} catch (const std::exception &e) {
    std::cout << e.what() << '\n';
    return 1;
}
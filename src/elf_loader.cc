#include <elfio/elfio.hpp>

#include "elf_loader.hh"

namespace hSim {

void ElfLoader::load(Memory &memory) {
    ELFIO::elfio reader{};

    if (reader.load(m_path))
        throw std::invalid_argument("Bad ELF path: " + m_path.string());

    if (reader.get_encoding() != ELFIO::ELFDATA2LSB) {
        throw std::runtime_error("Wrong ELF encoding");
    }

    m_entry_point = reader.get_entry();

    for (const auto &segment : reader.segments) {
        if (segment->get_type() == ELFIO::PT_LOAD) {
            const Addr phys_addr = segment->get_physical_address();
            const std::size_t file_size = segment->get_file_size();

            memory.writeBlock(
                phys_addr, reinterpret_cast<const Byte *>(segment->get_data()),
                file_size);
        }
    }
}
} // namespace hSim
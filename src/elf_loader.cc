#include <elfio/elfio.hpp>

#include "elf_loader.hh"

namespace hsim {

void ElfLoader::load(Memory &memory) {
    ELFIO::elfio reader{};

    if (!reader.load(m_path)) {
        throw std::invalid_argument("Bad ELF path: " + m_path.string());
    }

    if (reader.get_encoding() != ELFIO::ELFDATA2LSB) {
        throw std::runtime_error("Wrong ELF encoding");
    }

    m_entryPoint = reader.get_entry();

    for (const auto &segment : reader.segments) {
        if (segment->get_type() == ELFIO::PT_LOAD) {
            const Addr vaddr = segment->get_virtual_address();
            const auto fileSize = segment->get_file_size();

            memory.writeBlock(vaddr, {reinterpret_cast<const std::byte *>(
                                          segment->get_data()),
                                      fileSize});
        }
    }
}
} // namespace hsim

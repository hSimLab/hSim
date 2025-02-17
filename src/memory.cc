#include <algorithm>
#include <cassert>
#include <cstring>

#include "memory.hh"

namespace hsim {
void Memory::readBlock(Addr addr, std::span<std::byte> buffer) const {
    std::memcpy(buffer.data(), m_data.data() + addr, buffer.size_bytes());
}

void Memory::writeBlock(Addr addr, std::span<const std::byte> buffer) {
    std::memcpy(m_data.data() + addr, buffer.data(), buffer.size_bytes());
}
} // namespace hsim

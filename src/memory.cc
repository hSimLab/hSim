#include <cassert>
#include <cstdint>
#include <cstring>

#include "memory.hh"

namespace hSim {
void Memory::readBlock(Addr addr, Byte *buf, std::size_t size) const {
    assert(buf && "Invalid buffer pointer");
    std::memcpy(buf, m_data.data() + addr, size);
}

void Memory::writeBlock(Addr addr, const Byte *buf, std::size_t size) {
    assert(buf && "Invalid buffer pointer");
    std::memcpy(m_data.data() + addr, reinterpret_cast<const char *>(buf),
                size);
}
} // namespace hSim
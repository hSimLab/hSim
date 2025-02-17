#ifndef HSIM_MEMORY_INCLUDED
#define HSIM_MEMORY_INCLUDED

#include <concepts>
#include <cstring>
#include <limits>
#include <span>
#include <vector>

#include "support.hh"

namespace hsim {

/**
 * @brief Naive implementation of byte-addressable memory
 *
 */
class Memory final {
  public:
    static constexpr std::size_t kMemSize = std::numeric_limits<Addr>::max();

    Memory() { m_data.resize(kMemSize); }

    template <std::integral T> T read(Addr addr) const {
        T value;
        std::memcpy(&value, m_data.data() + addr, sizeof(T));
        return value;
    }

    void write(Addr addr, std::integral auto value) {
        std::memcpy(m_data.data() + addr, &value, sizeof(value));
    }

    void readBlock(Addr addr, std::span<std::byte> buffer) const;
    void writeBlock(Addr addr, std::span<const std::byte> buffer);

  private:
    std::vector<Byte> m_data;
};

} // namespace hsim

#endif // HSIM_MEMORY_INCLUDED

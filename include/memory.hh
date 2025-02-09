#ifndef HSIM_MEMORY_INCLUDED
#define HSIM_MEMORY_INCLUDED

#include <limits>
#include <vector>

#include "support.hh"

namespace hSim {

/**
 * @brief Naive implementation of byte-addressable memory
 *
 */
class Memory final {
  public:
    static constexpr std::size_t kMemSize = std::numeric_limits<Addr>::max();

    Memory() { m_data.resize(kMemSize); }

    template <typename T> T read(Addr addr) const {
        static_assert(std::is_integral<T>::value,
                      "Error: Integral type required");
        T value = *reinterpret_cast<const T *>(m_data.data() + addr);
        return value;
    }

    template <typename T> void write(Addr addr, T value) {
        static_assert(std::is_integral<T>::value,
                      "Error: Integral type required");
        *reinterpret_cast<T *>(m_data.data() + addr) = value;
    }

    void readBlock(Addr addr, Byte *buf, std::size_t size) const;
    void writeBlock(Addr addr, const Byte *buf, std::size_t size);

  private:
    std::vector<Byte> m_data;
};

} // namespace hSim

#endif // HSIM_MEMORY_INCLUDED
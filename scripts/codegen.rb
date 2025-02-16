
module CodeGenerator
  def self.generate_cpu_state(path)
    File.open(path, 'w') do |f|
      f.puts <<~EXECUTOR
        #ifndef HSIM_CPU_STATE_INCLUDED
        #define HSIM_CPU_STATE_INCLUDED

        #include <array>
        #include <cstddef>
        #include <iostream>

        #include "support.hh"
        #include "memory.hh"

        namespace hSim {
        class CpuState final {
          public:
            static constexpr std::size_t kNumRegisters = 32;

            CpuState(Addr entry, Memory* mem) : m_mem(mem), m_pc(entry) {}

            Word get_pc() const { return m_pc; }
            bool finished() const { return m_finished; }

            auto *get_mem() const { return m_mem; }

            Word get_reg(std::size_t idx) const { return m_X[idx]; }
            void set_reg(std::size_t idx, Word val) { m_X[idx] = val; }

          private:
            std::array<Word, kNumRegisters> m_X{};
            Memory* m_mem{nullptr};

            Word m_pc{};
            bool m_finished{false};
        };
        } // namespace hSim

        #endif // HSIM_CPU_STATE_INCLUDED
      EXECUTOR
    end
  end

  def self.generate_execuctors_hh(path)
    File.open(path, 'w') do |f|
      f.puts <<~EXECUTOR
        #ifndef HSIM_EXECUTORS_INCLUDED
        #define HSIM_EXECUTORS_INCLUDED


        namespace hSim {
          class CpuState;

          void execute(CpuState* state, int rd, int rs1, int rs2);
        }
        #endif // HSIM_EXECUTORS_INCLUDED
      EXECUTOR
    end
  end

  def self.generate_execuctors_cc(path)
    File.open(path, 'w') do |f|
      f.puts <<~EXECUTOR
        #include "executors.hh"

        namespace hSim {
          void execute(CpuState *state, int rd, int rs1, int rs2) { return; }
        }
      EXECUTOR
    end
  end

  def self.generate_decoder(path)
    File.open(path, 'w') do |f|
      f.puts <<~DECODER
        #ifndef HSIM_DECODER_INCLUDED
        #define HSIM_DECODER_INCLUDED

        namespace hSim {}

        #endif // HSIM_DECODER_INCLUDED
      DECODER
    end
  end
end

if ARGV.empty?
  puts "Usage: ruby codegen.rb <path/to/directory>"
  exit 1
end

root = ARGV[0]

if !Dir.exist?(root)
  Dir.mkdir(root)
end

CodeGenerator.generate_cpu_state(File.join(root, 'cpu_state.hh'))
CodeGenerator.generate_execuctors_hh(File.join(root, 'executors.hh'))
CodeGenerator.generate_execuctors_cc(File.join(root, 'executors.cc'))
CodeGenerator.generate_decoder(File.join(root, 'decoder.hh'))

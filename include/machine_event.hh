#ifndef HSIM_MACHINE_EVENT_INCLUDED
#define HSIM_MACHINE_EVENT_INCLUDED

#include <list>
#include <memory>
#include <utility>

#include "support.hh"

namespace hsim {

struct MemRead {};
struct MemWrite {};
struct PreInsn {};
struct PostInsn {};

class IEventConsumer {
  public:
    virtual ~IEventConsumer() = default;
    virtual void handle(MemRead event, Addr addr) = 0;
    virtual void handle(MemWrite event, Addr addr, Word value) = 0;
    virtual void handle(PreInsn event, Word insn) = 0;
    virtual void handle(PostInsn event, Word insn) = 0;
};

using IEventConsumerHandle = std::unique_ptr<IEventConsumer>;
class EventManager final {
  public:
    template <typename Event, typename... Args> void notify(Args &&...args) {
        for (auto &consumer : m_consumers) {
            consumer->handle(Event{}, std::forward<Args>(args)...);
        }
    }
    void attach(IEventConsumerHandle consumer) {
        m_consumers.push_back(std::move(consumer));
    }
    void detach(IEventConsumerHandle consumer) { m_consumers.remove(consumer); }

  private:
    std::list<IEventConsumerHandle> m_consumers;
};

} // namespace hsim

#endif // HSIM_MACHINE_EVENT_INCLUDED

#ifndef HSIM_MACHINE_EVENT_INCLUDED
#define HSIM_MACHINE_EVENT_INCLUDED

#include <list>
#include <memory>
#include <utility>

namespace hsim {

class IEventConsumer {
  public:
    virtual ~IEventConsumer() = default;
    virtual void update() = 0;
};

using IEventConsumerHandle = std::unique_ptr<IEventConsumer>;
class EventManager final {
  public:
    void notify() {
        for (auto &consumer : m_consumers) {
            consumer->update();
        }
    }
    void attach(IEventConsumerHandle consumer) {
        m_consumers.push_back(std::move(consumer));
    }
    void detach(IEventConsumerHandle consumer) { m_consumers.remove(consumer); }

  private:
    std::list<IEventConsumerHandle> m_consumers; // unique?
};

} // namespace hsim

#endif // HSIM_MACHINE_EVENT_INCLUDED

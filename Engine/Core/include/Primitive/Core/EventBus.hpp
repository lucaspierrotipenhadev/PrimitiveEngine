#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace primitive
{
    class EventBus
    {
    public:
        EventBus() = default;
        ~EventBus() = default;

        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;

        template<typename Event>
        using EventCallback = std::function<void(const Event&)>;

        template<typename Event>
        void Subscribe(EventCallback<Event> callback)
        {
            auto wrapper =
                [callback = std::move(callback)](const void* event)
                {
                    callback(
                        *static_cast<const Event*>(event)
                    );
                };

            m_subscribers[typeid(Event)].push_back(
                std::move(wrapper)
            );
        }

        template<typename Event>
        void Publish(const Event& event)
        {
            auto it = m_subscribers.find(typeid(Event));

            if (it == m_subscribers.end())
            {
                return;
            }

            for (auto& callback : it->second)
            {
                callback(&event);
            }
        }

    private:
        std::unordered_map<
            std::type_index,
            std::vector<std::function<void(const void*)>>
        > m_subscribers;
    };
}
#pragma once
// libs
#include <chrono>
#include <thread>
#include <iostream>

struct GameTimer
{
    using clock = std::chrono::steady_clock;
    using nano = std::chrono::duration<uint64_t, std::nano>;
    using timepoint = std::chrono::time_point<clock, nano>;

    explicit GameTimer() noexcept
    {
        start();
    }

    void start() noexcept
    {
        m_start = clock::now();
    }

    uint64_t ellapsed() noexcept
    {
        auto ns_passed{clock::now() - m_start};
        return ns_passed.count();
    }

    // template <typename ChronoType>
    // ChronoType ellapsedDuration() noexcept
    // {
    //     auto ns_passed{clock::now() - m_start};
    //     return std::chrono::duration_cast<ChronoType>(ns_passed);
    // }

    uint64_t waitUntil_ns(uint64_t to_ns)
    {
        // uint16_t ellapsed_time = ellapsed();
        // if (ellapsed_time < to_ns)
        if (ellapsed() < to_ns)
        {
            // auto toWait{to_ns - ellapsed_time};
            auto toWait{to_ns - ellapsed()};
            std::this_thread::sleep_for(nano{toWait});
            return toWait;
        }
        return 0;
    }

    /* bool cyclePassed() const {
        return waitUntil_ns() >= (1.0/fps);
    } */

    // void waitSeconds(float seconds)
    // {
    //     std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
    // }

    // lambda to see time of function
    // auto timedCall = [](std::string_view name, auto &&func)
    // {
    //     GameTimer timer;
    //     func();
    //     std::cout << "[" << name << "] " << timer.ellapsed() / 1000 << " ms ";
    //     // std::cout << timer.ellapsed() << ";";
    // };

private:
    timepoint m_start;
    // uint16_t ellapsed_time;
};
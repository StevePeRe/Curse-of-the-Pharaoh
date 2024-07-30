#pragma once
#include <chrono>

class GameTimerX
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    double fps;

public:
    GameTimerX() : startTime(std::chrono::high_resolution_clock::now()), fps(60.0) {}

    explicit GameTimerX(double targetFPS) : startTime(std::chrono::high_resolution_clock::now()), fps(targetFPS) {}

    void start() noexcept
    {
        startTime = std::chrono::high_resolution_clock::now();
    }

    // Devuelve el tiempo transcurrido en segundos desde el inicio del temporizador
    double cycleSecs() const
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - startTime;
        return elapsedTime.count();
    }

    // Devuelve true si ha pasado el tiempo suficiente para un ciclo (según el FPS objetivo)
    bool cyclePassed() const
    {
        return cycleSecs() >= (1.0 / fps);
    }
};
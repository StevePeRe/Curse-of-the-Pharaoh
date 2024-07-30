#pragma once
// libs
#include <engines/audio/AudioInstance.hpp>
#include <vector>
#include <memory>
#include <glm/vec3.hpp>

struct AudioInstance
{

    enum class AudioState : int
    {
        PLAYING,
        PAUSED,
        STOPPED
    };

    virtual ~AudioInstance() = default;

    AudioInstance &Play()
    {
        state = playVirtual();
        return *this;
    }

    void Pause()
    {
        state = pauseVirtual();
    }

    void Resume()
    {
        state = resumeVirtual();
    }

    void Stop()
    {
        state = stopVirtual();
    }

    virtual AudioInstance &SetVolume(float value) = 0;

    virtual AudioInstance &Set3DPosition(glm::vec3 position, glm::vec3 direction) = 0;

    virtual void UpdateStatus() = 0;

    AudioState GetState()
    {
        return state;
    }

protected:
    AudioState state{AudioState::STOPPED};

    virtual AudioState playVirtual() = 0;
    virtual AudioState pauseVirtual() = 0;
    virtual AudioState resumeVirtual() = 0;
    virtual AudioState stopVirtual() = 0;
};
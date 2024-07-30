#pragma once
// raiz
#include "AudioEngine.hpp"

struct FMOD_STUDIO_EVENTDESCRIPTION;
struct FMOD_STUDIO_EVENTINSTANCE;
struct FMOD_STUDIO_BANK;
struct FMOD_STUDIO_SYSTEM;
struct FMOD_SYSTEM;

struct FMODEngine : AudioEngine
{
    void init() override final;
    void update() override final;
    AudioInstance *createInstance(const char* soundTag, const char *path) override final;
    std::vector<AudioInstance*> getInstances(const char *soundTag) override final;

    void setListener(glm::vec3 position, glm::vec3 direction, glm::vec3 up) override final;

private:
    FMOD_STUDIO_EVENTDESCRIPTION *eventDescription{nullptr};
    FMOD_STUDIO_EVENTINSTANCE *eventInstance{nullptr};

    FMOD_STUDIO_BANK *masterBank{nullptr};

    FMOD_SYSTEM *coreSystem{nullptr};

    static void releaseSystem(FMOD_STUDIO_SYSTEM *system);

    using FMODSystem = std::unique_ptr<FMOD_STUDIO_SYSTEM, void (*)(FMOD_STUDIO_SYSTEM *)>;

    inline static FMODSystem fmodSystem{nullptr, releaseSystem};

    bool Initialized{false};

};

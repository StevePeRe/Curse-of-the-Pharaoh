#pragma once

#include <string>
#include "AudioInstance.hpp"

struct FMOD_STUDIO_EVENTINSTANCE;
struct FMODInstance : public AudioInstance
{
    explicit FMODInstance(FMOD_STUDIO_EVENTINSTANCE *eventInstance);

    ~FMODInstance();

    AudioInstance &SetVolume(float value) override final;

    AudioInstance &Set3DPosition(glm::vec3 position, glm::vec3 direction) override final;

    void UpdateStatus() override final;

private:
    FMOD_STUDIO_EVENTINSTANCE *eventInstance{nullptr};

protected:
    AudioState playVirtual() override final;
    AudioState pauseVirtual() override final;
    AudioState resumeVirtual() override final;
    AudioState stopVirtual() override final;
};
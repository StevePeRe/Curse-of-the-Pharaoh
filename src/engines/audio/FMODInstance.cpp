#include "FMODInstance.hpp"

#include <FMOD/src/fmod.h>
#include <FMOD/src/fmod_studio.h>

#include <iostream>

FMODInstance::FMODInstance(FMOD_STUDIO_EVENTINSTANCE *eventInstance) : eventInstance{eventInstance} {}

FMODInstance::~FMODInstance()
{
    Stop();
    FMOD_Studio_EventInstance_Release(eventInstance);
}

AudioInstance::AudioState FMODInstance::playVirtual()
{
    FMOD_Studio_EventInstance_Start(eventInstance);
    state = AudioState::PLAYING;
    return state;
}

AudioInstance::AudioState FMODInstance::pauseVirtual()
{
    if (state == AudioState::PLAYING)
    {
        FMOD_Studio_EventInstance_SetPaused(eventInstance, true);
        state = AudioState::PAUSED;
    }
    return state;
}

AudioInstance::AudioState FMODInstance::resumeVirtual()
{
    if (state == AudioState::PAUSED)
    {
        FMOD_Studio_EventInstance_SetPaused(eventInstance, false);
        state = AudioState::PLAYING;
    }
    return state;
}

AudioInstance::AudioState FMODInstance::stopVirtual()
{
    if (state != AudioState::STOPPED)
    {
        FMOD_Studio_EventInstance_Stop(eventInstance, FMOD_STUDIO_STOP_IMMEDIATE);
        state = AudioState::STOPPED;
    }
    return state;
}

AudioInstance &FMODInstance::SetVolume(float value)
{
    FMOD_Studio_EventInstance_SetVolume(eventInstance, value);
    return *this;
}

AudioInstance &FMODInstance::Set3DPosition(glm::vec3 position, glm::vec3 direction)
{
    FMOD_3D_ATTRIBUTES eventAttributes{
        FMOD_VECTOR{-position.x, position.y, position.z},
        FMOD_VECTOR{0.0f, 0.0f, 0.0f},
        FMOD_VECTOR{direction.x, direction.y, direction.z},
        FMOD_VECTOR{0, 1, 0}};

    FMOD_Studio_EventInstance_Set3DAttributes(eventInstance, &eventAttributes);
}

void FMODInstance::UpdateStatus()
{
    FMOD_STUDIO_PLAYBACK_STATE st; // es C
    FMOD_Studio_EventInstance_GetPlaybackState(eventInstance, &st);
    // asigno los estados de las instancias segun FMOD
    switch (st)
    {   
    case FMOD_STUDIO_PLAYBACK_STOPPED:
        state = AudioState::STOPPED;
        break;
    case FMOD_STUDIO_PLAYBACK_PLAYING:
        state = AudioState::PLAYING;
        break;
    /* case FMOD_STUDIO_PLAYBACK_STOPPING: // creo que stopping es pause
        state = AudioState::PAUSED;
        break; */
    default:
        break;
    }
}

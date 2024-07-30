#pragma once
// cmp
#include <ecs/cmp/component.hpp>
// util
#include <ecs/util/globals.hpp>
// libs
#include <vector>
#include <cstdint>
#include <engines/audio/AudioInstance.hpp>

struct AudioSystem;

struct AudioComponent : ECS::Component
{
    explicit AudioComponent(std::size_t eID)
        : ECS::Component(eID){

          };

    static std::size_t getComponentTypeID() noexcept
    {
        return static_cast<std::size_t>(19);
    }

    AudioComponent &AddAudioInstance(const char *soundTag, AudioInstance *audio)
    {
        auto itr = soundMap.find(soundTag);
        if (itr == soundMap.end())
            soundMap.emplace(soundTag, audio);
        else
            std::cout << "\n**** ERROR al añadir sonido" << std::endl;
        return *this;
    }

    AudioComponent &play(const char *soundTag)
    {
        AudioInstance *instance = getAudioInstance(soundTag);
        if (instance)
        {
            
            instance->Play();
            
        }
        return *this;
    }

    AudioComponent &pause(const char *soundTag)
    {
        AudioInstance *instance = getAudioInstance(soundTag);
        if (instance)
        {
            instance->Pause();
        }
        return *this;
    }

    AudioComponent &stop(const char *soundTag)
    {
        AudioInstance *instance = getAudioInstance(soundTag);
        if (instance)
        {
            instance->Stop();
        }
        return *this;
    }

    AudioComponent &setVolume(const char *soundTag, float value)
    {
        AudioInstance *instance = getAudioInstance(soundTag);
        if (instance)
        {
            instance->SetVolume(value);
        }
        return *this;
    }

    AudioComponent &setSpatial(const char *soundTag, bool value)
    {
        auto itr = soundMap.find(soundTag);
        if (itr != soundMap.end())
        {
            if (value)
                spatialSounds.emplace_back(itr->second);
            else
            {
                for (auto itrSpatial = spatialSounds.begin(); itrSpatial != spatialSounds.end(); ++itrSpatial)
                    if (*itrSpatial == itr->second)
                        spatialSounds.erase(itrSpatial);
            }
        }
        else
            std::cout << "\nERROR SET SPATIAL SOUND, NO SE ENCUENTRA EL SONIDO: " << soundTag;
        return *this;
    }

    AudioInstance *getAudioInstance(const char *soundTag)
    {
        auto itr = soundMap.find(soundTag);
        if (itr != soundMap.end())
            return itr->second;
        return nullptr;
    }

    std::unordered_map<std::string, AudioInstance *> getSoundMap(){ return soundMap; }

private:
    std::unordered_map<std::string, AudioInstance *> soundMap{};

    friend AudioSystem;
    std::vector<AudioInstance *> spatialSounds{};
};
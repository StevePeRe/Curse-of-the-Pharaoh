#pragma once
// libs
#include <engines/audio/AudioInstance.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

struct AudioEngine
{
    virtual ~AudioEngine() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual AudioInstance *createInstance(const char *soundTag, const char *path) = 0;
    virtual std::vector<AudioInstance *> getInstances(const char *soundTag) = 0;

    virtual void setListener(glm::vec3 position, glm::vec3 direction, glm::vec3 up) = 0;

    void stopAll()
    {
        for (auto &instances : audioMap)
            for (auto &soundInstance : instances.second)
                soundInstance->Stop();
    }

    void cleanAll()
    {
        audioMap.clear();
    }

protected:
    std::unordered_map<std::string, std::vector<std::unique_ptr<AudioInstance>>> audioMap{};
};
#include <game/sys/audio.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/audioComponent.hpp>

#include <game/cmp/physicsComponent.hpp>

#include <engines/audio/AudioEngine.hpp>

#include <engines/graphic/T_ECamera.hpp>

bool AudioSystem::update(ECS::EntityManager &em, AudioEngine &ae, TNode *currentCamera)
{
    // Update camera listener
    if (currentCamera != lastCameraActive)
    {
        auto *camera = currentCamera->getEntity<T_ECamera>();
        ae.setListener(currentCamera->getPosition(), camera->getTarget(), camera->getUp());
    }

    // Update sounds
    for (auto &audio : em.getComponents<AudioComponent>())
    {
        auto *entity = em.getEntityByID(audio.getEntityID());
        auto *physics = entity->getComponent<PhysicsComponent>();

        // Update sounds position
        if (physics)
        {
            glm::vec3 soundDirection = glm::normalize(currentCamera->getPosition() - physics->position);

            for (auto itr : audio.spatialSounds)
            {
                itr->Set3DPosition(physics->position, soundDirection);
            }
        }

        /* for(const auto& par : audio.getSoundMap()) {
            if(par.second && par.second->GetState() == AudioInstance::AudioState::PLAYING){
                std::cout << "paro la musica\n";
                par.second->Stop();
            }
        } */

    }

    // Update engine
    ae.update();

    return true;
}
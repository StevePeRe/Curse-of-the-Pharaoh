#define GLM_ENABLE_EXPERIMENTAL // necesario para calcular la rotacion
#include <game/sys/input.hpp>
// cmp
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/colliderComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/animationComponent.hpp>
#include <game/cmp/audioComponent.hpp>
// engines
#include <engines/physics/body/bodyComponent.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
#include <game/man/event/eventManager.hpp>
// triggers
// util
// libs
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <glm/gtx/vector_angle.hpp>

// Graphic
#include <engines/graphic/GraphicEngine.hpp>

// Read txt
#include <fstream>
#include <JSON/src/json.hpp>

// Este input solo afecta al player a nadie mas
void InputSystem::update(ECS::EntityManager &em, GraphicEngine &ge)
{
    auto current_time = std::chrono::steady_clock::now();
    // [[maybe_unused]] auto &eventM = em.getSingletonComponentEM<EventManager>();
    // obtengo el HUD
    auto &HUD = em.getSingletonComponentEM<HUDComponent>();
    nlohmann::json datos_general;

    for (auto &input : em.getComponents<InputComponent>())
    {
        auto *e = em.getEntityByID(input.getEntityID());

        if (e)
        {
            auto *phy = e->getComponent<PhysicsComponent>();
            auto *beh = e->getComponent<ShotBehaviourComponent>(); // para controlar el disparo
            auto *inv = e->getComponent<InventoryComponent>();     // revisar objetos
            // auto *col = e->getComponent<ColliderComponent>();
            auto *rend = e->getComponent<RenderComponent>();
            auto *body = e->getComponent<bodyComponent>();
            auto *audio = e->getComponent<AudioComponent>();

            if (phy && body && rend && beh && inv && audio)
            {
                if (player_bend)
                    e->setState(ECS::EntityState::IDLE);
                else
                    e->setState(ECS::EntityState::IDLE_CROUCH);

                beh->state = ECS::BehaviourState::IDLEB_S; // reinicio de estado de disparo

                if (ge.isKeyReleased(GLFW_KEY_F1))
                {
                    ge.initImGui_ = true;
                }

                // reseteo de variable
                // uso el objeto del inventario
                // o a lo mejor todo tiene que ser con la E, y cada vez la intente usar verificar
                // TODO que todo lo que se pueda interactuar conla E, que lo ponga al colisinoar con eso
                input.interaction = false;
                if (ge.isKeyReleased(GLFW_KEY_E))
                {
                    input.interaction = true;
                }

                // coger objetos
                if (ge.isKeyReleased(GLFW_KEY_F))
                    inv->putIntoTheInventory(em, ge);
                // e->setState(ECS::EntityState::C_OBJETO);

                input.useInventory = false;
                if (ge.isKeyReleased(GLFW_KEY_Q))
                {
                    input.useInventory = true;
                }

                if (ge.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
                {
                    auto *anim_ = e->getComponent<AnimationComponent>();
                    anim_->anim->setAnimation(anim_->crouch);
                    e->setState(ECS::EntityState::IDLE_CROUCH);

                    player_bend = !player_bend;
                }

                if (!player_bend)
                {
                    rend->h = rend->player_bend;
                    body->bBox_.yMax = rend->player_bend;
                    maxForceSprint = 5000.f;
                }
                else
                {
                    rend->h = rend->player_noBend;
                    body->bBox_.yMax = rend->player_noBend;
                    // por la perspectiva de la camra no cambia el valor en todos los angulos
                    ge.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? phy->maxForceSprint = 16500.f : phy->maxForceSprint = 13000.f;
                }

                // pulsar la X para borrar el mensaje
                input.message_erase = false;
                if (ge.isKeyReleased(GLFW_KEY_X))
                {
                    // cerrar mensaje
                    HUD.clearMessage(); // borrar el mensaje en el HUD DIALOGO
                    input.message_erase = true;
                    HUD.clearQuickMessage(); // borrar mensaje rapido
                }

                if (ge.isKeyDown(GLFW_KEY_SPACE))
                {
                    // reproducir mas rapido el mensaje
                    HUD.framesCounter += 8;
                }

                ////////////////////////////////////////////////////////////////////////
                // CAMARA
                if (ge.isKeyDown(GLFW_KEY_1))
                    CameraComponent::currentCam = ECS::ID_MOVABLE_CAM;
                if (ge.isKeyDown(GLFW_KEY_2))
                    CameraComponent::currentCam = ECS::ID_INIT_CAM;

                if (CameraComponent::currentCam == ECS::ID_MOVABLE_CAM)
                {
                    if (ge.isKeyDown(GLFW_KEY_UP))
                        e->setState(ECS::EntityState::CAM_MOVING_FORWARDS);
                    else if (ge.isKeyDown(GLFW_KEY_DOWN))
                        e->setState(ECS::EntityState::CAM_MOVING_BACKWARDS);
                    else if (ge.isKeyDown(GLFW_KEY_LEFT))
                        e->setState(ECS::EntityState::CAM_MOVING_LEFT);
                    else if (ge.isKeyDown(GLFW_KEY_RIGHT))
                        e->setState(ECS::EntityState::CAM_MOVING_RIGTH);

                    if (ge.isKeyDown(GLFW_KEY_L))
                        e->setState(ECS::EntityState::CAM_ROTATE_LEFT);
                    else if (ge.isKeyDown(GLFW_KEY_J))
                        e->setState(ECS::EntityState::CAM_ROTATE_RIGTH);
                    else if (ge.isKeyDown(GLFW_KEY_I))
                        e->setState(ECS::EntityState::CAM_ROTATE_FORWARDS);
                    else if (ge.isKeyDown(GLFW_KEY_K))
                        e->setState(ECS::EntityState::CAM_ROTATE_BACKWARDS);

                    if (ge.isKeyDown(GLFW_KEY_SPACE))
                        e->setState(ECS::EntityState::CAM_UP);
                    else if (ge.isKeyDown(GLFW_KEY_RIGHT_SHIFT))
                        e->setState(ECS::EntityState::CAM_DOWN);

                    if (ge.isKeyDown(GLFW_KEY_Y))
                        e->setState(ECS::EntityState::CAM_ZOOM_DOWN);
                    else if (ge.isKeyDown(GLFW_KEY_H))
                        e->setState(ECS::EntityState::CAM_ZOOM_UP);

                    if (ge.isKeyDown(GLFW_KEY_G))
                        e->setState(ECS::EntityState::CAM_RESET);
                }

                ////////////////////////////////////////////////////////////////////////
                // MOVIMIENTO
                if (!(input.blockInput) && !aim)
                {
                    OrientationPlayer(*e, ge);
                }

                // hacer con el behaviourCopmonent el arma que tienes en la mano en todo momento, porque al principio vas a estar sin arma
                if (ge.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
                {
                    aim = true;
                    if (ge.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && current_time - last_shot_time >= beh->shoot_cooldown)
                    {
                        // para despues el estado shotting puede estar para las IAs cuando quieran disparar
                        if (beh->shot_ammo > 0)
                        {
                            beh->state = ECS::BehaviourState::SHOTTING;
                            last_shot_time = current_time;
                            beh->shot_ammo--;
                        }
                        else
                        {
                            // HUD.setQuickMessage("No me quedan más balas, voy a intentar buscar por el mapa *a ver si encuentro munición.*");
                            HUD.setQuickMessage("No me quedan mas balas, voy a intentar buscar por el mapa *a ver si encuentro municion.");
                            HUD.showQuickMessage();
                        }
                    }
                }
                else
                {
                    aim = false;
                }

                // ///////////////////////////////////
                // INVENTARIO
                if (inv->getInventory().size() > 0)
                {
                    if (ge.getMouseWheelMove() > 0)
                    {
                        // if(ge.isKeyReleased(GLFW_KEY_J)){
                        inv->index++;
                        if (inv->index > static_cast<int16_t>(inv->getInventory().size()) - 1)
                        {
                            inv->index = 0;
                        }
                        inv->setObjectHand(inv->getInventory().at(inv->index));
                        // std::cout << "valor inventario: " << inv->getInventory().at(index).first << "\n";
                    }
                    else if (ge.getMouseWheelMove() < 0)
                    {
                        // } else if(ge.isKeyReleased(GLFW_KEY_L)){
                        inv->index--;
                        if (inv->index < 0)
                        {
                            inv->index = static_cast<int16_t>(inv->getInventory().size()) - 1;
                        }
                        inv->setObjectHand(inv->getInventory().at(inv->index));
                        // std::cout << "valor inventario: " << inv->getInventory().at(index).first << "\n";
                    }
                }

                input.useAMMO = false;
                if (ge.isKeyReleased(GLFW_KEY_R))
                {
                    input.useAMMO = true;
                }

                if (e->getType() == ECS::EntityType::PLAYER)
                {
                    auto *anim_ = e->getComponent<AnimationComponent>();
                    checkAnimation(*e, anim_, *audio);
                }
            }
        }
    }
}

void InputSystem::OrientationPlayer(ECS::Entity &e, GraphicEngine &ge)
{
    int lastKey = 0;               // cero que no hace falta
    float forceMagnitude = 4000.f; // fuerza con la que se mueve el personaje

    auto *camGL = ge.getActiveCamera();
    auto *rend = e.getComponent<RenderComponent>();
    auto *phy = e.getComponent<PhysicsComponent>();

    if (!rend || !phy)
        return;

    // saber target de la camara
    if (camGL && camGL->getEntity<T_ECamera>())
    {
        cameraForward = camGL->getEntity<T_ECamera>()->getTarget() - camGL->getEntity<T_ECamera>()->getPosition();
        cameraForward.y = 0.f;
        cameraForward = glm::normalize(cameraForward);
        cameraRigth = glm::normalize(glm::cross(cameraForward, glm::vec3(0.f, 1.f, 0.f)));
        if (glm::length(lastTarget) == 0) // para incializarlo
            lastTarget = cameraForward;
    }

    glm::vec3 movementDirection(0.f);

    if (ge.isKeyDown(GLFW_KEY_D))
    {
        e.getComponent<InputComponent>()->lastOrientation = GLFW_KEY_D;
        if (e.getType() == ECS::EntityType::PLAYER)
            e.setState(ECS::EntityState::MOVING_LEFT);
        lastKey++;
        movementDirection += cameraRigth;
        /* movementDirection.x += 1; */
    }
    if (ge.isKeyDown(GLFW_KEY_A))
    {
        e.getComponent<InputComponent>()->lastOrientation = GLFW_KEY_A;
        if (e.getType() == ECS::EntityType::PLAYER)
            e.setState(ECS::EntityState::MOVING_LEFT);
        lastKey++;
        movementDirection += -cameraRigth;
        /* movementDirection.x += -1; */
    }

    if (ge.isKeyDown(GLFW_KEY_S))
    {
        e.getComponent<InputComponent>()->lastOrientation = GLFW_KEY_S;
        if (e.getType() == ECS::EntityType::PLAYER)
            e.setState(ECS::EntityState::MOVING_LEFT);
        lastKey++;
        movementDirection += -cameraForward;
        /* movementDirection.z += 1; */
    }
    if (ge.isKeyDown(GLFW_KEY_W))
    {
        e.getComponent<InputComponent>()->lastOrientation = GLFW_KEY_W;
        if (e.getType() == ECS::EntityType::PLAYER)
            e.setState(ECS::EntityState::MOVING_LEFT);
        lastKey++;
        movementDirection += cameraForward;
        /* movementDirection.z += -1; */
    }

    if (lastRegisterKey != lastKey)
        lastTarget = cameraForward;

    // Al pulsar cualquier tecla
    if (lastKey != 0)
    {
        // direccion del personaje
        glm::vec3 direction{0.f};
        if (lastTarget == cameraForward)
        {
            direction = movementDirection;
            lastDirection = movementDirection;
        }
        else
        {
            direction = lastDirection;
        }

        phy->ownForces.x += direction.x * /*movementDirection.x * */ forceMagnitude;
        phy->ownForces.z += direction.z * /* movementDirection.z * */ forceMagnitude;
        /* std::cout << "ownForces x: " << phy->ownForces.x << " , z: " << phy->ownForces.z << "\n";  */
        /* std::cout << "direction x: " << direction.x << " , z: " << direction.z << "\n";  */
        phy->forceDirection = direction;
        // std::cout << "phy->forceDirection x: " << phy->forceDirection.x << " , z: " << phy->forceDirection.z << "\n";
    }

    lastRegisterKey = lastKey;
}

void InputSystem::checkAnimation(ECS::Entity &e, AnimationComponent *anim_, AudioComponent &audio)
{
    if (e.getType() == ECS::EntityType::PLAYER && e.getState() == ECS::EntityState::IDLE && aim == false)
    {
        if (anim_->anim->checkEndAnimation() || anim_->anim->getCurrentAnimation() != anim_->idle)
            anim_->anim->setAnimation(anim_->idle);
    }
    else if (e.getType() == ECS::EntityType::PLAYER && e.getState() == ECS::EntityState::MOVING_LEFT && aim == false)
    {
        if (player_bend)
        {
            if (anim_->anim->checkEndAnimation() || anim_->anim->getCurrentAnimation() != anim_->walk)
                anim_->anim->setAnimation(anim_->walk);
        }
        else
        {
            if (anim_->anim->checkEndAnimation() || anim_->anim->getCurrentAnimation() != anim_->crouchWalk)
                anim_->anim->setAnimation(anim_->crouchWalk);
        }

        if (!(audio.getAudioInstance("WALKING")->GetState() == AudioInstance::AudioState::PLAYING))
        {
            audio.play("WALKING");
        }
    }
    else if (e.getType() == ECS::EntityType::PLAYER && e.getState() == ECS::EntityState::IDLE_CROUCH && aim == false)
    {
        if (anim_->anim->getCurrentAnimation() != anim_->crouch)
            anim_->anim->setAnimation(anim_->crouch);
    }
    else if (e.getType() == ECS::EntityType::PLAYER && aim && player_bend)
    {
        // if (anim_->anim->getCurrentAnimation() != anim_->aim)
        //     anim_->anim->setAnimation(anim_->aim);
    }
}
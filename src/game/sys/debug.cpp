#include <game/sys/debug.hpp>
// man
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/inputComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/powerUpComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/aiComponent.hpp>
// body
#include <engines/physics/body/bodyComponent.hpp>
// graphics
#include <engines/graphic/GraphicEngine.hpp>
// libs
#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>

#include <JSON/src/json.hpp>

#include <iostream>

void DebugSystem::update(ECS::EntityManager &em, GraphicEngine &ge)
{
    if (ge.initImGui_)
    {
        if (init_ == false)
        {
            close = true;
            ge.initImGui(firstTime);
            init_ = true;
            ge.initImGui_ = true;
        }

        nlohmann::json datos_general;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        datos_general = manageData.leerJSON("./media/levels/general.json");

        auto &io{ImGui::GetIO()};

        if (close)
        {
            // El begin crea ventanas
            ImGui::Begin("DEBUG Window", &close); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                                                  // Aqui se construye todo el contenido de la ventana de ImGUI

            // ImGui::Image(/* añadir img */);
            ImGui::Text("------ DATOS DEL JUEGO ------");
            ImGui::Text("FPS: %2f", io.Framerate);
            ImGui::Text("ms/f: %2f", 1000.0f / io.Framerate);

            ImGui::Text("\n");

            // FILTRADO
            ImGui::Combo(" - ", &entityTypeSelected, entityType, IM_ARRAYSIZE(entityType));
            ImGui::SameLine();
            if (ImGui::Button("FILTRAR"))
            {
                if (!(vecEntities.empty()))
                    vecEntities.clear();

                for (auto &e : em.getEntityVector())
                {
                    if (e.getType() == entityTypeList[entityTypeSelected])
                    {
                        vecEntities.emplace_back(e.getId());
                    }
                }
                filtered = true;
            }

            if (filtered)
            {
                ImGui::InputInt("ENTIDAD", &ID_ent, 1);
                ID_ent = std::clamp(ID_ent, 1, static_cast<int>(vecEntities.size()-1)); // no se porque no pilla la ultima entidad
                auto *e = em.getEntityByID(vecEntities[ID_ent]);
                if (e)
                {
                    /* ImGui::End();
                    return; */
                    ImGui::Text("Borrar entidad: ");
                    ImGui::SameLine();

                    if (ImGui::Button("borrar"))
                    {
                        e->mark4destruction();
                        /* ImGui::End();
                        return; */
                    }
                    // auto *e = em.getEntityByTAG(ECS::EntityTAG::E_PLAYER);

                    auto *phy = e->getComponent<PhysicsComponent>();
                    auto *body = e->getComponent<bodyComponent>();
                    auto *rn = e->getComponent<RenderComponent>();
                    auto *inv = e->getComponent<InventoryComponent>();
                    auto *heal = e->getComponent<HealthComponent>();
                    auto *perc = e->getComponent<PerceptionComponent>();
                    auto *beh = e->getComponent<ShotBehaviourComponent>();
                    auto *powr = e->getComponent<PowerUpComponent>();
                    auto *ai = e->getComponent<AIComponent>();

                    ImGui::Text("\n---- CMPS ENTIDADES ----");

                    if (phy)
                    {
                        // TODO modificar y enseñar las fisicas en una pestaña aparte
                        // TODO modificar el rango y todo del raycsat
                        
                        // si tieen physics la busco
                        CameraComponent::currentCam = ECS::ID_MOVABLE_CAM;
                        auto *entCam = em.getEntityByTAG(ECS::EntityTAG::MOVIBLE_CAM);

                        if (entCam)
                        {
                            auto *cam = entCam->getComponent<CameraComponent>();
                            if (cam)
                            {
                                cam->cameraPosition.x = phy->position.x - 1.1f;
                                cam->cameraPosition.y = phy->position.y + 3.5f;
                                cam->cameraPosition.z = phy->position.z;

                                cam->cameraTarget.x = phy->position.x;
                                cam->cameraTarget.y = phy->position.y;
                                cam->cameraTarget.z = phy->position.z;

                                cam->cameraUp.x = 0.f;
                                cam->cameraUp.y = 0.998f;
                                cam->cameraUp.z = 0.f;
                                show_hitbox = true;
                            }
                        }

                        if (ImGui::Button("CMP PHYSICS"))
                        {
                            physics = !physics;
                        }
                    }

                    if (physics)
                    {
                        /* ImGui::InputText("TAG: ", text, IM_ARRAYSIZE(text));
                        // Mostrar el texto introducido
                        ImGui::Text("tag a buscar: %s", text); */
                        if (ImGui::Button("Mostrar Fuerzas"))
                        {
                            show_forces = !show_forces;
                        }

                        if(show_forces){
                            ImGui::Begin("Fuerzas window");

                            ImGui::Text("Fuerza");
                            ImGui::Text(TextFormat("  - Fuerza X: %f", phy->force.x).c_str());
                            ImGui::Text(TextFormat("  - Fuerza Y: %f", phy->force.y).c_str());
                            ImGui::Text(TextFormat("  - Fuerza Z: %f", phy->force.z).c_str());

                            ImGui::Text("Aceleracion");
                            ImGui::Text(TextFormat("  - Aceleracion X: %f", phy->velocity.x).c_str());
                            ImGui::Text(TextFormat("  - Aceleracion Y: %f", phy->velocity.y).c_str());
                            ImGui::Text(TextFormat("  - Aceleracion Z: %f", phy->velocity.z).c_str());

                            ImGui::Text("Velocidad");
                            ImGui::Text(TextFormat("  - Velocidad X: %f", phy->velocity.x).c_str());
                            ImGui::Text(TextFormat("  - Velocidad Y: %f", phy->velocity.y).c_str());
                            ImGui::Text(TextFormat("  - Velocidad Z: %f", phy->velocity.z).c_str());

                            ImGui::Text("Fuerza Direccion");
                            ImGui::Text(TextFormat("  - X: %f", phy->forceDirection.x).c_str());
                            ImGui::Text(TextFormat("  - Y: %f", phy->forceDirection.y).c_str());
                            ImGui::Text(TextFormat("  - Z: %f", phy->forceDirection.z).c_str());

                            ImGui::InputFloat("Max. Velocidad Sprint", &changeSprintVel);
                            // float xyz[3] = {xyz[0], xyz[1], xyz[2]};
                            if (ImGui::Button("CAMBIAR Sprint"))
                            {
                                phy->maxForceSprint = changeSprintVel;
                            }

                            if (ImGui::Button("CERRAR F."))
                            {
                                show_forces = false;
                            }
                            ImGui::End();
                        }

                        ImGui::Text(TextFormat("  - Pos X: %f", phy->position.x).c_str());
                        ImGui::Text(TextFormat("  - Pos Y: %f", phy->position.y).c_str());
                        ImGui::Text(TextFormat("  - Pos Z: %f", phy->position.z).c_str());
                        ImGui::InputFloat3("X,Y,Z", player_pos);
                        // float xyz[3] = {xyz[0], xyz[1], xyz[2]};
                        if (ImGui::Button("CAMBIAR POSICION"))
                        {
                            phy->position = glm::vec3{player_pos[0], player_pos[1], player_pos[2]};
                        }

                        ImGui::Text("\n");

                        ImGui::Text(TextFormat("  - Hitbox: %f, %f, %f", body->bBox_.xMax, body->bBox_.yMax, body->bBox_.zMax).c_str());
                        /* ImGui::Checkbox("Mostrar HitBox", &show_hitbox); */

                        ImGui::InputFloat2("ANCHO, LARGO", player_hitbox);
                        // float xyz[3] = {xyz[0], xyz[1], xyz[2]};
                        if (ImGui::Button("CAMBIAR HITBOX"))
                        {
                            body->bBox_.xMax = player_hitbox[0];
                            rn->w = body->bBox_.xMax;
                            body->bBox_.zMax = player_hitbox[1];
                            rn->d = body->bBox_.zMax;
                        }

                        ImGui::Text("\n");

                        ImGui::Checkbox("Usar gravedad", &(phy->use_gravity));

                        ImGui::Text(TextFormat("  - Masa: %f", phy->mass).c_str());
                        ImGui::InputFloat("NUEVA MASA", &masa);
                        if (ImGui::Button("CAMBIAR MASA"))
                        {
                            phy->mass = masa;
                        }

                        ImGui::Checkbox("Usar impulso", &(phy->hasImpulse));

                        // ImGui::Text("Player gravedad: %s",phy->use_gravity ? "true" : "false");
                        ImGui::Text(TextFormat("  - Restitucion: %f", phy->restitution).c_str());
                        ImGui::InputFloat("RESTITUCION", &restitucion);
                        if (ImGui::Button("CAMBIAR RESTITUCION"))
                        {
                            phy->restitution = restitucion;
                        }
                        ImGui::Text(TextFormat("  - Friccion estatica: %f", phy->staticFriction).c_str());
                        ImGui::InputFloat("STATIC_FRICTION", &staticFriction);
                        if (ImGui::Button("CAMBIAR STATIC_FRICTION"))
                        {
                            phy->staticFriction = staticFriction;
                        }
                        ImGui::Text(TextFormat("  - Friccion dinamica: %f", phy->dynamicFriction).c_str());
                        ImGui::InputFloat("DYNAMIC_FRICTION", &dynamicFriction);
                        if (ImGui::Button("CAMBIAR DYNAMIC_FRICTION"))
                        {
                            phy->dynamicFriction = dynamicFriction;
                        }

                        // ENSEÑAR EL RAYCAST
                    }

                    if (show_hitbox)
                    {
                        ge.drawBoundingBox({phy->position.x, phy->position.y, phy->position.z}, rn->w,
                                           rn->h, rn->d, {1.f, 0.f, 0.f});
                    }

                    /* ImGui::Text("----------------------------------\n"); */

                    if (rn)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP RENDER"))
                        {
                            render = !render;
                        }
                    }

                    if (render)
                    {
                        // informacion render
                        ImGui::Text("Direccion modelo\n");
                        ImGui::Text(TextFormat("  - X: %f", ge.getNode(rn->node)->getModelDirection().x).c_str());
                        ImGui::Text(TextFormat("  - Y: %f", ge.getNode(rn->node)->getModelDirection().y).c_str());
                        ImGui::Text(TextFormat("  - Z: %f", ge.getNode(rn->node)->getModelDirection().z).c_str());
                    }

                    /* ImGui::Text("----------------------------------\n"); */

                    if (inv)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP INVENTARIO"))
                        {
                            inventory = !inventory;
                        }
                    }

                    if (inventory)
                    {
                        // informacion
                        ImGui::InputInt("Añadir municion", &add_ammo, 1);
                        add_ammo = std::clamp(add_ammo, 0, 10);
                        if (ImGui::Button("APLICAR MUN."))
                        {
                            if (add_ammo != 0)
                                inv->ApplyQuantity(ECS::EntityTAG::AMMO, static_cast<int16_t>(add_ammo));
                            else
                                inv->eraseElement(ECS::EntityTAG::AMMO);
                        }

                        ImGui::InputInt("Añadir BCura", &add_bigHeal, 1);
                        add_bigHeal = std::clamp(add_bigHeal, 0, 10);
                        if (ImGui::Button("APLICAR B.HEAL"))
                        {
                            if (add_bigHeal != 0)
                                inv->ApplyQuantity(ECS::EntityTAG::BIG_HEAL, static_cast<int16_t>(add_bigHeal));
                            else
                                inv->eraseElement(ECS::EntityTAG::BIG_HEAL);
                        }

                        ImGui::InputInt("Añadir SCura", &add_smallHeal, 1);
                        add_smallHeal = std::clamp(add_smallHeal, 0, 10);
                        if (ImGui::Button("APLICAR S.HEAL"))
                        {
                            if (add_smallHeal != 0)
                                inv->ApplyQuantity(ECS::EntityTAG::SMALL_HEAL, static_cast<int16_t>(add_smallHeal));
                            else
                                inv->eraseElement(ECS::EntityTAG::SMALL_HEAL);
                        }
                    }

                    /* ImGui::Text("----------------------------------\n"); */

                    if (heal)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP VIDA"))
                        {
                            health = !health;
                        }
                    }

                    if (health)
                    {
                        // informacion
                        ImGui::SliderFloat("Vida", &h_health, 1.f, 100.f);
                        if (ImGui::Button("APLICAR"))
                        {
                            heal->health = h_health;
                        }

                        ImGui::Checkbox("  - Inmunidad", &(heal->hasInmunity));
                        if (heal->hasInmunity)
                        {
                            ImGui::InputFloat("Tiempo inmunidad", &inmunityTime);
                            if (ImGui::Button("APLICAR"))
                            {
                                heal->inmunityTime = inmunityTime;
                            }
                        }
                    }

                    /* ImGui::Text("----------------------------------\n"); */

                    if (perc)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP PERCEPCION"))
                        {
                            perception = !perception;
                        }
                    }

                    if (perception)
                    {
                        ImGui::Checkbox("  - Percep. Vista", &(perc->hasSigth));

                        ImGui::Checkbox("  - Usar Raycast", &(perc->useRaycast));
                        if (perc->useRaycast)
                        {
                            ImGui::SliderFloat("Rango raycast", &(perc->raycast.range), 1.f, 15.f);

                            ImGui::Checkbox("  - Mostrar Raycast", &show_raycast);
                            if (show_raycast)
                            {
                                // fix
                                auto endV = perc->raycast.origin + (perc->raycast.range * perc->raycast.direction);
                                // std::cout << "origin " << endV.x << " , " << endV.y << " , " << endV.z << "\n";
                                // std::cout << "direction " << perc->raycast.direction.x << " , " << perc->raycast.direction.y << " , " << perc->raycast.direction.z << "\n";
                                ge.draw3dLine(perc->raycast.origin, endV, {0.53f, 0.81f, 0.59f});
                                /* ge.draw3dLine(phy->position, endV, {0.53f, 0.81f, 0.59f}); */
                            }

                            if(perc->raycast.closestObject.ContainsLayer(LayerRaycast::PLAYER))
                                ImGui::Text("Percibo al Jugador");
                            if(perc->raycast.closestObject.ContainsLayer(LayerRaycast::ENEMY))
                                ImGui::Text("Percibo al enemigo");
                            if(perc->raycast.closestObject.ContainsLayer(LayerRaycast::ENVIRONMENT))
                                ImGui::Text("Percibo objeto del mundo");

                            /* ImGui::Checkbox("  - Capa Jugador", &addLayerPlayer);
                            if (addLayerPlayer) 
                            else  */
                        }

                        // LayerMask layersToDetect{}; poder añadir capas para ver

                        ImGui::Text("\n");

                        ImGui::Checkbox("  - Percep. Oido", &(perc->hasHearing));

                        // radio_sound mejor no modificarlo, habria que modificar el mapa

                        // informacion
                        /* glm::vec3 endVec = perc->origin + perc->direction * perc->range;
                        // std::cout << "endVec: " << endVec.x << " , " << endVec.z << "\n";
                        ge.draw3dLine(perc->origin, endVec, {1.f, 1.f, 1.f}); */
                    }

                    /* ImGui::Text("----------------------------------\n"); */

                    if (powr)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP POWER_UP"))
                        {
                            powerUp = !powerUp;
                        }
                    }

                    if (powerUp)
                    {
                        // informacion
                    }

                    if (beh)
                    {
                        ImGui::Text("----------------------------------\n");
                        if (ImGui::Button("CMP COMPORTAMIENTO"))
                        {
                            shotBeh = !shotBeh;
                        }
                    }

                    if (shotBeh)
                    {
                        // informacion
                    }

                    if (ai)
                    {
                        ImGui::Text("\n----------");
                        switch (ai->enemyType){
                        case 1:
                            ImGui::Text("  - Enemytype: ZOMBIE");
                        break;
                         case 2:
                            ImGui::Text("  - Enemytype: ESCARABAJO");
                        break;
                         case 3:
                            ImGui::Text("  - Enemytype: MOMIA");
                        break;
                         case 4:
                            ImGui::Text("  - Enemytype: MOMIA LABERINTO");
                        break;
                        }
                        ImGui::Text("\n----------");
                        if(ai->running){
                            ImGui::Text("  - Currently running tree: YES");
                        }else{
                            ImGui::Text("  - Currently running tree: NO");
                        }
                        ImGui::Text("\n----------");
                        switch (ai->currentNode){
                        case 1:
                            ImGui::Text("  - Current running node: ACTION ARRIVE");
                        break;
                         case 2:
                            ImGui::Text("  - Current running node: ACTION ATTACK CLOSE");
                        break;
                         case 3:
                            ImGui::Text("  - Current running node: ACTION ATTACK FAR");
                        break;
                         case 4:
                            ImGui::Text("  - Current running node: ACTION CHECK GOAL REACHED");
                        break;
                        case 5:
                            ImGui::Text("  - Current running node: ACTION FIND PATH");
                        break;
                        case 6:
                            ImGui::Text("  - Current running node: ACTION FLEE");
                        break;
                        case 7:
                            ImGui::Text("  - Current running node: ACTION GET GOAL");
                        break;
                        case 8:
                            ImGui::Text("  - Current running node: ACTION IDLE");
                        break;
                        case 9:
                            ImGui::Text("  - Current running node: ACTION MOVE");
                        break;
                        case 10:
                            ImGui::Text("  - Current running node: ACTION SEEK");
                        break;
                        case 11:
                            ImGui::Text("  - Current running node: DECORADOR CHECK DISTANCE");
                        break;
                        case 12:
                            ImGui::Text("  - Current running node: DECORADOR CHECK SB");
                        break;
                        default:
                            ImGui::Text("  - Current running node: ---");
                        break;
                        }
                        ImGui::Text("\n----------");
                        ImGui::Text(TextFormat("  - Distance from player: %f", ai->distPlayer).c_str());

                    }

                    ImGui::Text("\n---- TP MAPA ----");

                    if (ImGui::Button("MOVERSE POR EL MAPA"))
                    {
                        tps = !tps;
                    }
                    if (tps)
                    {
                        if (datos_general["jugador"]["nivel_actual"] == "level_0")
                        {
                            if (ImGui::Button("PRE-PUENTE"))
                            {
                                phy->position = glm::vec3{30.527f, 1.25f, -45.035f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("POS-PUENTE"))
                            {
                                phy->position = glm::vec3{22.784f, 1.25f, -64.489f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("FINAL"))
                            {
                                phy->position = glm::vec3{3.14f, 1.25f, -77.533f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                        }
                        else if (datos_general["jugador"]["nivel_actual"] == "level_1")
                        {
                            if (ImGui::Button("COMEDOR"))
                            {
                                phy->position = glm::vec3{-1.936f, 1.25f, -59.256f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("PILARES"))
                            {
                                phy->position = glm::vec3{-26.781f, 11.003, -72.473f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("LLAVE"))
                            {
                                phy->position = glm::vec3{-48.990f, 11.003f, -96.845};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("PUZZLE"))
                            {
                                phy->position = glm::vec3{-8.649f, 11.003f, -84.088f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                        }
                        else if (datos_general["jugador"]["nivel_actual"] == "level_2")
                        {
                            if (ImGui::Button("BIBLIOTECA"))
                            {
                                phy->position = glm::vec3{42.0f, 18.333f, -11.2f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("ZONA DERECHA"))
                            {
                                phy->position = glm::vec3{42.0f, 18.333f, 37.2f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("ZONA CENTRAL"))
                            {
                                phy->position = glm::vec3{48.74f, 18.333f, 0.66f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                            if (ImGui::Button("PRIMER PASILLO"))
                            {
                                phy->position = glm::vec3{28.201f, -0.062f, -0.123f};
                                // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                            }
                        }
                        /*  if (ImGui::Button("CERRAR TPS"))
                         {
                             tps = false;
                             // ImGui::Text(TextFormat("TP A POSICION: %f, %f, %f", phy->position.x, phy->position.y, phy->position.z).c_str());
                         } */
                    }
                }
            }
            ImGui::Text("\n");

            if (ImGui::Button("CERRAR") || !close)
            {
                close = false;
                init_ = false;
                ge.initImGui_ = false;
                CameraComponent::currentCam = CameraComponent::lastCam;
                ge.closeImGui();
            }

            if (ge.initImGui_)
                ImGui::End();
        }

        if (ge.initImGui_)
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }
}

void DebugSystem::init(GraphicEngine &ge)
{
    // ge.initImGui(true);
}

std::string DebugSystem::TextFormat(const char *format, ...)
{
    // Crear un buffer de caracteres para almacenar la cadena formateada
    char buffer[1024]; // Tamaño arbitrario del buffer

    // Inicializar la lista variable de argumentos
    va_list args;
    va_start(args, format);

    // Formatear la cadena usando vsnprintf
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Limpiar la lista variable de argumentos
    va_end(args);

    // Retornar la cadena formateada
    return std::string(buffer);
}
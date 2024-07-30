#include <game/sys/render.hpp>
// managers
#include <ecs/man/entitymanager.hpp>
// cmp
#include <game/cmp/colliderComponent.hpp>
#include <game/cmp/renderComponent.hpp>
#include <game/cmp/cameraComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
#include <game/cmp/HUD/HUDComponent.hpp>
#include <game/cmp/aiComponent.hpp>
#include <game/cmp/perceptionComponent.hpp>
// libs
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <glm/gtx/vector_angle.hpp>

//  Graphic
#include <engines/graphic/GraphicEngine.hpp>
// #include <imgui/src/imgui.h>
// #include <imgui/src/imgui_impl_glfw.h>
// #include <imgui/src/imgui_impl_opengl3.h>
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

void RenderSystem::init(GraphicEngine &ge)
{
	ge.setActiveCamera(1);
	camara = ge.getActiveCamera()->getId();
}

// Se pone de forma momentanea los datos de la camara como parametro para luego añadir un componente camara
void RenderSystem::update(ECS::EntityManager &em, GraphicEngine &ge, [[maybe_unused]] float dt)
{
	/// obtengo el HUD
	auto &HUD = em.getSingletonComponentEM<HUDComponent>();
	auto *player = em.getPlayer();
	// Esto es para mostrar las posiciones del jugador en pantalla
	ge.enableDrawModels();

	for (auto &render : em.getComponents<RenderComponent>())
	{
		auto *e = em.getEntityByID(render.getEntityID());
		if (e)
		{
			auto *phy = e->getComponent<PhysicsComponent>();
			auto *cam = e->getComponent<CameraComponent>();
			auto *ray = e->getComponent<PerceptionComponent>();
			auto *iac = e->getComponent<AIComponent>();
			// auto *hl = e->getComponent<HealthComponent>();
			// si son marcadas para destruir, las "borro"
			if (!e->getIsAlive())
			{
				ge.getNode(render.node)->setVisible(false);
			}

			if (phy)
			{
				// calcular la direccion de la IA
				if(iac && player) {
					auto* phyPlayer = player->getComponent<PhysicsComponent>();
						if(iac->vX != 0 || iac->vZ != 0) {
							phy->forceDirection = glm::normalize(glm::vec3{iac->vX, 0.f, iac->vZ});
						} else {
							if(phyPlayer)
								phy->forceDirection = glm::normalize(glm::vec3{phyPlayer->position.x - phy->position.x, 0.f, phyPlayer->position.z - phy->position.z});
						}
						/* std::cout << "frce: " << phy->forceDirection.x << " , " << phy->forceDirection.y << " , " << phy->forceDirection.z << "\n"; */
				}
				
				if (ge.isKeyDown(GLFW_KEY_9))
				{
					ge.drawBoundingBox({phy->position.x, phy->position.y, phy->position.z}, render.w,
									   render.h, render.d, /* {0.2f, 0.1f, 0.0f} */ {1.f, 0.f, 0.f});
				}

				if (ge.getNode(render.node) && render.movableModel)
				{
					// Rotacion modelo personaje
					vecToRotate = phy->forceDirection;
					if (e->getType() == ECS::EntityType::PLAYER)
						vecToRotate = -vecToRotate; // necesario porque el player mira al contrario de hacia la camara

					if (glm::length2(vecToRotate) > 0.f)
						ge.getNode(render.node)->rotateInterpolate(vecToRotate);

					// posicion del modelo
					ge.getNode(render.node)->setPosition({phy->position.x, phy->position.y, phy->position.z});

					if (ray)
					{ // si tiene raycast la entidad pongo su origin en su posicion actual
						ray->raycast.origin = phy->position;
						ray->raycast.direction = ge.getNode(render.node)->getModelDirection(); // si eso en vez de que dependa del input, que depende del modelo la direccion
						if (e->getType() == ECS::EntityType::PLAYER) ray->raycast.direction = -ray->raycast.direction;
					}


					// // Rotacion modelo personaje
					// vecToRotate = phy->forceDirection;
					// if (e->getType() == ECS::EntityType::PLAYER)
					// 	vecToRotate = -vecToRotate; // necesario porque el player mira al contrario de hacia la camara

					// if(glm::length2(vecToRotate) > 0.f){
					// 	if (e->getType() != ECS::EntityType::ENEMY) ge.getNode(render.node)->rotateInterpolate(vecToRotate);
					// 	/* else ge.getNode(render.node)->rotate(vecToRotate); */
					// }

					// // posicion del modelo
					// ge.getNode(render.node)->setPosition({phy->position.x, phy->position.y, phy->position.z});

					// if (ray)
					// { // si tiene raycast la entidad pongo su origin en su posicion actual
					// 	ray->raycast.origin = phy->position;
					// 	ray->raycast.direction = ge.getNode(render.node)->getModelDirection(); // si eso en vez de que dependa del input, que depende del modelo la direccion
					// 	if (e->getType() == ECS::EntityType::ENEMY) ray->raycast.direction = vecToRotate;
					// 	if (e->getType() == ECS::EntityType::PLAYER) ray->raycast.direction = -ray->raycast.direction;
					// }
				}
			}

			if (cam)
			{
				auto camAux = ge.getNode(camara);
				// ge.drawBoundingBox({phy->x, phy->y, phy->z}, render.w,
				// 		render.h, render.d, {0.2f, 0.1f, 0.0f});
				// std::cout << "Valores camara position: " << camAux->getEntity<T_ECamera>()->getPosition().x << "f," << " " << camAux->getEntity<T_ECamera>()->getPosition().y << "f, " << camAux->getEntity<T_ECamera>()->getPosition().z << "f" << std::endl;
				// std::cout << "Valores camara target: " << camAux->getEntity<T_ECamera>()->getTarget().x << "f, " << camAux->getEntity<T_ECamera>()->getTarget().y << "f, " << camAux->getEntity<T_ECamera>()->getTarget().z << "f" << std::endl;
				// std::cout << "Valores camara up: " << camAux->getEntity<T_ECamera>()->getUp().x << "f, " << camAux->getEntity<T_ECamera>()->getUp().y << "f, " << camAux->getEntity<T_ECamera>()->getUp().z << "f" << std::endl;
				// std::cout << "Valores camara fovy: " << camAux->getEntity<T_ECamera>()->getFovy() << std::endl;
				if (cam->idCam == CameraComponent::currentCam)
				{
					camAux->setPosition({cam->cameraPosition.x, cam->cameraPosition.y, cam->cameraPosition.z});
					camAux->getEntity<T_ECamera>()->setPosition({cam->cameraPosition.x, cam->cameraPosition.y, cam->cameraPosition.z});
					camAux->getEntity<T_ECamera>()->setTarget({cam->cameraTarget.x, cam->cameraTarget.y, cam->cameraTarget.z});
					camAux->getEntity<T_ECamera>()->setUp({cam->cameraUp.x, cam->cameraUp.y, cam->cameraUp.z});
					camAux->getEntity<T_ECamera>()->setFovy(cam->cameraFovy);
				}
			}
		}
	}
	////////////////////////////////////
	// HUD - obtengo los datos del jugador para imprimirlos - LUEGO SI OCUADO MUCHO ESPACIO OCULATARLO CON UNA TECLA
	if (ge.isKeyReleased(GLFW_KEY_TAB))
	{
		controlHUD = !controlHUD;
	}

	auto *inv = em.getPlayer()->getComponent<InventoryComponent>();
	auto *hlt = em.getPlayer()->getComponent<HealthComponent>();
	auto *sht = em.getPlayer()->getComponent<ShotBehaviourComponent>();
	if (controlHUD && inv && hlt && sht)
	{
		HUD.drawInventory(*inv, ge);
		HUD.drawLife(*hlt, ge);
		HUD.drawLife(*hlt, ge);
		HUD.drawGun(*sht, ge);
		// Dibujar las balas que tiene el player
	}
	//"Intenta abrirte camino cruzando los diferentes desafios que encontraras. \nMira tus utilidades con el espacio, con la rueda del raton ayudate para \nacceder a tus objetos y recoge objetos con la F. \nBuena suerte. :)\0"
	// HUD.setMessage("Intenta abrirte camino cruzando los diferentes desafios que encontraras. \nMira tus utilidades con el espacio, con la rueda del raton ayudate para \nacceder a tus objetos y recoge objetos con la F. \nBuena suerte. :)");
	HUD.createDialog(HUD.getMessage(), ge); // hasta que no le de a la X el dialogo que este no se borra
	HUD.createQuickDialog(HUD.getQuickMessage(), ge);
	HUD.createUse(HUD.getInteractMessage(), ge); // solo se muestra cuando colisiona con un mensaje entity
												 // EndDrawing();
												 // anim->UpdateAnimation(dt);

	// ge.drawAll();
	// ge.endScene();
}

void RenderSystem::rotationModel(GraphicEngine &ge)
{
}

void RenderSystem::imGuiInit()
{
	// glfwSetErrorCallback([](auto error, auto description) {
	// 	std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	// 	throw std::runtime_error("GLFW Error");
	// });
	// if (!glfwInit()) throw std::runtime_error("Error al inicializar ventana GLFW");

	// // Inicializamos open GL
	// constexpr const char* glsl_version = "#version 130";
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// // // Creamos y inicializamos la ventana
	// window = glfwCreateWindow(300, 600, "Debug", NULL, NULL);

	// if (window == nullptr) throw std::runtime_error("Error al crear la ventana de GLFW");
	// //glfwMakeContextCurrent(window);
	// glfwSwapInterval(1);

	// //Inicializamos loader de OpenGl Glew
	// if (glewInit() != GLEW_OK) throw std::runtime_error("Error al inicializar GLEW");

	// // Inicializamos ImGui
	// IMGUI_CHECKVERSION();
	// ImGui::CreateContext();
	// ImGuiIO& io = ImGui::GetIO(); (void)io;

	// ImGui::StyleColorsDark();

	// ImGui_ImplGlfw_InitForOpenGL(window, true);
	// ImGui_ImplOpenGL3_Init(glsl_version);
}

RenderSystem::~RenderSystem()
{
	// ImGui_ImplOpenGL3_Shutdown();
	// ImGui_ImplGlfw_Shutdown();
	// ImGui::DestroyContext();

	// if (window)	glfwDestroyWindow(window);
	// glfwTerminate();
}

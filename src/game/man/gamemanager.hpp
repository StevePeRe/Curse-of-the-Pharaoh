#pragma once
// Managers
#include <game/man/levelmanager.hpp> //es un estado tmb - EntityManager - Entity - GOF
// #include <game/man/event/eventManager.hpp>
// #include <game/man/puzzlemanager.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
// Sys
#include <game/sys/ai.hpp>
#include <game/sys/behaviour.hpp>
#include <game/sys/camera.hpp>
#include <game/sys/inventory.hpp>
#include <game/sys/collision.hpp>
#include <game/sys/powerUp.hpp>
#include <game/sys/health.hpp>
#include <game/sys/spawn.hpp>
#include <game/sys/input.hpp>
#include <game/sys/physics.hpp>
#include <game/sys/render.hpp>
#include <game/sys/elevator.hpp>
#include <game/sys/event.hpp>  // incluye el event managaer
#include <game/sys/puzzle.hpp> // incluye el puzzle managaer
#include <game/sys/message.hpp>
#include <game/sys/audio.hpp>
#include <game/sys/animation.hpp>
#include <game/sys/debug.hpp>
#include <game/sys/raycast.hpp>
#include <game/sys/sensory.hpp>
#include <game/sys/cinematic.hpp>
// States
#include <game/states/PauseState.hpp>
#include <game/states/MenuState.hpp> // state - Audio - Fmod -
#include <game/states/DeathState.hpp>
#include <game/states/EndState.hpp>
// util
// #include <game/util/GameTimer.hpp>
#include <game/util/GameTimerX.hpp>
// #include <game/util/GameDataManager.hpp>
// Graphic Engine
#include <engines/graphic/GraphicEngine.hpp>
// Read txt
#include <fstream>
#include <JSON/src/json.hpp>
// libs
#include <iostream>
#include <chrono>
#include <string_view>
#include <cstdlib>
#include <array>

// clase que manejara todo el sistema del juego, cuando empieza, se pausa, sigue y termina
struct GameManager : StateBase
{
	explicit GameManager(StateManager &sm, ECS::EntityManager &em, GameObjectFactory &gof, AudioEngine &ae, PuzzleManager &puzzleMan, GraphicEngine &ge) : SM{sm}, EntityMan{em}, GOF{gof}, 
		eventManager{em.getSingletonComponentEM<EventManager>()}, audioEngine{ae}, puzzleManager{puzzleMan}, EventSys{eventManager, EntityMan, audioEngine, ge}, PuzzleSys{puzzleMan}, GE{ge}
	{
		RenSys.init(GE); // tmb se tendria que hacer en el level manager, pero con el neuvo sistema de pantallas - el nuevo motor grafico
		deltaTime = 0;
	};

	void update() final
	{
		float dt = float(SimulTimer.cycleSecs());
		if (dt > 0.1f)
			dt = 0.f; // cuando vuelve del estado pause

		// // DESCOMENTAR SI QUIERES HACER DEBUG PROFILING
		// auto timedCall = [](std::string_view name, auto&& func) {
		// 	GameTimer timer;
		// 	func();
		// 	std::cout << "[" << name << "] " << timer.ellapsed()/1000 << "mCs\n";
		// };

		// // A MAXIMA VELOCIDAD
		// timedCall("ENT", [&](){ EntityMan.update(); });
		// timedCall("INP", [&](){ InputSys.update(EntityMan, GE); });
		// timedCall("PHY", [&](){ PhySys.update(EntityMan, dt);; });
		// timedCall("BEH", [&](){ BehSys.update(EntityMan, audioEngine, GOF); });
		// 	// ESPERA HSATA QUE PASE EL CICLO
		// 	if(SimulTimer.cyclePassed()){
		// 		timedCall("MESS", [&](){ MessageSys.update(EntityMan); });
		// 		timedCall("SPAW", [&](){ SpawnSys.update(EntityMan); });
		// 		timedCall("CAM", [&](){ CamSys.update(EntityMan); });
		// 		SimulTimer.start();
		// 	}
		// timedCall("ELE", [&](){ ElevSys.update(EntityMan); });
		// timedCall("INV", [&](){ InvSys.update(EntityMan); });
		// timedCall("RAY", [&](){ RaycastSys.update(EntityMan); });
		// timedCall("SENS", [&](){ SensorySys.update(EntityMan); });
		// timedCall("AI", [&](){ AISys.update(EntityMan, GE, dt, GOF); });
		// timedCall("PUZZ", [&](){ PuzzleSys.updatePuzzles(EntityMan, GOF, GE, audioEngine); });
		// timedCall("COL", [&](){ ColSys.update(EntityMan);  });
		// timedCall("EVEN", [&](){ EventSys.updateTriggers(); });
		// timedCall("CINE", [&](){ CinematicSys.update(EntityMan); });
		// timedCall("HEAL", [&](){ HealthSys.update(EntityMan);  });
		// timedCall("PWUP", [&](){ PowerUps.update(EntityMan); });
		// timedCall("DEBG", [&](){ DebugSys.update(EntityMan, GE); });
		// timedCall("REND", [&](){ RenSys.update(EntityMan, GE, dt); });
		// timedCall("ANIM", [&](){ AnimationSys.update(EntityMan, GE, dt); });
		// timedCall("LATE_E", [&](){ EventSys.lateUpdate(); });
		// timedCall("AUD", [&](){ AudioSys.update(EntityMan, audioEngine, GE.getActiveCamera()); });
		// std::cout << "------------------------------------------------\n";

		// A MAXIMA VELOCIDAD
		EntityMan.update();
		InputSys.update(EntityMan, GE); // siempre primero
		PhySys.update(EntityMan, dt);
		BehSys.update(EntityMan, audioEngine, GOF);
		// ESPERA HASTA QUE PASE EL CICLO
		if (SimulTimer.cyclePassed())
		{
			MessageSys.update(EntityMan);
			SpawnSys.update(EntityMan);
			CamSys.update(EntityMan);

			SimulTimer.start();
		}
		ElevSys.update(EntityMan);
		InvSys.update(EntityMan);
		RaycastSys.update(EntityMan);
		SensorySys.update(EntityMan);
		AISys.update(EntityMan, GE, dt, GOF);
		PuzzleSys.updatePuzzles(EntityMan, GOF, GE, audioEngine);
		ColSys.update(EntityMan); 
		EventSys.updateTriggers();
		CinematicSys.update(EntityMan);
		HealthSys.update(EntityMan);
		PowerUps.update(EntityMan);
		DebugSys.update(EntityMan, GE);
		RenSys.update(EntityMan, GE, dt);
		AnimationSys.update(EntityMan, GE, dt);
		EventSys.lateUpdate();
		AudioSys.update(EntityMan, audioEngine, GE.getActiveCamera());
		// std::cout << "------------------------------------------------\n";

		if (eventManager.getEventType().ContainsLayer(EventMask::LOAD_LEVEL))
		{
			saveData(); // guardo los datos del jugador al acabar la partida
			eraseAllDataLevel();
			setNextLevel();
			SM.pushState<LevelManager>(SM, audioEngine, GE);
		}

		// entidad jugador
		if (EntityMan.getEntityVector().size() > 0 && !EntityMan.getPlayer()->getIsAlive())
		{
			eraseAllDataLevel();
			eraseData();
			GE.closeImGui();
			SM.pushState<DeathState>(SM, audioEngine, GE);
		}

		if (GE.closeWindow || GE.isKeyPressed(GLFW_KEY_P) || GE.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			SM.pushState<PauseState>(SM, *this, audioEngine, GE);
			GE.closeWindow = false;
		}
		// std::cout << "[FPS] " << 1.f/SimulTimer.cycleSecs() << "\n";
		// std::cout << "[FPS] " << timer.ellapsed() << "\n";
		// w8 till 60fps
		GE.drawAll();
		GE.endScene();

		timer.waitUntil_ns(NSPF);
		timer.start();
	}

	bool alive() final { return m_playing; }

	void setNotAlive() { m_playing = false; } // de momento para que en pausa pueda volver al menu
	/* void setPause(bool set) { isPaused = set; } */

	void eraseData()
	{
		json archivo_vacio;
		// quitar el paso del level manager aqui
		for (int16_t i = 0; i < static_cast<int16_t>(niveles.size()); i++)
		{
			std::string concatenado = "./media/levels/";
			concatenado += niveles.at(i);
			concatenado += "/levelData.json";
			manageData.escribirJSON(archivo_vacio, concatenado);
		}
	}

private:
	// se inicializan todos al llamar al contructor
	// dependiendo en que orden los ponga tmb se inicializan asi en el constructor de la clase
	StateManager &SM;			   // se inicializa en el main
	ECS::EntityManager &EntityMan; // se inicializa en el levelmanager
	GameObjectFactory &GOF;		   // se inicializa en el levelmanager
	EventManager &eventManager;	   // se inicializa en el levelmanager
	AudioEngine &audioEngine;
	PuzzleManager &puzzleManager; // se inicializa en el levelmanager
	GraphicEngine &GE;
	PhysicsSystem PhySys;
	RenderSystem RenSys;
	CameraSystem CamSys;
	BehaviourSystem BehSys;
	HealthSystem HealthSys;
	InventorySys InvSys;
	CollisionSystem ColSys;
	AISystem AISys;
	PowerUpSystem PowerUps;
	SpawnSystem SpawnSys;
	InputSystem InputSys;
	EventSystem EventSys;
	PuzzleSystem PuzzleSys;
	MessageSystem MessageSys;
	ElevatorSystem ElevSys;
	AudioSystem AudioSys;
	AnimationSystem AnimationSys;
	DebugSystem DebugSys;
	RaycastSystem RaycastSys;
	SensorySystem SensorySys;
	CinematicSystem CinematicSys;
	bool m_playing{true};
	float deltaTime;
	std::chrono::steady_clock::time_point lastUpdate;

	uint64_t FPS{60};
	uint64_t NSPF{1000000000 / FPS};
	GameTimer timer;

	GameTimerX full{};
	GameTimerX SimulTimer{60};
	int c{};
	std::array<std::string, 3> niveles = {"level_0", "level_1", "level_2"};

	/* bool isPaused{false}; */
	GameDataManager manageData;

	void eraseAllDataLevel()
	{
		m_playing = false;
		puzzleManager.clearAllPuzzles();
		EntityMan.cleanAll();
		eventManager.clearAllEvents();
	}

	void setNextLevel()
	{
		nlohmann::json datos_general;
		datos_general = manageData.leerJSON("./media/levels/general.json");
		uint16_t level = datos_general["jugador"]["nivel_siguiente"];
		level++;
		datos_general["jugador"]["nivel_siguiente"] = level;
		manageData.escribirJSON(datos_general, "./media/levels/general.json");
	}

	void saveData()
	{
		auto *player = EntityMan.getPlayer();
		nlohmann::json datos;
		if (player)
		{
			// Guardo datos del jgador - inventario - vida - balas
			auto *inv = player->getComponent<InventoryComponent>();
			auto *hel = player->getComponent<HealthComponent>();
			auto *beh = player->getComponent<ShotBehaviourComponent>();
			if (inv && hel && beh)
			{
				// datos1["posicion"] = {phy->x, phy->y, phy->z};
				datos["jugador"]["vida_actual"] = hel->health;
				datos["jugador"]["balas"] = beh->shot_ammo;
				for (const auto &pair : inv->getInventory())
				{
					// std::cout << "tipo: " << pair.first << "\n";
					// int aux_type = pair.first;
					datos["jugador"]["inventario"][std::to_string(pair.first)] = pair.second;
				}
			}
		}

		nlohmann::json datos_general;
		datos_general = manageData.leerJSON("./media/levels/general.json");
		std::string concatenado = "./media/levels/";
		concatenado += datos_general["jugador"]["nivel_actual"];
		concatenado += "/levelData.json";

		manageData.escribirJSON(datos, concatenado);
	}
};
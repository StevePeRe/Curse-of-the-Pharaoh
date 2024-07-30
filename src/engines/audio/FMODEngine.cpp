// raiz
#include "FMODEngine.hpp"

// libs
#include <unistd.h>
#include <iostream>
#include <memory>

#include <FMOD/src/fmod.h>
#include <FMOD/src/fmod_studio.h>
#include <FMOD/src/fmod_errors.h>
#include <FMOD/src/fmod_common.h>

#include "FMODInstance.hpp"

void FMODEngine::init()
{

  if (Initialized)
    return;

  FMOD_RESULT result;

  void *extraDriverData = NULL;

  fmodSystem = FMODSystem(nullptr, releaseSystem);
  FMOD_STUDIO_SYSTEM *rawPtr = fmodSystem.get();
  result = FMOD_Studio_System_Create(&rawPtr, FMOD_VERSION);

  std::cout << "\nFMOD CREATE SYSTEM: " << FMOD_ErrorString(result);

  fmodSystem.reset(rawPtr);

  FMOD_Studio_System_GetCoreSystem(fmodSystem.get(), &coreSystem);

  FMOD_System_SetSoftwareFormat(coreSystem, 0, FMOD_SPEAKERMODE_5POINT1, 0);

  // FMOD INITIALIZE

  result = FMOD_Studio_System_Initialize(fmodSystem.get(), 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);

  std::cout << "\nFMOD INITIALIZE: " << FMOD_ErrorString(result);

  // LOAD BANKS

  masterBank = NULL;
  result = FMOD_Studio_System_LoadBankFile(fmodSystem.get(), "bancos_fmod/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

  std::cout << "\nFMOD LOAD MASTER BANK: " << FMOD_ErrorString(result);

  FMOD_STUDIO_BANK *stringsBank = NULL;
  result = FMOD_Studio_System_LoadBankFile(fmodSystem.get(), "bancos_fmod/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
  std::cout << "\nFMOD LOAD MASTER STRING BANK: " << FMOD_ErrorString(result);

  Initialized = true;
}

void FMODEngine::releaseSystem(FMOD_STUDIO_SYSTEM *system)
{
  std::cout << "\nRELEASE AUDIO ENGINE" << std::endl;
  FMOD_Studio_System_Release(system);
}

void FMODEngine::update()
{
  FMOD_Studio_System_Update(fmodSystem.get());
  for (auto &par : audioMap)
  {
    // recorro cada vector de cada par del mapa
    for (std::size_t i = 0; i < par.second.size(); i++)
    {
      par.second.at(i).get()->UpdateStatus();
    }
  }
}

AudioInstance *FMODEngine::createInstance(const char *soundTag, const char *path)
{

	std::cout << "\nLOAD AUDIO EVENT: " << soundTag << std::endl;

	eventDescription = nullptr;
	eventInstance = nullptr;

	std::string event = "event:/" + std::string{path};

	FMOD_Studio_System_GetEvent(fmodSystem.get(), event.c_str(), &eventDescription);
	FMOD_Studio_EventDescription_CreateInstance(eventDescription, &eventInstance);
	FMOD_Studio_EventInstance_SetVolume(eventInstance, 1);

	auto itr = audioMap.find(soundTag);

	if (itr != audioMap.end())
	{
		std::cout << "ya existe el sonido\n";
		return itr->second.emplace_back(std::make_unique<FMODInstance>(eventInstance)).get();
	}

	std::vector<std::unique_ptr<AudioInstance>> vectorInstances;
	vectorInstances.emplace_back(std::make_unique<FMODInstance>(eventInstance));

	return audioMap.emplace(soundTag, std::move(vectorInstances)).first->second.back().get();
}

std::vector<AudioInstance *> FMODEngine::getInstances(const char *soundTag)
{
  std::vector<AudioInstance *> result{};

  auto itr = audioMap.find(soundTag);
  if (itr != audioMap.end() && !itr->second.empty())
  {
    for (auto &instance : itr->second)
      result.emplace_back(instance.get());
  }

  return result;
}

void FMODEngine::setListener(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
  FMOD_3D_ATTRIBUTES eventAttributes;

  eventAttributes.position.x = -position.x;
  eventAttributes.position.y = position.y;
  eventAttributes.position.z = position.z;

  eventAttributes.velocity.x = 0.0f;
  eventAttributes.velocity.y = 0.0f;
  eventAttributes.velocity.z = 0.0f;

  eventAttributes.forward.x = -direction.x;
  eventAttributes.forward.y = direction.y;
  eventAttributes.forward.z = direction.z;

  eventAttributes.up.x = -up.x;
  eventAttributes.up.y = up.y;
  eventAttributes.up.z = up.z;

  FMOD_Studio_System_SetListenerAttributes(fmodSystem.get(), 0, &eventAttributes, nullptr);
}
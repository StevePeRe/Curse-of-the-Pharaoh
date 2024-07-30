#pragma once
// cmp
#include <ecs/cmp/component.hpp>
//util
#include <ecs/util/globals.hpp>
// libs
#include <cstdint>
// #include <string>
#include <string_view>

struct HealthComponent;
struct InventoryComponent;
struct ShotBehaviourComponent;
struct GraphicEngine;
struct UImage;
struct TNode;

struct HUDComponent : ECS::SingletonComponent
{

    explicit HUDComponent() : ECS::SingletonComponent(ECS::IDSingleCMPHUD) {}

    static std::size_t getSingletonComponentTypeID() noexcept 
    { 
        return static_cast<std::size_t>(ECS::IDSingleCMPHUD); 
    }

    void createDialog(const char* message, GraphicEngine &ge);
    void createQuickDialog(const char* message, GraphicEngine &ge);
    void drawInventory(InventoryComponent& inv, GraphicEngine &ge);
    void drawLife(HealthComponent& health, GraphicEngine &ge);
    void drawGun(ShotBehaviourComponent& behaviour, GraphicEngine &ge);
    void createUse(const char* message, GraphicEngine &ge);

    const char* TextSubtext(const char *text, int position, int length);
    unsigned int TextLength(const char *text);
    std::string TextFormat(const char* format, ...);

    void showMessage() { eraseMessage = false; };
    void showQuickMessage() { eraseQuickMessage = false; };
    void clearMessage() { 
        eraseMessage = true;
        framesCounter = 0;
    };

    void clearQuickMessage() {  
        eraseQuickMessage = true;
    };

    void setMessage(const char* dialog) { message = dialog; };
    const char* getMessage() { return message; };

    // quickMessage
    void setQuickMessage(const char* dialog) { quickMessage = dialog; };
    const char* getQuickMessage() { return quickMessage; };

    // interactMessage
    void setInteractMessage(const char* dialog) { interactMessage = dialog; };
    const char* getInteractMessage() { return interactMessage; };

    void canInteractUseE(bool could) { 
        canInteract = could; 
    };

    static constexpr uint32_t TIME {  110 };

    int framesCounter{0};
    uint32_t timer{ TIME };

    private:
    bool eraseMessage{true};
    const char* message{};

    // quickMessage
    bool eraseQuickMessage{true};
    const char* quickMessage{};

    // Use E
    bool canInteract{false};
    const char* interactMessage{};

    bool inserted{false};
    std::string lastDialog;
};
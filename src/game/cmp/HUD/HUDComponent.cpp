#include <game/cmp/HUD/HUDComponent.hpp>
// cmp
#include <game/cmp/healthComponent.hpp>
#include <game/cmp/inventoryComponent.hpp>
#include <game/cmp/shotBehaviourComponent.hpp>
// libs
// #include <raylib.h>
#include <stdio.h>
// Graphic
#include <engines/graphic/GraphicEngine.hpp>

void HUDComponent::createDialog(const char *message, GraphicEngine &ge)
{
    if (!eraseMessage)
    { // prototipo
        framesCounter += 3;
        ge.addSceneImage("./media/img/Plano_TextoM.png", 20, 740);

        ge.addSceneText(TextSubtext(message, 0, framesCounter / 10), "Vintage.ttf", 60, 270, 1.1f, {1.0f, 1.0f, 1.0f});

        ge.addSceneImage("./media/img/spacebar.png", 1090, 1000);
        ge.addSceneText(" AVANZAR ", "Vintage.ttf", 850, 50, 1.2f, {1.0f, 1.0f, 1.0f});
    }
}

void HUDComponent::createQuickDialog(const char *message, GraphicEngine &ge)
{
    if (!eraseQuickMessage)
    { // prototipo
        ge.addSceneImage("./media/img/Plano_Texto2.png", 20, 810);
        ge.addSceneText(message, "Vintage.ttf", 60, 200, 1.2f, {1.0f, 1.0f, 1.0f});
        ge.addSceneText("CERRAR X", "Vintage.ttf", 850, 40, 1.2f, {1.0f, 1.0f, 1.0f});
        if (timer-- <= 0)
        {
            eraseQuickMessage = true;
            timer = TIME;
        }
    }
}

void HUDComponent::createUse(const char *message, GraphicEngine &ge)
{
    if (canInteract)
    {
        ge.addSceneImage("./media/img/Plano2.png", 20, 500);
        ge.addSceneText(message, "Vintage.ttf", 30, 535, 1, {1.0f, 1.0f, 1.0f});
    }
}

void HUDComponent::drawInventory(InventoryComponent &inv, GraphicEngine &ge)
{
    ge.addSceneImage("./media/img/inventory.png", 1580, 740);

    if (inv.getInventory().size() > 0)
    {
        switch (inv.getObjectInHand().first)
        {
        case ECS::EntityTAG::AMMO:
            ge.addSceneImage("./media/img/Icon-ammo.png", 1630, 860);
            ge.addSceneText(TextFormat("X%i ", inv.getObjectInHand().second), "Vintage.ttf", 1760, 260, 1, {1.0f, 1.0f, 1.0f});
            break;
        case ECS::EntityTAG::KEY_1:
            ge.addSceneImage("./media/img/Icon-llave.png", 1650, 860);
            break;
        case ECS::EntityTAG::KEY_2:
            ge.addSceneImage("./media/img/Icon-llave2.png", 1650, 860);
            break;
        case ECS::EntityTAG::KEY_3:
            ge.addSceneImage("./media/img/Icon-llave3.png", 1650, 860);
            break;
        case ECS::EntityTAG::KEY_4:
            ge.addSceneImage("./media/img/Icon-llave3.png", 1650, 860); // cambiar a llave 4 img
            break;
        case ECS::EntityTAG::SMALL_HEAL:
            ge.addSceneImage("./media/img/Icon-curaP.png", 1650, 860);
            ge.addSceneText(TextFormat("X%i ", inv.getObjectInHand().second), "Vintage.ttf", 1760, 260, 1, {1.0f, 1.0f, 1.0f});
            break;
        case ECS::EntityTAG::BIG_HEAL:
            ge.addSceneImage("./media/img/Icon-curaG.png", 1650, 860);
            ge.addSceneText(TextFormat("X%i ", inv.getObjectInHand().second), "Vintage.ttf", 1760, 260, 1, {1.0f, 1.0f, 1.0f});
            break;
        default:
            break;
        }
    }
    else
    {
        ge.addSceneText(" NO TIENES OBJETOS", "Vintage.ttf", 1560, 150, 1.0f, {1.0f, 1.0f, 1.0f});
    }

    ge.addSceneImage("./media/img/q.png", 1685, 990);
}

void HUDComponent::drawLife(HealthComponent &health, GraphicEngine &ge)
{
    auto life = health.health;

    if (life > 80.f)
        ge.addSceneImage("./media/img/Inf-icon1.png", 30, 20);
    if (life <= 80.f && life > 60.f)
        ge.addSceneImage("./media/img/Inf-icon2.png", 30, 20);
    if (life <= 60.f && life > 40.f)
        ge.addSceneImage("./media/img/Inf-icon3.png", 30, 20);
    if (life <= 40.f && life > 20.f)
        ge.addSceneImage("./media/img/Inf-icon4.png", 30, 20);
    if (life <= 20.f && life > -1.f)
        ge.addSceneImage("./media/img/Inf-icon5.png", 30, 20);
}

void HUDComponent::drawGun(ShotBehaviourComponent &behaviour, GraphicEngine &ge)
{
    switch (behaviour.type)
    {
    case ECS::BehaviourType::Pistol:
        ge.addSceneText(TextFormat(" PISTOLA - %i/%i", behaviour.shot_ammo, behaviour.shot_maxAmmo), "Vintage.ttf", 1600, 350, 1, {1.0f, 1.0f, 1.0f});
        break;
    case ECS::BehaviourType::ShotGun:
        ge.addSceneText(TextFormat(" ESCOPETA - %i/%i", behaviour.shot_ammo, behaviour.shot_maxAmmo), "Vintage.ttf", 1600, 350, 1, {1.0f, 1.0f, 1.0f});
        break;
    default:
        break;
    }
}

const char *HUDComponent::TextSubtext(const char *text, int position, int length)
{
    static char buffer[1024] = {0};
    memset(buffer, 0, 1024);

    int textLength = TextLength(text);
    if (position >= textLength)
    {
        position = textLength - 1;
        length = 0;
    }
    if (length >= textLength)
        length = textLength;

    for (int c = 0; c < length; c++)
    {
        *(buffer + c) = *(text + position);
        text++;
    }
    *(buffer + length) = '\0';

    return buffer;
}
unsigned int HUDComponent::TextLength(const char *text)
{
    unsigned int length = 0;

    if (text != NULL)
    {
        while (*text++)
            length++;
    }

    return length;
}
std::string HUDComponent::TextFormat(const char *format, ...)
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
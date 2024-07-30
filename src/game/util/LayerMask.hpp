#pragma once

#include <bitset>
#include <iostream>

// hacer lo mismo para los tipos de la entidad si eso
const int MAX_LAYERS = 32;

// esto de mi motor PE, pero le he añadido mas tipos de capa como lo haria unity
typedef enum {
    DEFAULT = 0,
    PLAYER,
    ENEMY,
    ENVIRONMENT,
    CAMERA,
    TRIGGER,
    SPAWNER,
    NUM_LAYERS
} LayerRaycast;

typedef enum {
    NONE_EVENT = 0,
    COMBAT_MUSIC,
    DUNGEON_MUSIC,
    EXTERIOR_MUSIC,
    POWER_UP_MUSIC,
    PICK_OBJECT,
    CINEMATIC,
    PZ_COMPLETED,
    LOAD_LEVEL,
    NUM_EVENTS
} EventMask;

typedef enum {
    NO_POWERS = 0,
    SHOTGUN_MODE,
    INMUNITY_MODE,
    NUM_POWER_UPS
} PowerUps;

class LayerMask {
public:
    LayerMask() : mask(0) {}

    // Añadir una capa a la máscara
    template<typename MASK>
    void AddLayer(MASK layer) {
        mask.set(layer);
    }

    // Eliminar una capa de la máscara
    template<typename MASK>
    void RemoveLayer(MASK layer) {
        mask.reset(layer);
    }

    // Verificar si la máscara contiene una capa específica
    template<typename MASK>
    bool ContainsLayer(MASK layer) const {
        return mask.test(layer);
    }

    // Comprobar intersección con otra máscara
    bool Intersects(const LayerMask& other) const {
        return (mask & other.mask).any();
    }

    std::bitset<MAX_LAYERS> getMask() const { return mask; }    

private:
    std::bitset<MAX_LAYERS> mask;
};
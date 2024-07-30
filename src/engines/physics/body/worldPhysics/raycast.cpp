// todo del raycast que esta en el AABB ponerlo aqui
#include <engines/physics/body/worldPhysics/raycast.hpp>
// PE - PHYSICS ENGINE
#include <engines/physics/body/bodyComponent.hpp>
// cmp
#include <game/cmp/physicsComponent.hpp> //  cambiar luego a que este tmb en el PE
// libs
#include <glm/gtc/matrix_transform.hpp>

void Raycast::resetClosestPosition() {
    closestPos = FLT_MAX;
}

bool Raycast::checkObjectCollision(bodyComponent &body, PhysicsComponent &phy, bool useLayer)
{
    bool check = false;
    if(useLayer){
        if (!(layer.Intersects(phy.layer))) return false;
    }

    auto b2 = body.collisionAABB.turnToScreenCoordinates(body.bBox_, phy.position.x, phy.position.y, phy.position.z);

    float t1 = (b2.xMin - origin.x) / direction.x;
    float t2 = (b2.xMax - origin.x) / direction.x;
    float t3 = (b2.yMin - origin.y) / direction.y;
    float t4 = (b2.yMax - origin.y) / direction.y;
    float t5 = (b2.zMin - origin.z) / direction.z;
    float t6 = (b2.zMax - origin.z) / direction.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    if ((tmin <= tmax) && (tmin >= 0) && (tmin <= range))
    {
        result.intersection = origin + (tmin * direction);
        result.has_intersection = true;

        if(closestPos > tmin){
            closestPos = tmin;
            closestObject = phy.layer;
        }

        check = true;
    }

    return check;
}

bool Raycast::checkObjectCollisionCone(bodyComponent &body, PhysicsComponent &phy, uint32_t steps = 10)
{
    bool check = false;
    auto b2 = body.collisionAABB.turnToScreenCoordinates(body.bBox_, phy.position.x, phy.position.y, phy.position.z);
    Raycast coneRay = *this;

    glm::vec3 forwardVector = glm::normalize(direction);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    // Calcular los pasos angulares para cubrir el cono
    uint32_t numSteps = steps; // Número de rayos dentro del cono
    uint32_t vision = 90;
    float stepSize = static_cast<float>(vision / numSteps);

        // Iterar sobre cada paso angular y lanzar un rayo
    for (int i = -numSteps / 2; i <= numSteps / 2; ++i) {
        float angle = glm::radians(static_cast<float>(i) * stepSize); // Convertir el ángulo a radianes
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, upVector);
        glm::vec3 coneDirection = glm::vec3(rotationMatrix * glm::vec4(forwardVector, 0.0f)); // Rotar la dirección del cono

        if(coneDirection.length() > 0)
            coneRay.direction = glm::normalize(coneDirection);
        // Calcular los valores t para las intersecciones con la AABB
        float t1 = (b2.xMin - coneRay.origin.x) / coneRay.direction.x;
        float t2 = (b2.xMax - coneRay.origin.x) / coneRay.direction.x;
        float t3 = (b2.yMin - coneRay.origin.y) / coneRay.direction.y;
        float t4 = (b2.yMax - coneRay.origin.y) / coneRay.direction.y;
        float t5 = (b2.zMin - coneRay.origin.z) / coneRay.direction.z;
        float t6 = (b2.zMax - coneRay.origin.z) / coneRay.direction.z;

        // Encontrar los valores t mínimo y máximo de intersección con la AABB en la dirección del rayo
        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        // Verificar si la intersección ocurre dentro del rango máximo de longitud y si tmin es menor o igual a tmax
        if ((tmin <= tmax) && (tmin >= 0) && (tmin <= range))
        {
            check = true;
            break;
        }
    }

    return check;
}

bool Raycast::checkDetectionCone(PhysicsComponent &phyOrigin, PhysicsComponent &phyToDetect)
{
    bool check = false;

    // origin 
    if((phyToDetect.position - phyOrigin.position).length == 0) return true;
    if(direction.length == 0) return false;

    glm::vec3 objectDirection = glm::normalize(phyToDetect.position - phyOrigin.position);
    glm::vec3 forwardVector = glm::normalize(direction);
    float angleToObject = glm::acos(glm::dot(forwardVector, objectDirection));

    // Convertir el ángulo a grados
    float angleDegrees = glm::degrees(angleToObject);

    // para angulo de 90 grados
    if (angleDegrees < 65.0f && glm::length(phyToDetect.position - phyOrigin.position) <= rangeVisionCone)
    {
        check = true;
    }
    else
    {
        check = false;
    }

    return check;
}
#include <engines/physics/body/collider/AABB.hpp>
// cmp
#include <engines/physics/body/bodyComponent.hpp>
#include <game/cmp/physicsComponent.hpp>
// PE
#include <engines/physics/body/worldPhysics/raycastResult.hpp>
// lib
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void AABB::resolveCollisionWithFriction(PhysicsComponent &phyA, PhysicsComponent &phyB)
{
    float averageStatic = (phyB.staticFriction + phyA.staticFriction) * 0.5f;
    float averageDynamic = (phyB.dynamicFriction + phyA.dynamicFriction) * 0.5f;
    if (phyA.dynamic_)
    {
        float forceRozStaticA = averageStatic * phyA.mass * 9.8f; 
        if (glm::abs(phyA.ownForces.x) <= forceRozStaticA) phyA.ownForces.x = 0;
        else phyA.ownForces.x *= averageDynamic;

        if (glm::abs(phyA.ownForces.z) <= forceRozStaticA) phyA.ownForces.z = 0;
        else phyA.ownForces.z *= averageDynamic;

        if (phyB.kinematic_)
            phyA.externForces = phyB.ownForces * 1.26f;
    }

    if (phyB.dynamic_)
    {
        float forceRozStaticB = averageStatic * phyB.mass * 9.8f; 
        if (glm::abs(phyB.ownForces.x) <= forceRozStaticB) phyB.ownForces.x = 0;
        else phyB.ownForces.x *= averageDynamic;

        if (glm::abs(phyB.ownForces.z) <= forceRozStaticB) phyB.ownForces.z = 0;
        else phyB.ownForces.z *= averageDynamic;

        if (phyA.kinematic_)
            phyB.externForces = phyA.ownForces * 1.26f;
    }
}

bool AABB::nearlyEqual(glm::vec3 a, glm::vec3 b)
{
    float tolerance = 0.0005f;
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;

    float distanceSquared = dx * dx + dy * dy + dz * dz;

    return distanceSquared < tolerance * tolerance;
}

bool AABB::nearlyEqual(float a, float b)
{
    float tolerance = 0.02f;
    return std::abs(a - b) < tolerance;
}

void AABB::resolveCollisionXZ(PhysicsComponent &phyA, PhysicsComponent &phyB)
{
    if (phyA.invMass == 0 && phyB.invMass == 0)
    {
        return;
    }
    glm::vec3 relativeForce = {phyB.ownForces.x - phyA.ownForces.x, 0.f, phyB.ownForces.z - phyA.ownForces.z};
    glm::vec3 normal = {phyA.normal.x, 0.f, phyA.normal.z};

    if (glm::dot(relativeForce, normal) > 0.f)
    {
        return;
    }

    float avarageRest = (phyB.restitution + phyA.restitution) * 0.5f;

    float eA = avarageRest;
    float eB = avarageRest;

    float jA = -(1.f + eA) * glm::dot(relativeForce, normal);
    jA /= phyA.invMass + phyB.invMass;
    glm::vec3 impulseA = jA * normal;

    float jB = -(1.f + eB) * glm::dot(relativeForce, normal);
    jB /= phyA.invMass + phyB.invMass;
    glm::vec3 impulseB = jB * normal;

    // solo cuerpos dinamicos podran tener impulsos por fuerzas
    if (phyA.dynamic_ && phyA.hasImpulse)
    {
        phyA.ownForces.x += -impulseA.x * phyA.invMass;
        phyA.ownForces.z += -impulseA.z * phyA.invMass;
    }

    if (phyB.dynamic_ && phyB.hasImpulse)
    {
        phyB.ownForces.x += impulseB.x * phyB.invMass;
        phyB.ownForces.z += impulseB.z * phyB.invMass;
    }
}

void AABB::resolveCollisionY(PhysicsComponent &phyA, PhysicsComponent &phyB)
{
    // FORCES
    if (phyA.invMass == 0 && phyB.invMass == 0)
    {
        return;
    }

    glm::vec3 normal = {0.f, 1.f, 0.f};

    if ((phyB.force.y - phyA.force.y) > 0.f)
    {
        return;
    }

    float avarageRest = (phyA.restitution + phyB.restitution) * 0.5f;

    float eA = avarageRest;
    float eB = avarageRest;

    float jA = -(1.f + eA) * (phyB.force.y - phyA.force.y);
    jA /= phyA.invMass + phyB.invMass;
    float impulseA = jA * normal.y;

    float jB = -(1.f + eB) * (phyB.force.y - phyA.force.y);
    jB /= phyA.invMass + phyB.invMass;
    float impulseB = jB * normal.y;

    // solo cuerpos dinamicos podran tener impulsos por fuerzas
    if (phyA.dynamic_ && phyA.hasImpulse)
        phyA.ownForces.y = (-impulseA * phyA.invMass) - (phyB.force.y - phyA.force.y);
    if (phyB.dynamic_ && phyB.hasImpulse)
        phyB.ownForces.y = (impulseB * phyB.invMass) + (phyB.force.y - phyA.force.y);
}

bool AABB::checkObjectCollision(bodyComponent &bc1, bodyComponent &bc2, PhysicsComponent &phy1, PhysicsComponent &phy2)
{
    phy1.normal *= 0;
    phy1.depth = 0.f;
    phy2.normal *= 0;
    phy2.depth = 0.f;

    auto b1 = turnToScreenCoordinates(bc1.bBox_, phy1.position.x, phy1.position.y, phy1.position.z);
    auto b2 = turnToScreenCoordinates(bc2.bBox_, phy2.position.x, phy2.position.y, phy2.position.z);

    bool collisionDetected = (b1.xMin <= b2.xMax && b1.xMax >= b2.xMin) &&
                             (b1.yMin <= b2.yMax && b1.yMax >= b2.yMin) &&
                             (b1.zMin <= b2.zMax && b1.zMax >= b2.zMin);

    if (collisionDetected && bc1.collider && bc2.collider)
    {
        float dx = std::min(b1.xMax - b2.xMin, b2.xMax - b1.xMin);
        float dy = std::min(b1.yMax - b2.yMin, b2.yMax - b1.yMin);
        float dz = std::min(b1.zMax - b2.zMin, b2.zMax - b1.zMin);

        phy1.normal = phy2.normal = glm::normalize(phy2.position - phy1.position);

        // STATIC ------------------------------------------------------------
        if ((phy1.dynamic_ && (phy2.static_ || phy2.kinematic_)) || ((phy1.static_ || phy1.kinematic_) && phy2.dynamic_))
        {
            if (dx < dy && dx < dz)
            {
                resolveCollisionXZ(phy1, phy2);
                if (b1.xMax - b2.xMin < b2.xMax - b1.xMin)
                {
                    if (phy1.dynamic_)
                    {
                        phy1.position.x -= dx / 2.0f;
                    }
                    if (phy2.dynamic_)
                    {
                        phy2.position.x += dx / 2.0f;
                    }
                }
                else
                {
                    if (phy1.dynamic_)
                    {
                        phy1.position.x += dx / 2.0f;
                    }
                    if (phy2.dynamic_)
                    {
                        phy2.position.x -= dx / 2.0f;
                    }
                }
            }
            else if (dy < dx && dy < dz)
            {
                if (b1.yMax - b2.yMin < b2.yMax - b1.yMin)
                {
                    if (phy1.dynamic_)
                    {
                        phy1.gravityForce.y = 0.f;
                        phy1.position.y -= dy / 2.0f;
                    }

                    if (phy2.dynamic_)
                    {
                        phy2.gravityForce.y = 0.f;
                        phy2.position.y += dy / 2.0f;
                    }
                }
                else
                {
                    if (phy1.dynamic_)
                    {
                        phy1.gravityForce.y = 0.f;
                        phy1.position.y += dy / 2.0f;
                    }

                    if (phy2.dynamic_)
                    {
                        phy2.gravityForce.y = 0.f;
                        phy2.position.y -= dy / 2.0f;
                    }
                }
                resolveCollisionY(phy1, phy2);
            }
            else
            {
                resolveCollisionXZ(phy1, phy2);
                if (b1.zMax - b2.zMin < b2.zMax - b1.zMin)
                {
                    if (phy1.dynamic_)
                    {
                        phy1.position.z -= dz / 2.0f;
                    }
                    if (phy2.dynamic_)
                    {
                        phy2.position.z += dz / 2.0f;
                    }
                }
                else
                {
                    if (phy1.dynamic_)
                    {
                        phy1.position.z += dz / 2.0f;
                    }
                    if (phy2.dynamic_)
                    {
                        phy2.position.z -= dz / 2.0f;
                    }
                }
            }

            resolveCollisionWithFriction(phy1, phy2);
        }

        // DYNAMIC ------------------------------------------------------------
        if ((phy1.dynamic_ && phy2.dynamic_) || (phy2.dynamic_ && phy1.dynamic_))
        {
            if (dx < dy && dx < dz)
            {
                resolveCollisionXZ(phy1, phy2);
                if (b1.xMax - b2.xMin < b2.xMax - b1.xMin)
                {
                    phy1.position.x -= dx / 2.0f;
                    phy2.position.x += dx / 2.0f;

                }
                else
                {
                    phy1.position.x += dx / 2.0f;
                    phy2.position.x -= dx / 2.0f;
                    
                }
            }
            else if (dy < dx && dy < dz)
            {
                if (b1.yMax - b2.yMin < b2.yMax - b1.yMin)
                {
                    phy2.gravityForce.y = 0.f;
                    phy1.position.y -= dy / 2.0f;
                    phy2.position.y += dy / 2.0f;
                }
                else
                {
                    phy1.gravityForce.y = 0.f;
                    phy1.position.y += dy / 2.0f;
                    phy2.position.y -= dy / 2.0f;
                }
            }
            else
            {
                resolveCollisionXZ(phy1, phy2);
                if (b1.zMax - b2.zMin < b2.zMax - b1.zMin)
                {
                    phy1.position.z -= dz / 2.0f;
                    phy2.position.z += dz / 2.0f;

                }
                else
                {
                    phy1.position.z += dz / 2.0f;
                    phy2.position.z -= dz / 2.0f;

                }
            }
            resolveCollisionWithFriction(phy1, phy2);
        }

        // TRIGGERS
        if (phy1.trigger) phy1.triggerCollision = true;
        if (phy2.trigger) phy2.triggerCollision = true;
    }

    return collisionDetected;
}

// Transforma las coordenadas de la BB a coordenadas de pantalla
BoundingBox_PE AABB::turnToScreenCoordinates(const BoundingBox_PE &box, float x, float y, float z)
{
    BoundingBox_PE screenBox{
        x + box.xMin - (box.xMax * 0.5f),
        y + box.yMin - (box.yMax * 0.5f),
        z + box.zMin - (box.zMax * 0.5f),
        x + (box.xMax * 0.5f),
        y + (box.yMax * 0.5f),
        z + (box.zMax * 0.5f)};
    return screenBox;
}
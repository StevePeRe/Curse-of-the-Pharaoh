#pragma once

#include <engines/graphic/T_EBillboard.hpp>

struct SParticle : public T_EBillboard
{
    //SParticle() = default;
    SParticle(unsigned int id) { this->setVertex(); }

    void update(double dt)
    {
        lifeTime += dt;
    }

    double lifeTime{0};
    double endTime{0};
    glm::vec3 color{0.0f, 0.0f, 0.0f};

private:
    unsigned int textureId{0};
};
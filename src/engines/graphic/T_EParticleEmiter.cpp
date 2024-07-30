#include <engines/graphic/T_EParticleEmiter.hpp>
#include <engines/graphic/GraphicEngine.hpp>
#include <engines/graphic/SParticle.hpp>
#include <iostream>

void T_EParticleEmiter::draw(GraphicEngine *ge, TNode *node)
{
    if (playing || not particles.empty())
    {
        updateParticles(ge, node);
    }
}

void T_EParticleEmiter::update(GraphicEngine *ge, TNode::key_type node)
{
    double dt = 0.016666666;
    typedef std::vector<TNode::key_type>::iterator particleIt;
    constexpr auto pi = 3.1416;

    auto removeUnvalidParticles = [&]()
    {
        for (auto &particle_id : particles)
        {
            auto sp = ge->getNode(particle_id)->getEntity<SParticle>();
            if (sp->lifeTime < startLifeTime)
                return;
            auto *particle_node = ge->getNode(particle_id);
            treeNode.deleteNode(particle_id);
            particles.erase(particleIt(&particle_id));
        }
    };
    auto isTimeToGenerateParticle = [&]()
    { return maxParticles != particles.size() && 1 / rateOverTime <= rateTimer; };
    auto generateNewParticle = [&]()
    {
        glm::vec3 particle_pos{ge->getNode(node)->getPosition()};
        if (spawnRadius > 0)
        {
            double theta = 2 * pi * ((double)rand() / RAND_MAX);

            if (perimeterSpawn)
            {
                particle_pos.x += std::cos(theta) * spawnRadius;
                particle_pos.z += std::sin(theta) * spawnRadius;
            }
            else
            {
                double r = sqrt((double)rand() / RAND_MAX);
                particle_pos.x += r * spawnRadius * cos(theta);
                particle_pos.z += r * spawnRadius * sin(theta);
            }
        }
        auto p = ge->addSceneParticle(node, 0, particle_pos);
        ge->getNode(node)->addChild(p);
        ge->getNode(p)->setScale(ge->getNode(node)->getScale());
        particles.push_back(p);
        auto *particle_node = ge->getNode(p);
        particle_node->getEntity<SParticle>()->endTime = startLifeTime;
        // el color esta en el emisor de particulas
        particle_node->getEntity<SParticle>()->color = color;
    };
    auto checkToGenerateParticles = [&]()
    {
        if (timer < duration)
        {
            if (maxParticles > particles.size())
            {
                if (isTimeToGenerateParticle())
                {
                    generateNewParticle();
                    rateTimer = 0;
                }
                rateTimer += dt;
            }
            timer += dt;
        }

        else if (looping)
        {
            playing = true;
            timer = 0;
        }
        else
        {
            playing = false;
        }
    };
    removeUnvalidParticles();
    checkToGenerateParticles();
}

void T_EParticleEmiter::updateParticles(GraphicEngine *ge, TNode *node)
{
    double dt{0.016666666};

    auto updateParticles_impl = [&]()
    {
        for (auto &particle_id : particles)
        {
            auto *particle_node = ge->getNode(particle_id);
            if (particle_node == nullptr)
                continue;
            auto *sp = particle_node->getEntity<SParticle>();
            sp->update(dt);
        }
    };
    updateParticles_impl();

    auto updateParticles_afectors = [&]()
    {
        for (auto &particle_id : particles)
        {
            for (auto &affector_ : affectorList)
            {
                affector_->affect(ge->getNode(particle_id), dt);   
            }
        }
    };
    updateParticles_afectors();
}

void T_EParticleEmiter::play()
{
    timer = 0;
    playing = true;
}

bool T_EParticleEmiter::pushAffector(std::unique_ptr<Affector> affector_)
{
    std::vector<std::unique_ptr<Affector>>::iterator it;

    for (it = affectorList.begin(); it != affectorList.end(); it++)
    {
        if ((*it)->getType() == affector_->getType())
        {
            return false;
        }
    }

    affectorList.push_back(std::move(affector_));
    return true;
}
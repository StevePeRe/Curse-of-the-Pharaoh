#pragma once

#include <engines/graphic/TNode.hpp>
#include <engines/graphic/TEntity.hpp>
#include <engines/graphic/RSkinModel.hpp>
#include <engines/graphic/SAnimator.hpp>

struct T_AnimationMesh : public TEntity {
    T_AnimationMesh(RSkinModel*);
    void loadMesh(std::string);
    void draw(GraphicEngine *ge, TNode *node);

    // void setBorder(glm::vec4 color, double width = 1);
    // void isSpawning();
    
    RSkinModel *model_ {};
    SAnimator animator_ {};
    
    private:
};

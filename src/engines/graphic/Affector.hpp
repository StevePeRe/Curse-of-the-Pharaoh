#pragma once

struct TNode;

enum AFFECTOR_TYPE {
    NONE = 0,
    ROTATE,
    DIRECTION
};

struct Affector
{
    Affector() : enabled{true} {};
    virtual ~Affector() = default;
    
    virtual void affect(TNode *node, double dt) = 0;
    virtual AFFECTOR_TYPE getType() = 0;
    virtual void setEnabled(bool en) { enabled = en; }
    virtual bool getEnabled() const { return enabled; }

    private:
        bool enabled{false};
};
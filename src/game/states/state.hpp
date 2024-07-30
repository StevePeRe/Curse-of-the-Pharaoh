#pragma once
// util
#include <game/util/GameTimer.hpp>
// libs
#include <stack>
#include <memory>
#include <type_traits>
#include <iostream>
#include <engines/graphic/GraphicEngine.hpp>

struct StateBase
{
    virtual void update() = 0;
    virtual bool alive() = 0;
    virtual ~StateBase() = default;
};

struct StateManager 
{
    explicit StateManager() = default;

    template <typename State_t, typename... Ts>
    void pushState(Ts&&... args){
        static_assert(std::is_base_of<StateBase, State_t>::value, "ERROR! Invalid State");
        m_States.push(std::make_unique<State_t>(std::forward<decltype(args)>(args)...));
        
    }

    void update(){
        if(alive()){
            auto& state { m_States.top() };
            if(state && state->alive()){
                state->update();
            }else{
                m_States.pop();
            }
        }
    }

    bool alive() { return !m_States.empty(); }

private:
    std::stack<std::unique_ptr<StateBase>> m_States;
};

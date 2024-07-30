#pragma once
#include "node.hpp"
#include <iostream>
#include <vector>
#include <initializer_list>

struct BTnodeSequence : BTnode{
    using value_type = BTnode*;
    using container_type = std::vector<value_type>;
    using init_list = std::initializer_list<value_type>;
    using iterator = std::vector<value_type>::iterator;

    BTnodeSequence(init_list l) : nodes{l} {}

    void resetSequence(){ currentNodeIt = nodes.begin(); }

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept final{
        if(currentNodeIt == nodes.end()){
            resetSequence();
        }
        auto status = (*currentNodeIt)->run(etcx, dt);
        switch(status){
            case BTnodeStatus::fail: { resetSequence(); return BTnodeStatus::fail; }
            break;
            case BTnodeStatus::running: { return BTnodeStatus::running; }
            break;
            case BTnodeStatus::success: {
                ++currentNodeIt;
                if(currentNodeIt == nodes.end()){
                    resetSequence();
                    return BTnodeStatus::success;
                }
            }
            break;
            default:
                // std::cout << "0000000 DEFAULT" << std::endl;
                ++currentNodeIt;
                if(currentNodeIt == nodes.end()){
                    // std::cout << "0000000 RESET SEQUENCE" << std::endl;
                    resetSequence();
                    return BTnodeStatus::success;
                }
            break;
        }
        return BTnodeStatus::running; //no deberia llegar aqui nunca pero si no pones esto se queja
    }

    private:
        container_type nodes {};
        iterator currentNodeIt { nodes.begin() };
};
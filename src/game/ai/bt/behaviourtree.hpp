#pragma once
#include <vector>
#include <memory>
#include "node.hpp"
#include <game/ai/include_all.hpp>
#include <bitset>
//#include <concepts>

struct BehaviourTree{
    using value_type = std::unique_ptr<BTnode, BTnode::Deleter>;
    using NodeStorage = std::vector<value_type>;
    using MemoryStorage = std::unique_ptr<std::byte[]>;

    explicit BehaviourTree(){}

    BTnodeStatus run(EntityContext& etcx, float dt) noexcept{
        if(nodes.size() > 0){
            return nodes.back()->run(etcx, dt);
        }
        return BTnodeStatus::fail;
    }

    template <typename NodeType, typename... ParamTypes>
    NodeType& createNode(ParamTypes&&... params){
        //reservar memoria
        ptr_reserved -= sizeof(NodeType);
        if(ptr_reserved<mem.get()){
            ptr_reserved += sizeof(NodeType);
            throw std::bad_alloc{};
        }
        //crear nodo
        auto* pnode = new (ptr_reserved) NodeType{std::forward<ParamTypes>(params)...};
        nodes.emplace_back(pnode);
        return *pnode;
    }   

    void initTreeZombie(){
        this->createNode<BTnodeSelector>(   
        &this->createNode<BTnodeSequence>(
            &this->createNode<BTdecoratorCheckDistance>(
                &this->createNode<BTactionAttackClose>(),
                &this->createNode<BTdecoratorCheckSB>(
                    &this->createNode<BTactionArrive>(),
                    &this->createNode<BTactionSeek>(),
                    &this->createNode<BTactionFlee>(),
                    &this->createNode<BTactionFindPath>()
                )                
            ),
            &this->createNode<BTactionMove>()
        ),
        &this->createNode<BTnodeSequence>(
            &this->createNode<BTactionIdle>(),
            &this->createNode<BTactionMove>()
        )
    );
    }

    void initTreeMomia(){
        this->createNode<BTnodeSelector>(   
        &this->createNode<BTnodeSequence>(
            &this->createNode<BTdecoratorCheckDistance>(
                &this->createNode<BTactionAttackClose>(),
                &this->createNode<BTactionAttackFar>()             
            ),
            &this->createNode<BTdecoratorCheckSB>(
                &this->createNode<BTactionArrive>(),
                &this->createNode<BTactionSeek>(),
                &this->createNode<BTactionFlee>(),
                &this->createNode<BTactionFindPath>()
            )  
        ),
        &this->createNode<BTnodeSequence>(
            &this->createNode<BTactionIdle>(),
            &this->createNode<BTactionMove>()
        )
    );
    }

    void initTreeMomiaLaberinto(){
        this->createNode<BTnodeSelector>(   
            &this->createNode<BTnodeSequence>(
                &this->createNode<BTdecoratorCheckDistance>(
                   &this->createNode<BTactionAttackClose>(),
                   &this->createNode<BTactionFindPath>()                
                ),
                &this->createNode<BTactionCheckGoalReached>(),
                &this->createNode<BTactionGetGoal>(),
                &this->createNode<BTactionMove>()
            ),
            &this->createNode<BTnodeSequence>( //patrulla 
                // &this->createNode<BTactionGetGoal>(),
                &this->createNode<BTactionCheckGoalReached>(),
                &this->createNode<BTactionGetGoal>(),
                &this->createNode<BTactionMove>()
            ),
            &this->createNode<BTactionMove>()
        );
    }
    
    //void initTreeEscarabajo(){
    //    this->createNode<BTnodeSelector>(   
    //        &this->createNode<BTnodeSequence>( //seq2
    //            &this->createNode<BTactionCheckJesFar>(),
    //            &this->createNode<BTactionPursue>()
    //    ),
    //        &this->createNode<BTnodeSequence>( //seq3 
    //            &this->createNode<BTactionIdle>()
    //    )
    //);
    //}

    void clearNodes(){
        nodes.clear();
        ptr_reserved = mem.get() + mem_size;
    }

    int numNodes(){
        return this->nodes.size();
    }

    private:
        std::size_t   mem_size     { 1024 };
        MemoryStorage mem          { std::make_unique<std::byte[]>(mem_size) };
        std::byte*    ptr_reserved { mem.get() + mem_size };
        NodeStorage   nodes        {};
};
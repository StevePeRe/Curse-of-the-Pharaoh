#include <engines/graphic/TNodeTree.hpp>
#include <engines/graphic/TNode.hpp>
#include <bitset>
#include <cstring>
#include <iostream>

TNodeTree::key_type TNodeTree::createNode(BUILD_NODE_C)
{
    auto *node_ptr = end_ptr + sizeof(TNode);

    constexpr size_t alignment = alignof(TNode);
    uintptr_t alignedPtr = reinterpret_cast<uintptr_t>(node_ptr);
    alignedPtr = (alignedPtr + alignment - 1) & ~(alignment - 1);
    node_ptr = reinterpret_cast<decltype(node_ptr)>(alignedPtr);

    if (node_ptr >= capacity)
    {
        node_ptr = realloc(node_ptr);
    }

    alignas(TNode) std::byte *alginedNodePtr = reinterpret_cast<std::byte *>(end_ptr);
    TNode *node = new (alginedNodePtr) TNode(*this, parent, ++nextId, position, rotation, scale);

    end_ptr = node_ptr;

    return node->id;
}
std::byte *TNodeTree::realloc(std::byte *nodePtr)
{
    std::byte *oldBeginPtr = begin_ptr;
    std::byte *oldEndPtr = end_ptr;
    auto oldMemSize = memory_size;

    memory_size *= 2;
    auto newBytes = std::make_unique<std::byte[]>(memory_size);
    begin_ptr = newBytes.get();
    capacity = begin_ptr + memory_size;

    size_t const distance{size_t(begin_ptr - oldBeginPtr)};
    end_ptr = oldEndPtr + distance;

    std::memcpy(begin_ptr, oldBeginPtr, oldMemSize);

    bytes.reset(newBytes.release());

    return nodePtr + distance;
}
void TNodeTree::deleteNode(key_type const nodeId)
{
    auto it = at(nodeId);

    base_type *node = it.base();

    assert(node);

    auto from = node + 1;
    auto to = node;
    auto size = end_ptr - reinterpret_cast<std::byte *>(from);

    std::memmove(to, from, size);

    std::memset(end_ptr - sizeof(*node), 0, sizeof(*node));

    end_ptr -= sizeof(*node);
}
[[nodiscard]] TNodeTree::base_type *TNodeTree::getById(key_type const nodeId) const
{
    auto it = at(nodeId);
    if (it >= begin_ptr && it <= end_ptr)
    {
        return it.base();
    }

    return nullptr;
}
TNodeTree::Iterator TNodeTree::at(key_type id) const
{
    auto hasId = [id](auto *node)
    { return node->id == id; };

    for (Iterator it{begin_ptr}; it < end_ptr; ++it)
    {
        if (hasId(it.base()))
        {
            return it;
        }
    }

    return {end_ptr};
}
#pragma once

#include <memory>
#include <engines/graphic/TNode.hpp>

#define BUILD_NODE_H TNodeTree::key_type parent = 1, [[maybe_unused]] std::size_t id = -1, glm::vec3 position = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0}, glm::vec3 scale = {1, 1, 1}
#define BUILD_NODE_C TNodeTree::key_type parent, [[maybe_unused]] std::size_t id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale

struct TNodeTree
{
    using base_type = TNode;
    using key_type = base_type::key_type;
    using memory_storage = std::unique_ptr<std::byte[]>;
    using value_type = std::unique_ptr<base_type, base_type::DELETER>;

    struct Iterator
    {
        Iterator(std::byte *pointer) : ptr{reinterpret_cast<base_type*>(pointer)} {};
        Iterator(base_type *pointer) : ptr{pointer} {};
        Iterator(Iterator const &it) : ptr{it.ptr} {};

        base_type* base() { return ptr; }
        void operator++() { ++ptr; }
        auto operator<=>(Iterator const &it) const = default;
        auto operator<=>(std::byte* byte) const { return operator<=>(Iterator{byte}); }
        Iterator& operator=(Iterator &&it) = default;
        Iterator& operator=(Iterator const &it) = default;

        private:
            base_type *ptr; 
    };

    Iterator begin() { return Iterator(begin_ptr); }
    Iterator end() { return Iterator(end_ptr); }    

    std::byte* realloc(std::byte *bytePtr);

    key_type createNode(BUILD_NODE_H);
    void deleteNode(key_type const nodeId);

    void resetId() { nextId = 1; };

    [[nodiscard]] TNodeTree::base_type *getById(key_type const nodeId) const;

private:
    size_t memory_size{1024};
    memory_storage bytes{std::make_unique<std::byte[]>(memory_size)};
    std::byte *begin_ptr{bytes.get()};
    std::byte *end_ptr{bytes.get()};
    std::byte *capacity{bytes.get() + memory_size};
    key_type nextId{0};

    Iterator at(key_type id) const;
};
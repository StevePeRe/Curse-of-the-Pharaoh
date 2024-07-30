#pragma once

#include <concepts>
#include <vector>
#include <engines/graphic/Resource.hpp>
#include <engines/graphic/ResourceTypes.hpp>

template <typename T>
concept ResourceType = std::derived_from<T, Resource>;

template <ResourceType... ResourceTypes>
struct ResourceManager
{
    explicit ResourceManager() = default;
    
    template <ResourceType typeR>
    using Container = std::vector<std::unique_ptr<typeR>>;

    template <ResourceType typeR>
    typeR* add(std::string fileName);
    template <ResourceType typeR>
    typeR* get(std::string fileName);
    template <ResourceType typeR>
    Container<typeR>& get();
    template <ResourceType typeR>
    void clear();
    template <ResourceType typeR>
    size_t size();

    private:
        std::tuple<Container<ResourceTypes>...> resources;
};
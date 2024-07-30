#include <engines/graphic/ResourceManager.hpp>
#include <cstddef>
#include <memory>

template <ResourceType... ResourceTypes>
template <ResourceType typeR>
typeR *ResourceManager<ResourceTypes...>::add(std::string fileName)
{
    typeR *resource = get<typeR>(fileName);

    if (resource == nullptr)
    {
        std::unique_ptr<typeR> resourcePtr = std::make_unique<typeR>();
        resource = resourcePtr.get();
        resource->loadResource(fileName);
        // Lo movemos para que dentro del push_back solo haya un puntero
        // para seguir siendo unico
        get<typeR>().push_back(std::move(resourcePtr));
        // Para mover un unique_point se utiliza mov
        // Push_back hace una copia exacta de un objeto
    }

    return resource;
}

template <ResourceType... ResourceTypes>
template <ResourceType typeR>
typeR *ResourceManager<ResourceTypes...>::get(std::string fileName)
{
    typename ResourceManager<ResourceTypes...>::Container<typeR>::iterator it;
    for (it = get<typeR>().begin(); it < get<typeR>().end(); it++)
    {
        if ((*it)->getName().compare(fileName) == 0)
        {
            return &*(*it);
        }
    }
    return nullptr;
}

template <ResourceType... ResourceTypes>
template <ResourceType typeR>
ResourceManager<ResourceTypes...>::Container<typeR> &ResourceManager<ResourceTypes...>::get()
{
    return std::get<Container<typeR>>(resources);
}

template <ResourceType... ResourceTypes>
template <ResourceType typeR>
void ResourceManager<ResourceTypes...>::clear()
{
    get<typeR>().clear();
}

template <ResourceType... ResourceTypes>
template <ResourceType typeR>
size_t ResourceManager<ResourceTypes...>::size()
{
    return get<typeR>().size();
}
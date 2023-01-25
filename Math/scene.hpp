#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Entity/entity.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace svarog
{
    class Scene
    {
        // Список объектов
        std::vector<std::unique_ptr<Entity>> _entities;

    public:

        // Имя
        std::string name;

        Scene();

        Scene(const std::string& name);

        // Создать сущьность
        unsigned long CreateEntity(const std::string& entity_name);

        // Удалить сущьность
        bool DestroyEntity(unsigned long entity_index);

        // Количество сущьностей
        unsigned int EntityCount();
    };

    Scene::Scene() : name("Entity")
    {}

    Scene::Scene(const std::string& name) : name(name)
    {}

    unsigned long Scene::CreateEntity(const std::string& entity_name)
    {
        _entities.emplace_back(std::make_unique<Entity>(entity_name));

        return _entities.size() - _entities.size() == 0 ? 0 : 1;
    }

    unsigned int Scene::EntityCount()
    {
        return _entities.size();
    }

    bool Scene::DestroyEntity(unsigned long entity_index)
    {
        if(_entities.size() == 0 || entity_index >= _entities.size())
            return false;

        _entities.erase(_entities.begin() + entity_index);

        return true;
    }
}
#endif
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "../Components/component.hpp"

namespace svarog
{
    class Entity
    {
        // Компаненты
        std::vector<std::unique_ptr<Component>> _components;
    
    public:

        // Имя
        std::string name;

        Entity();

        Entity(const std::string& name);
        
        template<typename ComponentType, typename ... Agrs>
        // Добавление компанента
        void AddComponent(Agrs&&... params);

        template<typename ComponentType>
        // Удаление компанента
        bool RemoveComponent();

        // Удаление компанентов
        unsigned int RemoveAllComponents();
        
        template<typename ComponentType>
        // Удаление нескольких совпавших компанентов
        unsigned int RemoveComponents();

        template<typename ComponentType>
        // Получение первого совпавшего компанента
        ComponentType& GetComponent();

        template<typename ComponentType>
        // Получение нескольких совпавших компанентов
        std::vector<ComponentType*> GetComponents();
    };

    Entity::Entity() : name("Game object")
    {}

    Entity::Entity(const std::string& name) : name(name)
    {}

    template<typename ComponentType, typename... Agrs>
    void Entity::AddComponent(Agrs&&... params)
    {
        _components.emplace_back(std::make_unique<ComponentType>(std::forward<Agrs>(params)...));
    }

    template<typename ComponentType>
    bool Entity::RemoveComponent()
    {
        if (_components.empty())
            return false;

        auto& index = std::find_if(_components.begin(), _components.end(), [class_type = ComponentType::Type](auto& component) 
        { 
            return component->IsClassType(class_type); 
        });

        bool success = index != _components.end();
        
        if(success)
            _components.erase(index);

        return success;
    }

    unsigned int Entity::RemoveAllComponents()
    {
        if (_components.empty())
            return 0;

        unsigned int count = _components.size();

        _components.clear();

        return count;
    }

    template<typename ComponentType>
    unsigned int Entity::RemoveComponents()
    {
        if(_components.empty())
            return 0;

        unsigned int count = 0;

        bool success = false;

        do
        {
            auto index = std::find_if(_components.begin(), _components.end(), [class_type = ComponentType::Type](auto& component) 
            { 
                return component->IsClassType(class_type); 
            });

            success = index != _components.end();

            if(success)
            {
                _components.erase(index);
                count++;
            }

        }while(success);

        return count;
    }

    template<typename ComponentType>
    ComponentType& Entity::GetComponent()
    {
        for(auto&& component : _components) 
            if(component->IsClassType(ComponentType::Type))
                return *static_cast<ComponentType*>(component.get());

        return *std::unique_ptr<ComponentType>(nullptr);
    }

    template<typename ComponentType>
    std::vector<ComponentType*> Entity::GetComponents()
    {
        std::vector<ComponentType*> componentsOfType;

        for(auto&& component : _components)
            if(component->IsClassType(ComponentType::Type))
                componentsOfType.emplace_back(static_cast<ComponentType*>(component.get()));

        return componentsOfType;
    }
}


#endif
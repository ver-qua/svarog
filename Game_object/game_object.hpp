#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "../Components/component.hpp"

namespace svarog
{
    class GameObject
    {
        // Компаненты
        std::vector<std::unique_ptr<Component>> _components;
    
    public:

        // Имя
        std::string name;

        GameObject();

        GameObject(std::string&& name);

        // Тип Компанента, Аргументы
        template<typename ComponentType, typename ... Agrs>
        // Добавление компанента
        void AddComponent(Agrs&&... params);

        // Тип Компанента
        template<typename ComponentType>
        // Удаление компанента
        bool RemoveComponent();

        // Удаление компанентов
        unsigned int RemoveAllComponents();
        
        // Тип Компанента
        template<typename ComponentType>
        // Удаление нескольких совпавших компанентов
        unsigned int RemoveComponents();

        // Тип Компанента
        template<typename ComponentType>
        // Получение первого совпавшего компанента
        ComponentType& GetComponent();

        // Тип Компанента
        template<typename ComponentType>
        // Получение нескольких совпавших компанентов
        std::vector<ComponentType*> GetComponents();
    };

    GameObject::GameObject() : name("Game object")
    {}

    GameObject::GameObject(std::string && name) : name(name)
    {}

    template<typename ComponentType, typename... Agrs>
    void GameObject::AddComponent(Agrs&&... params)
    {
        _components.emplace_back(std::make_unique<ComponentType>(std::forward<Agrs>(params)...));
    }

    template<typename ComponentType>
    bool GameObject::RemoveComponent()
    {
        if (_components.empty())
            return false;

        auto& index = std::find_if(_components.begin(), _components.end(), [class_type = ComponentType::Type](auto& component) 
        { 
            return component->IsClassType(class_type); 
        });

        bool success = index != _components.end();
        
        if (success)
        {
            _components.erase(index);
        }

        return success;
    }

    unsigned int GameObject::RemoveAllComponents()
    {
        if (_components.empty())
            return 0;

        unsigned int count = _components.size();

        _components.clear();

        return count;
    }

    template<typename ComponentType>
    unsigned int GameObject::RemoveComponents()
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
    ComponentType& GameObject::GetComponent()
    {
        for (auto&& component : _components) 
            if(component->IsClassType(ComponentType::Type))
                return *static_cast<ComponentType*>(component.get());

        return *std::unique_ptr<ComponentType>(nullptr);
    }

    template<typename ComponentType>
    std::vector<ComponentType*> GameObject::GetComponents()
    {
        std::vector< ComponentType * > result;

        for(auto&& component : _components)
            if(component->IsClassType(ComponentType::Type))
                result.emplace_back(static_cast<ComponentType*>(component.get()));

        return result;
    }
}


#endif
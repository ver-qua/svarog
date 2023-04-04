#ifndef _BASE_COMPONENT_H_
#define _BASE_COMPONENT_H_

#include<iostream>
#include<string>
#include<functional>

#define TO_STRING(input) #input

// Объявление класса
#define CLASS_DECLARATION(class)                                \
                                                                \
    /* Хеш идентификатор типа компонента */                     \
    const static std::size_t type;                              \
                                                                \
    /* Функция проверки идентификатора */                       \
    bool IsClassType(const std::size_t type) const override;    \
                                                                \
    /* Имя компонента */                                        \
    std::string name = TO_STRING(class);                        \

// Описание класса
#define CLASS_DEFENITION(parent_class, child_class)                                             \
    const std::size_t child_class::type = std::hash<std::string>()(TO_STRING(child_class));     \
                                                                                                \
    bool child_class::IsClassType(const std::size_t type) const                                 \
    {                                                                                           \
        if (type == child_class::type)                                                          \
            return true;                                                                        \
        return parent_class::IsClassType(type);                                                 \
    }                                                                                           \

namespace svg
{
    // Базовый класс компанента
    class Component
    {
    public:
        // Хеш идентификатор типа компонента
        const static std::size_t type;

        // Имя компонента
        std::string name;
        
        Component();

        Component(const std::string& name);

        // Функция проверки идентификатора
        virtual bool IsClassType(const std::size_t type) const;
    };

    const std::size_t Component::type = std::hash<std::string>()(TO_STRING(Component));

    bool Component::IsClassType(const std::size_t type) const
    {
        return this->type == type;
    }

    Component::Component() : name("Unnamed сomponent")
    {}

    Component::Component(const std::string& name) : name(name)
    {}
}

#endif
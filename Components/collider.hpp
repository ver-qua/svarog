#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Math/vec2.hpp"
#include "vector"
#include "../Math/transform.hpp"
#include "component.hpp"

namespace svarog
{
    class Collider : public Component
    {
        CLASS_DECLARATION(Collider)

        //AABB
        svarog::vec2<double> _AABB[2];

        // Обновление AABB
        void _UpdateAABB();

    public:
    
        // Трансформация
        svarog::Transform transform;

        // Триггер
        bool trigger;

        Collider();
        
        Collider(std::string name, svarog::Transform transform, bool trigger = false);

    };
    
    CLASS_DEFENITION(Component, Collider)

    Collider::Collider() : name("Collider"), transform(svarog::Transform()), trigger(false)
    {}

    Collider::Collider(std::string name, svarog::Transform transform, bool trigger) : name(name), transform(transform), trigger(trigger)
    {}

    void _UpdateAABB()
    {}
}

#endif
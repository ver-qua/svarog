#ifndef _CIRCLE_COLLIDER_H_
#define _CIRCLE_COLLIDER_H_

#include "collider.hpp"
#include "component.hpp"
#include "../Math/transform.hpp"

namespace svarog
{
    class CircleCollider: public Collider
    {   
        CLASS_DECLARATION(CircleCollider)

        void _UpdateAABB();

    public:
        // Радиус
        double radius;

        CircleCollider();

        CircleCollider(std::string name, double radius, svarog::Transform transform, bool trigger);
    };

    CLASS_DEFENITION(Collider, CircleCollider)

    CircleCollider::CircleCollider(): Collider::Collider(), name("Circle collider"), radius(1)
    {}

    CircleCollider::CircleCollider(std::string name, double radius, svarog::Transform transform, bool trigger): Collider::Collider("Circle collider", transform, trigger), radius(radius)
    {}

    void CircleCollider::_UpdateAABB()
    {
        _AABB[0] = {-1, -1};
        _AABB[1] = {1, 1};
    }
}

#endif
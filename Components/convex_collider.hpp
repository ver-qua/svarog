#ifndef _ConvexCollider_H_
#define _ConvexCollider_H_

#include "collider.hpp"
#include "../Math/transform.hpp"

namespace svarog
{
    class ConvexCollider : public Collider
    {

        CLASS_DECLARATION(ConvexCollider)

        // Форма для рендера
        std::vector<svarog::vec2<double>> _shape;

        // Оригинальная форма
        std::vector<svarog::vec2<double>> _originalShape;

        public:

        ConvexCollider();

        ConvexCollider(std::string name, std::vector<svarog::vec2<double>> shape, svarog::Transform transform, bool trigger = false);
    };

    CLASS_DEFENITION(Collider, ConvexCollider)

    ConvexCollider::ConvexCollider() : Collider(), _shape({{0, 0}, {1, 1}, {1, -1}}), _originalShape({{0, 0}, {1, 1}, {1, -1}})
    {}

    ConvexCollider::ConvexCollider(std::string name, std::vector<svarog::vec2<double>> shape, svarog::Transform transform, bool trigger) : Collider(name, transform, trigger), _shape(shape), _originalShape(shape)
    {}
}

#endif
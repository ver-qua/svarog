#ifndef _CIRCLE_COLLIDER_H_
#define _CIRCLE_COLLIDER_H_

#include"collider.cpp"
#include"component.cpp"
#include"../Math/transform.cpp"

#include"../Debug/logit.cpp"

namespace svg
{
    class CircleCollider: public Collider
    {   

    public:
        CLASS_DECLARATION(CircleCollider)

        // Радиус
        double radius;

        CircleCollider();

        CircleCollider(const std::string& name, double radius, const Transform& transform, bool trigger);

        std::array<vec2<double>, 2> GetAABB(Transform final_transform) override;
    };

    CLASS_DEFENITION(Collider, CircleCollider)

    CircleCollider::CircleCollider(): Collider::Collider(), name("Circle collider"), radius(20)
    {}

    CircleCollider::CircleCollider(const std::string& name, double radius, const Transform& transform, bool trigger): Collider::Collider(name, transform, trigger), radius(radius)
    {}

    std::array<vec2<double>, 2> CircleCollider::GetAABB(Transform final_transform)
    {
        logit("BEEING USED", "CircleCollider");
        return {vec2<double>(radius * -1, radius), vec2<double>(radius, radius * -1)};
    }
}

#endif
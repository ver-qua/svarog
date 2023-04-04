#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <array>
#include<vector>

#include"../Math/vec2.cpp"
#include"../Math/transform.cpp"
#include"component.cpp"

#include"../Debug/logit.cpp"

namespace svg
{
    class Collider : public Component
    {
    public:
        CLASS_DECLARATION(Collider)

        // Трансформация
        Transform transform;

        // Триггер ли
        bool trigger;

        Collider();
        
        Collider(const std::string& name, const Transform& transform, bool trigger = false);

        virtual std::array<vec2<double>, 2> GetAABB(Transform final_transform);
    };
    
    CLASS_DEFENITION(Component, Collider)

    Collider::Collider() : name("Collider"), transform(Transform()), trigger(false)
    {}

    Collider::Collider(const std::string& name, const Transform& transform, bool trigger) : name(name), transform(transform), trigger(trigger)
    {}

    std::array<vec2<double>, 2> Collider::GetAABB(Transform final_transform)
    {
        logit("BEEING USED", "Collider");
        return std::array<vec2<double>, 2>();
    }
}

#endif
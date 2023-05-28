#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include<vector>

#include"../Math/vec2.cpp"
#include"../Math/physic_material.cpp"
#include"component.cpp"
#include"../Math/transform.cpp"

namespace svg
{
    class Rigitbody : public Component
    {
    public:
        CLASS_DECLARATION(Rigitbody)

        PhysicMaterial physic_material;

        vec2<double> velocity;
        vec2<double> acceleration;
        vec2<double> forse;

        /*
        vec2<double> angular_velocity;
        vec2<double> angular_acceleration;
        vec2<double> torque;
        */

        Transform transform;

        Rigitbody();

        Rigitbody(Transform transform, PhysicMaterial physic_material, vec2<double> velocity, vec2<double> acceleration, vec2<double> forse);
    };

    Rigitbody::Rigitbody() : transform(Transform()), physic_material(PhysicMaterial()), velocity(vec2<double>()), acceleration(vec2<double>()), forse(vec2<double>())
    {}

    Rigitbody::Rigitbody(Transform transform, PhysicMaterial physic_material, vec2<double> velocity, vec2<double> acceleration, vec2<double> forse) : transform(transform), physic_material(physic_material), velocity(velocity), acceleration(acceleration), forse(forse)
    {}

    CLASS_DEFENITION(Component, Rigitbody)
}

#endif
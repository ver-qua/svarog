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

        Transform transform;
    };

    CLASS_DEFENITION(Component, Rigitbody)
}

#endif
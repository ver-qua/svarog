#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include <vector>
#include "../Math/vec2.hpp"
#include "../Math/physic_material.hpp"
#include "component.hpp"

namespace svarog
{
    class Rigitbody : public Component
    {
        CLASS_DECLARATION(Rigitbody)
    };

    CLASS_DEFENITION(Component, Rigitbody)
}

#endif
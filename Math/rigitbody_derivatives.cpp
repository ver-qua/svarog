#ifndef _RIGITBODY_DERIVATIVES_H_
#define _RIGITBODY_DERIVATIVES_H_

#include"vec2.cpp"

namespace svg
{
    struct RigitbodyDerivatives
    {
        vec2<double> velocity;
        vec2<double> acceleration;

        vec2<double> angular_velocity;
        vec2<double> angular_acceleration;
    };
}

#endif
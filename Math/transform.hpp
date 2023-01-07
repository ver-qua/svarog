#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "vec2.hpp"

namespace svarog
{
    class Transform
    {
    public:
    
        // Позиция
        svarog::vec2<double> position;

        // Поворот
        double rotation;

        Transform();

        Transform(svarog::vec2<double> position, double rotation);
    };

    Transform::Transform() : position({0, 0}), rotation(0)
    {}

    Transform::Transform(svarog::vec2<double> position, double rotation = 0) : position(position), rotation(rotation)
    {}
}

#endif
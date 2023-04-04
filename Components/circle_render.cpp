#ifndef _CIRCLE_RENDER_H_
#define _CIRCLE_RENDER_H_

#include<vector>

#include"component.cpp"
#include"render.cpp"
#include"../Math/vec2.cpp"
#include"../Math/vec3.cpp"
#include"../Math/transform.cpp"

namespace svg
{
    class CircleRender : public Render
    {
    public:
        CLASS_DECLARATION(CircleRender)

        double radius;

        // Цвет
        vec3<unsigned char> color;

        // Трансформация
        Transform transform;

        CircleRender();

        CircleRender(vec3<unsigned char> color, Transform transform);
    };

    CLASS_DEFENITION(Render, CircleRender)

    CircleRender::CircleRender() : radius(10), color({31, 206, 203}), transform()
    {}

    CircleRender::CircleRender(svg::vec3<unsigned char> color, Transform transform) : color(color), transform(transform)
    {}
}

#endif
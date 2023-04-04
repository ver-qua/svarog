#ifndef _RENDER_H_
#define _RENDER_H_

#include<vector>

#include"component.cpp"
#include"../Math/vec2.cpp"
#include"../Math/vec3.cpp"
#include"../Math/transform.cpp"

namespace svg
{
    class Render : public Component
    {
    public:
        CLASS_DECLARATION(Render)

        // Цвет
        vec3<unsigned char> color;

        // Трансформация
        Transform transform;

        Render();

        Render(vec3<unsigned char> color, Transform transform);
    };

    CLASS_DEFENITION(Component, Render)

    Render::Render() : color({31, 206, 203}), transform()
    {}

    Render::Render(svg::vec3<unsigned char> color, Transform transform) : color(color), transform(transform)
    {}
}

#endif
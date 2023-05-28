#ifndef _CONVEX_RENDER_H_
#define _CONVEX_RENDER_H_

#include<vector>

#include"component.cpp"
#include"render.cpp"
#include"../Math/vec2.cpp"
#include"../Math/vec3.cpp"
#include"../Math/transform.cpp"

namespace svg
{
    class ConvexRender : public Render
    {
    public:
        CLASS_DECLARATION(ConvexRender)

        std::vector<vec2<double>> shape;

        // Цвет
        vec3<unsigned char> color;

        // Трансформация
        Transform transform;

        ConvexRender();

        ConvexRender(const std::vector<vec2<double>>& shape, const vec3<unsigned char>& color, const Transform& transform);
    };

    CLASS_DEFENITION(Render, ConvexRender)

    ConvexRender::ConvexRender() : shape({{0, 0}, {20, 20}, {20, -20}}), color({31, 206, 203}), transform()
    {}

    ConvexRender::ConvexRender(const std::vector<vec2<double>>& shape, const vec3<unsigned char>& color, const Transform& transform) : shape(shape), color(color), transform(transform)
    {}
}

#endif
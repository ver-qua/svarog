#ifndef _RENDER_MATERIAL_H_
#define _RENDER_MATERIAL_H_

#include<vector>

#include"vec3.cpp"
#include"vec2.cpp"

namespace svg
{
    class RenderMaterial
    { 
    public:  
    
        // Цвет
        svg::vec3<unsigned char> color;

        // Форма
        std::vector<svg::vec2<double>> shape;
        // Оригинальная форма
        std::vector<svg::vec2<double>> original_shape;

        RenderMaterial();

        RenderMaterial(std::vector<svg::vec2<double>> shape, svg::vec3<unsigned char> color = {31, 206, 203});
    };

    RenderMaterial::RenderMaterial()
    {
        this->shape = {{0, 0}, {1, 1}, {1, -1}};
        this->color = {31, 206, 203};
    }

    RenderMaterial::RenderMaterial(std::vector<svg::vec2<double>> shape, svg::vec3<unsigned char> color)
    {
        this->shape = shape;
        this->color = color;
    }
    
}

#endif
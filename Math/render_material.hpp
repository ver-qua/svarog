#ifndef _RENDER_MATERIAL_H_
#define _RENDER_MATERIAL_H_

#include "Math/vec3.hpp"
#include "Math/vec2.hpp"
#include <vector>

namespace svarog
{
    class RenderMaterial
    { 
    public:  
    
        // Цвет
        svarog::vec3<unsigned char> color;

        // Форма
        std::vector<svarog::vec2<double>> shape;
        // Оригинальная форма
        std::vector<svarog::vec2<double>> original_shape;

        RenderMaterial();

        RenderMaterial(std::vector<svarog::vec2<double>> shape, svarog::vec3<unsigned char> color = {31, 206, 203});
    };

    RenderMaterial::RenderMaterial()
    {
        this->shape = {{0, 0}, {1, 1}, {1, -1}};
        this->color = {31, 206, 203};
    }

    RenderMaterial::RenderMaterial(std::vector<svarog::vec2<double>> shape, svarog::vec3<unsigned char> color = {31, 206, 203})
    {
        this->shape = shape;
        this->color = color;
    }
    
}

#endif
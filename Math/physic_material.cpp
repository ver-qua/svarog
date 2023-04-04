#ifndef _PHYSIC_MATERIAL_H_
#define _PHYSIC_MATERIAL_H_

#include"vec2.cpp"

namespace svg
{
    class PhysicMaterial
    {
    public: 

        // Масса
        double mass;

        // Инвертированная масса
        double inversed_mass;

        // Центр масс
        svg::vec2<double> center_of_mass;

        // Прыгучесть?
        double bounciness;

        PhysicMaterial();

        PhysicMaterial(double mass, double bounciness);
    };

    PhysicMaterial::PhysicMaterial(): mass(1), inversed_mass(1), bounciness(1)
    {}

    PhysicMaterial::PhysicMaterial(double mass, double bounciness): mass(mass), inversed_mass(1 / mass), bounciness(bounciness)
    {}
}


#endif
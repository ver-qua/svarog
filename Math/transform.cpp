#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include"vec2.cpp"

namespace svg
{
    class Transform
    {
    public:
    
        // Позиция
        vec2<double> position;

        // Поворот
        double rotation;

        Transform();

        Transform(const svg::vec2<double>& position, double rotation);

        Transform operator+(const Transform& other);

        Transform operator-(const Transform& other);

        Transform& operator+=(const Transform& other);

        Transform& operator-=(const Transform& other);
    };

    Transform::Transform() : position({0, 0}), rotation(0)
    {}

    Transform::Transform(const svg::vec2<double>& position, double rotation = 0) : position(position), rotation(rotation)
    {}

    Transform Transform::operator+(const Transform& other)
    {
        Transform result(this->position + other.position, this->rotation + other.rotation);
        result.position.rotate(this->rotation, this->position);
        return result;
    }

    Transform Transform::operator-(const Transform& other)
    {
        Transform result(this->position - other.position, this->rotation - other.rotation);
        result.position.rotate(this->rotation, this->position);
        return result;
    }

    Transform& Transform::operator+=(const Transform& other)
    {
        this->position += other.position;
        this->position.rotate(this->rotation, this->position);
        this->rotation += other.rotation;
        return *this;
    }

    Transform& Transform::operator-=(const Transform& other)
    {
        this->position += other.position;
        this->position.rotate(this->rotation * -1, this->position);
        this->rotation -= other.rotation;
        return *this;
    }

    
}

#endif
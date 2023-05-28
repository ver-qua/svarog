#ifndef _VEC2_H_
#define _VEC2_H_

#include<math.h>

namespace svg
{
    template <typename T>
    struct vec2
    {      
        static constexpr double DEG_TO_RAD = M_PI / 180;

        T x, y;
        
        // Конструкторы
        vec2();
        
        vec2(T x, T y);

        // Копирование
        vec2(const vec2<T>& original);

        // Сложение
        vec2<T> operator+(const vec2<T>& other);

        vec2<T> operator+(const T& other);

        // Вычетание
        vec2<T> operator-(const vec2<T>& other);

        vec2<T> operator-(const T& other);

        // Умножение
        vec2<T> operator*(const T& other);
        
        vec2<T> operator*(const vec2<T>& other);

        // Деление
        vec2<T> operator/(const T& other);

        // Сравнение
        bool operator==(const vec2<T>& other);

        bool operator!=(const vec2<T>& other);

        // Присваивание
        vec2<T>& operator=(const vec2<T>& other);

        // Добавление
        vec2<T>& operator+=(const vec2<T>& other);

        vec2<T>& operator+=(const T& other);

        // Убавление
        vec2<T>& operator-=(const vec2<T>& other);

        vec2<T>& operator-=(const T& other);

        // Деление
        vec2<T>& operator/=(const T& other);

        // Умножение
        vec2<T>& operator*=(const T& other);

        vec2<T>& operator*=(const vec2<T>& other);
        
        // Длинна
        double lenght();
        
        vec2<T> normalize();

        vec2<T> rotate(double degrees, const vec2<T>& center = vec2<T>());

        vec2<T> normalized();

        vec2<T> rotated(double degrees, const vec2<T>& center = vec2<T>());

        // Скалярное произведение
        static double dot_product(const vec2<T>& first, const vec2<T>& second);

        // Косинус угла между векторами
        static double cos(const vec2<T>& first, const vec2<T>& second);

        // Cинус угла между векторами
        static double sin(const vec2<T>& first, const vec2<T>& second);

        static vec2<T> zero();
    };

    template <typename T>
    vec2<T>::vec2() : x(0), y(0)
    {}

    template <typename T>
    vec2<T>::vec2(T x, T y) : x(x), y(y)
    {}

    template <typename T>
    vec2<T>::vec2(const vec2<T>& original) : x(original.x), y(original.y)
    {}

    template <typename T>
    vec2<T> vec2<T>::operator+(const vec2<T>& other)
    {
        return vec2<T>(this->x + other.x, this->y + other.y);
    }

    template <typename T>
    vec2<T> vec2<T>::operator+(const T& other)
    {
        return vec2<T>(this->x + other, this->y + other);
    }

    template <typename T>
    vec2<T> vec2<T>::operator-(const vec2<T>& other)
    {
        return vec2<T>(this->x - other.x, this->y - other.y);
    }

    template <typename T>
    vec2<T> vec2<T>::operator-(const T& other)
    {
        return vec2<T>(this->x - other, this->y - other);
    }

    template <typename T>
    vec2<T> vec2<T>::operator*(const T& other)
    {
        return vec2<T>(this->x * other, this->y * other);
    }

    template <typename T>
    vec2<T> vec2<T>::operator*(const vec2<T>& other)
    {
        return(this->x * other.x + this->y * other.y);
    }
    template <typename T>
    vec2<T> vec2<T>::operator/(const T& other)
    {
        return vec2<T>(this->x / other, this->y / other);
    }

    template <typename T>
    bool vec2<T>::operator==(const vec2<T>& other)
    {
        return((this->x == other.x) &&(this->y == other.y));
    }

    template <typename T>
    bool vec2<T>::operator!=(const vec2<T>& other)
    {
        return((this->x != other.x) && (this->y != other.y));
    }

    template <typename T>
    vec2<T>& vec2<T>::operator=(const vec2<T>& other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator+=(const vec2<T>& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator+=(const T& other)
    {
        this->x += other;
        this->y += other;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator-=(const vec2<T>& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator-=(const T& other)
    {
        this->x -= other;
        this->y -= other;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator/=(const T& other)
    {
        this->x /= other;
        this->y /= other;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator*=(const T& other)
    {
        this->x *= other;
        this->y *= other;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator*=(const vec2<T>& other)
    {
        this->x *= this->x * other.x;
        this->y *= this->y * other.y;
        return *this;
    }

    template <typename T>
    vec2<T> vec2<T>::rotate(double degrees, const vec2<T>& center)
    {
        degrees = degrees * DEG_TO_RAD;

        vec2<T> rotated;
        vec2<T> relative;

        relative = *this - center;

        rotated.x = relative.x * std::cos(degrees) - relative.y * std::sin(degrees);
        rotated.y = relative.x * std::sin(degrees) + relative.y * std::cos(degrees);

        *this = rotated + center;

        return *this;
    }

    template <typename T>
    vec2<T> vec2<T>::normalize()
    {
        double len = this->lenght();

        this->x /= len;
        this->y /= len;

        return *this;
    }

    template <typename T>
    vec2<T> vec2<T>::rotated(double degrees, const vec2<T>& center)
    {
        degrees = degrees * DEG_TO_RAD;

        vec2<T> rotated;
        vec2<T> relative;

        relative = *this - center;

        rotated.x = relative.x * std::cos(degrees) - relative.y * std::sin(degrees);
        rotated.y = relative.x * std::sin(degrees) + relative.y * std::cos(degrees);

        return rotated + center;
    }

    template <typename T>
    vec2<T> vec2<T>::normalized()
    {
        double len = this->lenght();

        return new vec2<T>(this->x / len, this->y / len);
    }


    template <typename T>
    double vec2<T>::lenght()
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    template <typename T>
    double vec2<T>::dot_product(const vec2<T>& first, const vec2<T>& second) 
    {
        return(first.x * second.x + first.y * second.y);
    }

    template <typename T>
    double vec2<T>::cos(const vec2<T>& first, const vec2<T>& second) 
    {   
        return(vec2<T>::dot_product(first, second) / (first.lenght() * second.lenght()));
    }

    template <typename T>
    double vec2<T>::sin(const vec2<T>& first, const vec2<T>& second) 
    {
        T cosine = vec2<T>::cos(first, second);
        return(cosine >= 0 ? sqrt(1 - pow(cosine, 2)) : sqrt(1 - pow(cosine, 2)) * -1);
    }

    template <typename T>
    vec2<T> vec2<T>::zero()
    {
        return(vec2(0, 0));
    }
}

#endif
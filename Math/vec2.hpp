#ifndef _VEC2_H_
#define _VEC2_H_

#include<math.h>

namespace svarog
{
    template <typename T>
    struct vec2
    {      
        
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
        
        // Длинна
        T lenght();

        // Скалярное произведение
        static T dot_product(const vec2<T>& first, const vec2<T>& second);

        // Косинус угла между векторами
        static T cos(vec2<T>& first, vec2<T>& second);

        // Cинус угла между векторами
        static T sin(vec2<T>& first, vec2<T>& second);

        static T zero();
    };

    template <typename T>
    vec2<T>::vec2()
    {
        this->x = 0;
        this->y = 0;
    }

    template <typename T>
    vec2<T>::vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    template <typename T>
    vec2<T>::vec2(const vec2<T>& original)
    {
        this->x = original.x;
        this->y = original.y;
    }

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
    T vec2<T>::lenght()
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    template <typename T>
    T vec2<T>::dot_product(const vec2<T>& first, const vec2<T>& second)
    {
        return(first.x * second.x + first.y * second.y);
    }

    template <typename T>
    T vec2<T>::cos(vec2<T>& first, vec2<T>& second)
    {   
        return(vec2<T>::dot_product(first, second) / (first.lenght() * second.lenght()));
    }

    template <typename T>
    T vec2<T>::sin(vec2<T>& first, vec2<T>& second)
    {
        T cosinus = cos(first, second);
        return(cosinus >= 0 ? sqrt(1 - pow(cosinus, 2)) : sqrt(1 - pow(cosinus, 2)) * -1);
    }

    template <typename T>
    T vec2<T>::zero()
    {
        return(vec2(0, 0));
    }
}

#endif
#ifndef _VEC3_H_
#define _VEC3_H_

#include<math.h>

namespace svarog
{
    template <typename T>
    struct vec3
    {    
        
        T x, y, z;
        
        // Конструкторы
        vec3();
        
        vec3(T x, T y, T z);

        // Копирование
        vec3(const vec3<T>& original);

        // Сложение
        vec3<T> operator+(const vec3<T>& other);

        vec3<T> operator+(const T& other);

        // Вычетание
        vec3<T> operator-(const vec3<T>& other);

        vec3<T> operator-(const T& other);

        // Умножение
        vec3<T> operator*(const T& other);

        // Деление
        vec3<T> operator/(const T& other);

        // Сравнение
        bool operator==(const vec3<T>& other);

        bool operator!=(const vec3<T>& other);

        // Присваивание
        vec3<T>& operator=(const vec3<T>& other);


        // Добавление
        vec3<T>& operator+=(const vec3<T>& other);

        vec3<T>& operator+=(const T& other);

        // Убавление
        vec3<T>& operator-=(const vec3<T>& other);

        vec3<T>& operator-=(const T& other);

        // Деление
        vec3<T>& operator/=(const T& other);

        // Умножение
        vec3<T>& operator*=(const T& other);
        
        // Длинна
        T lenght();

        // Скалярное произведение
        static T dot_product(const vec3<T>& first, const vec3<T>& second);

        // Косинус угла между векторами
        static T cos(vec3<T>& first, vec3<T>& second);

        // Cинус угла между векторами
        static T sin(vec3<T>& first, vec3<T>& second);

        static T zero();
    };

    template <typename T>
    vec3<T>::vec3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    template <typename T>
    vec3<T>::vec3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template <typename T>
    vec3<T>::vec3(const vec3<T>& original)
    {
        this->x = original.x;
        this->y = original.y;
        this->z = original.z;
    }

    template <typename T>
    vec3<T> vec3<T>::operator+(const vec3<T>& other)
    {
        return vec3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    template <typename T>
    vec3<T> vec3<T>::operator+(const T& other)
    {
        return vec3<T>(this->x + other, this->y + other, this->z + other.z);
    }

    template <typename T>
    vec3<T> vec3<T>::operator-(const vec3<T>& other)
    {
        return vec3<T>(this->x - other.x, this->y - other.y,this->z - other.z);
    }

    template <typename T>
    vec3<T> vec3<T>::operator-(const T& other)
    {
        return vec3<T>(this->x - other, this->y - other, this->z - other);
    }

    template <typename T>
    vec3<T> vec3<T>::operator*(const T& other)
    {
        return vec3<T>(this->x * other, this->y * other, this->z * other);
    }

    template <typename T>
    vec3<T> vec3<T>::operator/(const T& other)
    {
        return vec3<T>(this->x / other, this->y / other, this->z / other);
    }

    template <typename T>
    bool vec3<T>::operator==(const vec3<T>& other)
    {
        return((this->x == other.x) && (this->y == other.y) && (this->x != other.z));
    }

    template <typename T>
    bool vec3<T>::operator!=(const vec3<T>& other)
    {
        return((this->x != other.x) && (this->y != other.y) && (this->x != other.z));
    }

    template <typename T>
    vec3<T>& vec3<T>::operator=(const vec3<T>& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator+=(const vec3<T>& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator+=(const T& other)
    {
        this->x += other;
        this->y += other;
        this->z += other;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator-=(const vec3<T>& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator-=(const T& other)
    {
        this->x -= other;
        this->y -= other;
        this->z -= other;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator/=(const T& other)
    {
        this->x /= other;
        this->y /= other;
        this->z /= other;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator*=(const T& other)
    {
        this->x *= other;
        this->y *= other;
        this->z /= other;
        return *this;
    }

    template <typename T>
    T vec3<T>::lenght()
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    }

    template <typename T>
    T vec3<T>::dot_product(const vec3<T>& first, const vec3<T>& second)
    {
        return(first.x * second.x + first.y * second.y + first.z * second.z);
    }

    template <typename T>
    T vec3<T>::cos(vec3<T>& first, vec3<T>& second)
    {   
        return(vec3<T>::dot_product(first, second) / (first.lenght() * second.lenght()));
    }

    template <typename T>
    T vec3<T>::sin(vec3<T>& first, vec3<T>& second)
    {
        T cosinus = cos(first, second);
        return(cosinus >= 0 ? sqrt(1 - pow(cosinus, 2)) : sqrt(1 - pow(cosinus, 2)) * -1);
    }

    template <typename T>
    T vec3<T>::zero()
    {
        return(vec3(0, 0, 0));
    }
}

#endif
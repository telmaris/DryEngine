#pragma once

#include <random>
#include <ctime>
#include <iostream>

namespace dryengine
{
    namespace math
    {
        struct Vector2
        {
            Vector2();
            Vector2(double a, double b);

            Vector2 &operator+=(const Vector2 &a);
            Vector2 &operator-=(const Vector2 &a);
            friend std::ostream &operator<<(std::ostream &os, const Vector2 &v);
            double operator*(const Vector2 &a);
            Vector2 operator*(const double &a);
            Vector2 operator/(const double &a);
            Vector2 operator-(const Vector2 &a);
            Vector2 operator+(const Vector2 &a);
            bool operator==(const Vector2 &a);
            bool operator!=(const Vector2 &a);
            Vector2 &operator*=(const double &a);

            double Argument();
            double Magnitude();

            double x, y;
        };

        double Random(double a, double b);
    }
}
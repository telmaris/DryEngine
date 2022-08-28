#include "../inc/Maths.hpp"

namespace dryengine
{
    namespace math
    {
        std::mt19937 generator(time(NULL));

        Vector2::Vector2()
        {
            x = 0;
            y = 0;
        }

        Vector2::Vector2(double a, double b)
        {
            x = a;
            y = b;
        }

        double Vector2::Magnitude()
        {
            return sqrt((x * x) + (y * y));
        }

        double Vector2::Argument()
        {
            return atan(y / x);
        }

        Vector2 Vector2::operator+(const Vector2 &a)
        {
            return Vector2(x + a.x, y + a.y);
        }

        Vector2 Vector2::operator-(const Vector2 &a)
        {
            return Vector2(x - a.x, y - a.y);
        }

        double Vector2::operator*(const Vector2 &a)
        {
            return x * a.x + y * a.y;
        }

        Vector2 Vector2::operator*(const double &a)
        {
            return Vector2(x * a, y * a);
        }

        Vector2 Vector2::operator/(const double &a)
        {
            return Vector2(x / a, y / a);
        }

        Vector2 &Vector2::operator+=(const Vector2 &a)
        {
            this->x += a.x;
            this->y += a.y;
            return *this;
        }

        Vector2 &Vector2::operator-=(const Vector2 &a)
        {
            this->x -= a.x;
            this->y -= a.y;
            return *this;
        }

        std::ostream &operator<<(std::ostream &os, const Vector2 &v)
        {
            os << "[" << v.x << ", " << v.y << "]";
            return os;
        }

        bool Vector2::operator==(const Vector2 &a)
        {
            if (this->x == a.x && this->y == a.y)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool Vector2::operator!=(const Vector2 &a)
        {
            if (this->x != a.x || this->y != a.y)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        Vector2 &Vector2::operator*=(const double &a)
        {
            this->x *= a;
            this->y *= a;
            return *this;
        }

        double Random(double a, double b)
        {
            std::uniform_real_distribution<double> dis(a, b);

            return dis(generator);
        }
    }
}
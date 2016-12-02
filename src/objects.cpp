#include "../include/objects.h"

#include <cmath>


Vector3::Vector3(double x, double y, double z)
: x(x), y(y), z(z)
{
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 operator+(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
}

Vector3 operator-(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);
}

Vector3 operator*(double const& l, Vector3 const& a)
{
    return Vector3(l*a.x, l*a.y, l*a.z);
}

Vector3 operator*(Vector3 const& a, double const& l)
{
    return l*a;
}

Vector3 operator/(Vector3 const& a, double const& l)
{
    return (1/l)*a;
}

double sprod(Vector3 const& a, Vector3 const& b)
{
    return a.x*b.x + a.y*b.y + a.z+b.z;
}

Vector3 vprod(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.y*b.z - a.z*b.y,
                   a.x*b.z - a.z*b.x,
		   a.x*b.y - a.y*b.x);
}


double norm(Vector3 v)
{
  return sqrt(normq(v));
}
double normq(Vector3 v)
{
  return v.x*v.x + v.y*v.y + v.z*v.z;
}

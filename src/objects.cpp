#include "../include/objects.h"

#include <cmath>

// ##### VECTOR3 #####

Vector3::Vector3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::normalized() const
{
    return (*this)/norm(*this);
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


std::ostream& operator<<(std::ostream& out, Vector3 const& a)
{
    out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return out;
}



double sprod(Vector3 const& a, Vector3 const& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
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



// ##### RAY #####
Ray::Ray(Vector3 origin, Vector3 direction)
    : origin(origin), direction(direction)
{
}

// ##### SPHERE #####
Sphere::Sphere(Vector3 origin, double radius)
    : origin(origin), radius(radius)
{
}


// ##### CAMERA #####
Camera::Camera(Vector3 origin,
       double fov,
       unsigned int width,
       unsigned int height)
    : origin(origin), fov(fov), image_width(width), image_height(height)
{
}


Ray Camera::ray_to(unsigned int i, unsigned int j)
{
    return Ray(origin, Vector3(j-image_width/2+0.5,
			       i-image_height/2+0.5,
			       -image_height/(2*tan(fov/2.))));
}

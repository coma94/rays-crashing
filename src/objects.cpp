#include "../include/objects.h"
#include "../include/image.h"

#include <cmath>

// ##### VECTOR3 #####

Vector3::Vector3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

inline Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::normalized() const
{
    return (*this)/norm(*this);
}

inline Vector3 operator+(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Vector3 operator-(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline Vector3 operator*(double const& l, Vector3 const& a)
{
    return Vector3(l*a.x, l*a.y, l*a.z);
}

inline Vector3 operator*(Vector3 const& a, double const& l)
{
    return l*a;
}

inline Vector3 operator/(Vector3 const& a, double const& l)
{
    return (1/l)*a;
}


std::ostream& operator<<(std::ostream& out, Vector3 const& a)
{
    out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return out;
}



inline double sprod(Vector3 const& a, Vector3 const& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3 vprod(Vector3 const& a, Vector3 const& b)
{
    return Vector3(a.y*b.z - a.z*b.y,
                   a.x*b.z - a.z*b.x,
		   a.x*b.y - a.y*b.x);
}


inline double norm(Vector3 v)
{
    return sqrt(normq(v));
}
inline double normq(Vector3 v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z;
}



// ##### RAY #####
Ray::Ray(Vector3 origin, Vector3 direction)
    : origin(origin), direction(direction)
{
}

inline Ray Ray::operator-() const
{
    return Ray(origin, -direction);
}

inline bool Ray::intersects(const Sphere sphere) const
{
    return sphere.intersects(*this);
}

// ##### SPHERE #####
Sphere::Sphere(Vector3 origin, double radius)
    : origin(origin), radius(radius)
{
}

bool Sphere::intersects(const Ray ray) const
{
    Vector3 newcenter = ray.origin - this->origin;
    double b = 2*sprod(ray.direction, newcenter);
    double det = b*b - 4 * 1 * (normq(newcenter) - (this->radius) * (this->radius));

    if (det < 0)
	return false;
    else if (det = 0)
	return true;
    else
    {
	double t1 = (-b-sqrt(det))/2;
	double t2 = (-b+sqrt(det))/2;
	return true;
	std::cout << t1 << std::endl;

	if (t1>0 && t2>0)
	    return true; // Intersection point corresponds to t1
	else if (t1<0 && t2>0)
	    return true; // Intersection point corresponds to t2
	else if (t1<0 && t2<0)
	    return false;
    }
}


// ##### CAMERA #####
Camera::Camera(Vector3 origin,
       double fov,
       unsigned int width,
       unsigned int height)
    : origin(origin), fov(fov), image_width(width), image_height(height)
{
}

void Camera::render(std::string filename) const
{
    Image img(image_width, image_height);

    for(unsigned int i=0; i<image_width; i++)
    {
	for(unsigned int j=0; j<image_height; j++)
	{
	    if(scene->intersects(ray_to(i,j)))
		img.setPixel(Green, i, j, 255);
	    else
		img.setPixel(Green, i, j, 0);
		
	}
    }

    img.save(filename);
}


inline Ray Camera::ray_to(unsigned int i, unsigned int j) const
{
    return Ray(origin, Vector3(j-image_width/2.+0.5,
			       i-image_height/2.+0.5,
			       - (image_height/(2.*tan(fov/2.))) ).normalized());
}

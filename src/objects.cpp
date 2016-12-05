#include "../include/objects.h"
#include "../include/image.h"

#include <cmath>

// ##### VECTOR3 #####

Vector3::Vector3(double x, double y, double z, bool exists)
    : x(x), y(y), z(z), exists(exists)
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

inline Vector3 Ray::intersects(const Sphere sphere) const
{
    return sphere.intersects(*this);
}

// ##### SPHERE #####
Sphere::Sphere(Vector3 origin, double radius)
    : origin(origin), radius(radius)
{
}

Vector3 Sphere::intersects(const Ray ray) const
{
    Vector3 newcenter = ray.origin - this->origin;
    double b = 2*sprod(ray.direction, newcenter);
    double det = b*b - 4 * 1 * (normq(newcenter) - (this->radius) * (this->radius));

    Vector3 no_intersection;
    no_intersection.exists = false;
    double t = 0;

    if (det < 0)
	return no_intersection;
    else if (det = 0)
    {
	t = -b/2;
	return ray.origin + t*ray.direction;
    }
    else
    {
	double t1 = (-b-sqrt(det))/2;
	double t2 = (-b+sqrt(det))/2;

	if (t1>0 && t2>0)
	    t = t1; // Intersection point corresponds to t1
	else if (t1<0 && t2>0)
	    t = t2; // Intersection point corresponds to t2
	else if (t1<0 && t2<0)
	    return no_intersection;
	
	return ray.origin + t*ray.direction;
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
using namespace std;
void Camera::render(std::string filename) const
{
    Image img(image_width, image_height);

    for(unsigned int i=0; i<image_width; i++)
    {
	for(unsigned int j=0; j<image_height; j++)
	{
	    Vector3 inter = scene->intersects(ray_to(i,j));
	    
	    if(!inter.exists)
		img.setPixel(Red|Green|Blue, i, j, 0);
	    else // Now, the intersection exists
	    {
		Sphere sphere = *scene;
		
		Vector3 l = (light->origin - inter).normalized(); // Vector from intersection point to light
		Vector3 n = (inter - sphere.origin).normalized(); // Normal vector to the sphere at the intersection point
		double prod = sprod(l, n);
		    
		double d = normq(inter - light->origin); // Distance^2 fo the point to the light
		
		double value = prod * light->intensity / d;
		cout << value << endl;
		if(value > 255)
		    value = 255;
		else if(value < 0)
		    value = 0;
		
		img.setPixel(Red|Green|Blue, i, j, value);
	    }
		
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

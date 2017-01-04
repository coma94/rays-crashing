#include "../include/objects.h"
#include "../include/image.h"

#include <cmath>
#include <limits.h>
using namespace std; // temp

// Random numbers
std::default_random_engine engine;
std::uniform_real_distribution <double> distrib(0,1);



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


inline bool operator==(Vector3 const& a, Vector3 const& b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

inline bool operator!=(Vector3 const& a, Vector3 const& b)
{
    return !(a==b);
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

inline double Ray::intersects(const Sphere sphere) const
{
    return sphere.intersects(*this);
}

// ##### SPHERE #####
Sphere::Sphere(Vector3 origin, double radius)
    : origin(origin), radius(radius)
{
    material.diffuse = Vector3(180, 180, 180);
}

double Sphere::intersects(const Ray ray) const
{
    Vector3 newcenter = ray.origin - this->origin;
    double b = 2*sprod(ray.direction, newcenter);
    double det = b*b - 4 * 1 * (normq(newcenter) - (this->radius) * (this->radius));

    double no_intersection = std::numeric_limits<double>::quiet_NaN();

    if (det < 0)
	return no_intersection;
    else if (det == 0)
    {
	return -b/2;
    }
    else
    {
	double t1 = (-b-sqrt(det))/2;
	double t2 = (-b+sqrt(det))/2;
	
	if (t1>0 && t2>0)
	   return t1; // Intersection point corresponds to t1
	else if (t1<0 && t2>0)
	    return t2; // Intersection point corresponds to t2
	else if (t1<0 && t2<0)
	    return no_intersection;
    }
}



// ##### SCENE #####
Scene::Scene(std::list<Sphere> objects, Light light)
    : objects(objects), light(light)
{
}

Vector3 Scene::value(const Ray ray,
		     bool camera_ray,
		     unsigned int n_rays,
		     const unsigned int rem_reflexions,
		     const unsigned int indirect_reflexions) const
{
    double min_t = std::numeric_limits<double>::quiet_NaN();
    Sphere min_s = Sphere();
    
    for(const Sphere& s : objects)
    {
	double t = s.intersects(ray);

	if(std::isnan(t))
	    continue;
	else if(std::isnan(min_t))
	{
	    min_t = t;
	    min_s = s;
	}
	else if(t < min_t)
	{
	    min_t = t;
	    min_s = s;
	}
    }

    // Now we have the closest interection point and the corresponding sphere

    if(std::isnan(min_t))
	return Vector3(10,10,10);
    else
    {
	Vector3 inter = ray.origin + min_t * ray.direction;
		
	Vector3 l = (light.origin - inter).normalized(); // Vector from intersection point to light
	Vector3 n = (inter - min_s.origin).normalized(); // Normal vector to the sphere at the intersection point
	double prod = sprod(l, n);
		    
	double d = normq(inter - light.origin); // Distance^2 fo the point to the light

	
	// Shadows
	// Launch a ray from intersection to light
	Ray to_light = Ray(inter+_epsilon_*n, l);
	double min_t = std::numeric_limits<double>::quiet_NaN();
	for(const Sphere& s : objects)
	{
	    double t = s.intersects(to_light);

	    if(std::isnan(t))
		continue; // No intersection: ignore t
	    else if(std::isnan(min_t)) // intersection
	    {
		min_t = t;
	    }
	    else if(t < min_t)
	    {
		min_t = t;
	    }
	}

	double value_intensity;
	// If intersection is < than d : object hides the light
	if(std::isnan(min_t))
	    value_intensity = prod * light.intensity / d;
	else if(min_t*min_t < d)
	    value_intensity = 0;
	else
	    value_intensity = prod * light.intensity / d;

	Vector3 ret = min_s.material.diffuse * value_intensity;
	
	
	// If Specular not null, we compute recursively
	if(min_s.material.specular.x != Vector3())
	{
	    if(rem_reflexions > 0) // If we can still do reflexions
	    {
		Vector3 i = ray.direction.normalized();
		Ray reflected = Ray(inter+_epsilon_*n, i - 2*sprod(i,n) * n);

		Vector3 spec = value(reflected, false, n_rays, rem_reflexions-1, indirect_reflexions);

		//cout << spec << endl;
		
		ret = ret + Vector3(min_s.material.specular.x/255. * spec.x,
				    min_s.material.specular.y/255. * spec.y,
				    min_s.material.specular.z/255. * spec.z);
	    }
	}
	
        /*
	// If Opacity lower than 1, compute transparency
	if(min_s.material.opacity < 1)
	{
	    if(rem_reflexions > 0) // If we can still do reflexions
	    {
		Vector3 i = ray.direction.normalized();

		double nsphere = min_s.material.refraction_index;
		double in = sprod(i,n);
		
		double tosqrt = 1 - (1./(nsphere*nsphere)*(1-in*in));
		Ray refracted = Ray(inter+_epsilon_*n,
		                    1./nsphere * i - (1./nsphere * in + sqrt(tosqrt)) * n );

		Vector3 transp = value(refracted, rem_reflexions-1);

		//cout << transp << endl;
		
		ret = ret + Vector3(min_s.material.opacity * transp.x,
				    min_s.material.opacity * transp.y,
				    min_s.material.opacity * transp.z);
	    }
	}
	*/


	// Indirect lights
	if(indirect_reflexions > 0 && n_rays > 0) // If we can still do ind. light reflexions
	{
	    double number_rays;
	    if(camera_ray)
		number_rays = n_rays;
	    else
		number_rays = 1;

	    Vector3 spec;
	    for(unsigned int count=0; count<number_rays; count++)
	    {
		Vector3 i = ray.direction.normalized();
		Vector3 z = n;
		// Here we find the two other axis of the basis.
		// First, find any vecot of the normal plane. Say it has z=0, y=1, x=-b/a
		Vector3 x = Vector3(-n.y/n.x, 1, 0);
		// We normalize it
		x = x.normalized();
		// then we find y with vectorial product
		Vector3 y = vprod(-x, z);

		// We find the direction of the random ray
		double r1 = distrib(engine);
		double r2 = distrib(engine);
	    
		Vector3 direction = cos(2*M_PI*r1)*sqrt(1-r2)*x +
		    sin(2*M_PI*r1)*sqrt(1-r2)*y +
		    sqrt(r2)*z;

	    
		Ray reflected = Ray(inter+_epsilon_*n, direction.normalized());

		spec = spec + value(reflected, false, n_rays, rem_reflexions, indirect_reflexions-1);
	    }

	    spec = spec / number_rays;

	    
	    double coeff = 0.9;
	    ret =  ret + Vector3(coeff * spec.x / M_PI,
				 coeff * spec.y / M_PI,
				 coeff * spec.z / M_PI);
	}
	
		
	if(ret.x > 255)
	    ret.x = 255;
	else if(ret.x < 0)
	    ret.x = 0;
	if(ret.y > 255)
	    ret.y = 255;
	else if(ret.y < 0)
	    ret.y = 0;
	if(ret.z > 255)
	    ret.z = 255;
	else if(ret.z < 0)
	    ret.z = 0;

	return ret;
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

/* Gamma correction */
inline double gamma(const double x)
{
    return pow(x, 1./2.2) * 20.542735776768;
}


void Camera::render(std::string filename, unsigned int n_rays) const
{
    Image img(image_width, image_height);

    #pragma omp parallel for schedule(dynamic,1)
    for(unsigned int i=0; i<image_width; i++)
    {
	#pragma omp parallel for schedule(dynamic,1)
	for(unsigned int j=0; j<image_height; j++)
	{
	    Vector3 value = scene->value(ray_to(i,j), true, n_rays);
	    
	    img.setPixel(Red,   i, j, gamma(value.x));	
	    img.setPixel(Green, i, j, gamma(value.y));	
	    img.setPixel(Blue,  i, j, gamma(value.z));	
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

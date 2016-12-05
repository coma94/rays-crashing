#ifndef __H_OBJECTS__
#define __H_OBJECTS__

#include <iostream>
#include <string>

class Vector3
{
public:
    double x,y,z;
    bool exists; // Used for non-existing intersection points

    Vector3(double x=0, double y=0, double z=0, bool exists = true);

    Vector3 operator-() const;
    Vector3 normalized() const;

    friend std::ostream& operator<<(std::ostream& out, Vector3 const& a);
};

Vector3 operator+(Vector3 const& a, Vector3 const& b);
Vector3 operator-(Vector3 const& a, Vector3 const& b);
Vector3 operator*(double const& l, Vector3 const& a);
Vector3 operator*(Vector3 const& a, double const& l);
Vector3 operator/(Vector3 const& a, double const& l);

double sprod(Vector3 const& a, Vector3 const& b);
Vector3 vprod(Vector3 const& a, Vector3 const& b);
double norm(Vector3 v); 
double normq(Vector3 v);



class Sphere;

class Ray
{
public:
    Vector3 origin;
    Vector3 direction;

    Ray(Vector3 origin=Vector3(0,0,0), Vector3 direction=Vector3(0,0,0));
    Ray operator-() const;

    /*
      Return true iff the sphere intersects the given sphere.
    */
    Vector3 intersects(const Sphere sphere) const;
};

class Sphere
{
public:
    Vector3 origin;
    double radius;

    Sphere(Vector3 origin=Vector3(0,0,0), double radius=1);

    /*
      Return true iff the sphere intersects the given ray.
    */
    Vector3 intersects(const Ray ray) const;
};


class Light
{
public:
    Vector3 origin;
    unsigned int intensity;
};

class Camera
{
public:
    Vector3 origin;
    double fov; // in radians
    unsigned int image_width, image_height;
    
    Sphere* scene; //temp
    Light* light;
    

    Camera(Vector3 origin=Vector3(0,0,0),
	   double fov=1.05,
	   unsigned int width=800,
	   unsigned int height=600);


    void render(std::string filename) const;

protected:
    /*
      Generate a ray of norm 1 going to pixel (i,j)
    */
    Ray ray_to(unsigned int i, unsigned int j) const;
};


#endif

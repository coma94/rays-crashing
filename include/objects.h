/*
    Copyright 2016, Etienne Moutot
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef __H_OBJECTS__
#define __H_OBJECTS__

#include <iostream>
#include <string>
#include <list>
#include <random>


#define _MAX_SPEC_REFLEXIONS 5
#define _MAX_INDIRECT_REFLEXIONS 5
#define _epsilon_ 0.000001


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

bool operator==(Vector3 const& a, double const& l);
bool operator!=(Vector3 const& a, double const& l);

double sprod(Vector3 const& a, Vector3 const& b);
Vector3 vprod(Vector3 const& a, Vector3 const& b);
double norm(Vector3 v); 
double normq(Vector3 v);



class Material
{
public:
    Vector3 diffuse;
    Vector3 specular;
    double opacity = 1.;
    double refraction_index = 1.;
};

class Sphere;

class Ray
{
public:
    Vector3 origin;
    Vector3 direction;

    Ray(Vector3 origin=Vector3(0,0,0), Vector3 direction=Vector3(0,0,0));
    Ray operator-() const;

    /*
      If the sphere intersects the ray, return the distance of the intersection to the origin of the ray.
      If not, return *nan*.
    */
    double intersects(const Sphere sphere) const;
};

class Sphere
{
public:
    Vector3 origin;
    double radius;
    Material material; // shared with all objects

    Sphere(Vector3 origin=Vector3(0,0,0), double radius=1);

    /*
      If the sphere intersects the ray, return the distance of the intersection to the origin of the ray.
      If not, return *nan*.
    */
    double intersects(const Ray ray) const;
};


class Light
{
public:
    Vector3 origin;
    unsigned int intensity;
};



class Scene
{
public:
    std::list<Sphere> objects;
    Light light;

    Scene(std::list<Sphere> objects = std::list<Sphere>(), Light light = Light());

    /*
      Returns the RGB value of the intersection point of the ray and the scene. 
    */
    Vector3 value(const Ray ray,
		  bool camera_ray = false,
		  unsigned int n_rays = 0,
		  const unsigned int rem_reflexions = _MAX_SPEC_REFLEXIONS,
		  const unsigned int indirect_reflexions = _MAX_INDIRECT_REFLEXIONS) const;
};



class Camera
{
public:
    Vector3 origin;
    double fov; // in radians
    unsigned int image_width, image_height;
    
    Scene* scene;
    

    Camera(Vector3 origin=Vector3(0,0,0),
	   double fov=1.05,
	   unsigned int width=800,
	   unsigned int height=600);


    void render(std::string filename, unsigned int n_rays = 0) const;

protected:
    /*
      Generate a ray of norm 1 going to pixel (i,j)
    */
    Ray ray_to(unsigned int i, unsigned int j) const;
};


#endif

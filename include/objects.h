#ifndef __H_OBJECTS__
#define __H_OBJECTS__

#include <iostream>

class Vector3
{
public:
    double x,y,z;

    Vector3(double x=0, double y=0, double z=0);

    Vector3 operator-() const;

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


#endif

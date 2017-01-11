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

#include <iostream>
using namespace std;

#include "../include/image.h"
#include "../include/objects.h"


int main(int argc, char *argv[])
{
    cout << "Creating camera & sphere & light...";

    Sphere s1 = Sphere(Vector3(0,0,0), 4);        // specular
    s1.material.diffuse = Vector3(0, 0, 0);
    s1.material.specular = Vector3(255, 255, 255);
    Sphere s4 = Sphere(Vector3(5,-5,3), 3);//purple1
    s4.material.diffuse = Vector3(0, 0, 0);
    s4.material.specular = Vector3(255, 255, 255);
    
    Sphere s2 = Sphere(Vector3(0,8,0), 4);//white // non specular
    s2.material.diffuse = Vector3(220, 220, 220);
    Sphere s5 = Sphere(Vector3(-5,-2,10), 3);//purple2
    s5.material.diffuse = Vector3(0, 50, 220);
    s5.material.opacity = 0;
    s5.material.refraction_index = 1.2;
    
    Sphere s6 = Sphere(Vector3(-6,4,10), 3);//purple3
    s6.material.diffuse = Vector3(180, 100, 220);

    Sphere S1 = Sphere(Vector3(-60,0,-15), 60);   // Big spheres
    S1.material.diffuse = Vector3(10, 220, 30);
    Sphere S2 = Sphere(Vector3(-20,-15,-60), 60); 
    S2.material.diffuse = Vector3(100, 20, 10);

    Scene scene; // Create the scene and add objects in it
    scene.objects.push_back(s1);
    scene.objects.push_back(s2);
    scene.objects.push_back(s4);
    scene.objects.push_back(s5);
    scene.objects.push_back(s6);
    
    scene.objects.push_back(S1);
    scene.objects.push_back(S2);
    
    scene.light.origin = Vector3(10, 10, 10);
    scene.light.intensity = 600;
    
	
    Camera cam = Camera(Vector3(0,0,20), 1.05, 1000, 1000);
    cam.scene = &scene;

    cout << "[ok]" << endl;
    cout << "Rendering scene...\n";
    
    cam.render("bla.png", 500);

    cout << "[ok]" << endl;
    
    return 0;
}

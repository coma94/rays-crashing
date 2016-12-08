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

    Sphere s1 = Sphere(Vector3(0,0,0), 4);
    s1.material.diffuse = Vector3(200, 0, 0);
    Sphere s2 = Sphere(Vector3(0,6,0), 4);
    s2.material.diffuse = Vector3(0, 200, 0);
    Sphere s3 = Sphere(Vector3(-4,4,2), 2);
    s3.material.diffuse = Vector3(0, 0, 200);

    
    Scene scene;
    scene.objects.push_back(s1);
    scene.objects.push_back(s2);
    scene.objects.push_back(s3);
    
    scene.light.origin = Vector3(5, 5, 15);
    scene.light.intensity = 200;
    
	
    Camera cam = Camera(Vector3(0,0,20), 1.05, 400, 400);
    cam.scene = &scene;

    cout << "[ok]" << endl;
    cout << "Rendering scene...\n";

    cam.render("bla.png");

    cout << "[ok]" << endl;
    
    return 0;
}

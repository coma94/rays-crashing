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

    Sphere scene = Sphere(Vector3(0,0,0), 4);
    Light light;
    light.origin = Vector3(5, 5, 10);
    light.intensity = 5000;
	
    Camera cam = Camera(Vector3(0,0,10), 1.05, 100, 100);
    cam.scene = &scene;
    cam.light = &light;

    cout << "[ok]" << endl;
    cout << "Rendering scene...\n";

    cam.render("bla.png");

    cout << "[ok]" << endl;
    
    return 0;
}

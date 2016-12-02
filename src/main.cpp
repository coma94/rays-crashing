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
    cout << "Creating image" << endl;

    Image img(50,50);
    img.setPixel(Red, 25, 25, 255);
    img.setPixel(Blue, 1, 1, 255);
    // img.setPixel(Green, 48, 1, 255);

    img.save("test.png");
    
    return 0;
}

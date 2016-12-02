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

    cout << "Vector tests" << endl;
    Vector3 a = Vector3(1,1,1);
    Vector3 b = Vector3(1,1,0);

    cout << "a:" <<a << endl << "b:" << b << endl << endl;
    
    cout << "a+b " << a+b << endl;
    cout << "a-b " << a-b << endl;
    cout << "-a "  << -a  << endl;
    cout << "2*a " << 2*a << endl;
    cout << "a*2 " << a*2 << endl;
    cout << "a/2 " << a/2 << endl;
    cout << "a.b " << sprod(a,b) << endl;
    cout << "a^b " << vprod(a,b) << endl;
    cout << "||a|| " << norm(a) << endl;
    cout << "||a||^2 " << normq(a) << endl;
    cout << "||b|| " << norm(b) << endl;
    
    return 0;
}

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

#ifndef __H_IMAGE__
#define __H_IMAGE__

#include <string>
using namespace std;

#include "CImg.h"
using namespace cimg_library;

enum Layer
{
    Red = 1,
    Green = 2,
    Blue = 4
};

inline Layer operator|(Layer a, Layer b)
{return static_cast<Layer>(static_cast<int>(a) | static_cast<int>(b));}

inline Layer operator&(Layer a, Layer b)
{return static_cast<Layer>(static_cast<int>(a) & static_cast<int>(b));}

enum Filetype { png, jpeg, bmp, tiff };


/*
  Coordinates:
  
  y (height)
  ^
  |
  |
  |
  |
  0 --------> x (width)

 */


class Image
{
public:
    Image(unsigned int width, unsigned int height);
    
    void setPixel(Layer layer, int x, int y, unsigned char value);
    unsigned char getPixel(Layer layer, int x, int y) const;
    void save(string filename, Filetype ftype = png) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

protected:
    unsigned char* m_pixels;

    unsigned int m_width;
    unsigned int m_height;
};

#endif

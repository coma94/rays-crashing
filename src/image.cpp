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

#include "../include/image.h"

Image::Image(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
    
    m_pixels = (unsigned char *)malloc(3 * width * height * sizeof(unsigned char));
}


void Image::setPixel(Layer layer, int x, int y, unsigned char value)
{
    if(layer & Red)
        m_pixels[((m_height-y-1)*m_width+x)] = value;
    if(layer & Green)
        m_pixels[((m_height-y-1)*m_width+x) + m_width*m_height] = value;
    if(layer & Blue)
        m_pixels[((m_height-y-1)*m_width+x) + 2*m_width*m_height] = value;
}
#include <iostream>
unsigned char Image::getPixel(Layer layer, int x, int y) const
{
    unsigned char value = 0;
    unsigned int number = 0;
    if(layer & Red)
    {
        value += m_pixels[((m_height-y-1)*m_width+x)];
	number++;
    }
    if(layer & Green)
    {
        value += m_pixels[((m_height-y-1)*m_width+x) + m_width*m_height];
	number++;
    }
    if(layer & Blue)
    {
        value += m_pixels[((m_height-y-1)*m_width+x) + 2*m_width*m_height];
	number++;
    }
    
    return value/number;
}

void Image::save(string filename, Filetype ftype) const
{
    CImg<unsigned char> cimg(&m_pixels[0], m_width, m_height, 1, 3);

    if(ftype == png)
        cimg.save_png(filename.c_str());
    else if(ftype == jpeg)
        cimg.save_jpeg(filename.c_str());
    else if(ftype == bmp)
        cimg.save_bmp(filename.c_str());
    else if(ftype == tiff)
        cimg.save_tiff(filename.c_str());
}

unsigned int Image::getWidth() const
{
    return m_width;
}

unsigned int Image::getHeight() const
{
    return m_height;
}

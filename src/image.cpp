#include "../include/image.h"

Image::Image(int width, int height)
{
    m_width = width;
    m_height = height;
    
    m_pixels = (unsigned char *)malloc(3 * width * height * sizeof(unsigned char));
}


void Image::setPixel(Layer layer, int x, int y, unsigned char value)
{
    if(layer == Red)
        m_pixels[((m_height-y-1)*m_width+x)] = value;
    else if(layer == Green)
        m_pixels[((m_height-y-1)*m_width+x) + m_width*m_height] = value;
    else if(layer == Blue)
        m_pixels[((m_height-y-1)*m_width+x) + 2*m_width*m_height] = value;
}

unsigned char Image::getPixel(Layer layer, int x, int y) const
{
    if(layer == Red)
        return m_pixels[((m_height-y-1)*m_width+x)];
    else if(layer == Green)
        return m_pixels[((m_height-y-1)*m_width+x) + m_width*m_height];
    else if(layer == Blue)
        return m_pixels[((m_height-y-1)*m_width+x) + 2*m_width+m_height];
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

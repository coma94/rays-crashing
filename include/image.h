#ifndef __H_IMAGE__
#define __H_IMAGE__

#include <string>
using namespace std;

#include "CImg.h"
using namespace cimg_library;

enum Layer { Red, Green, Blue };
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

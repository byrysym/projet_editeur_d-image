#pragma once
#include "Image.h"
class Image;

namespace processing
{
    void converTogrey(Image& image);
    void convertToBinary(Image& image, const uint8& threshold = 122);
    void fill(Image& image, const Rgb& fillColor);
    void zoom(Image& image, float zoomFactor, const Rgb& fillColor);
    void zoom(Image& image, float zoomFactor, const Point& origin, const Rgb& fillColor);
    void rotation(Image& image, float angleInDegree, const Point& center, const Rgb& fillColor);
    void rotation(Image& image, float angleInDegree, const Rgb& fillColor);
    void stretchHistogram(Image& image);
}
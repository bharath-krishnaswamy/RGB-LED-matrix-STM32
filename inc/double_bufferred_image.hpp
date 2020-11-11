#pragma once

#include "image.hpp"
#include <array>

template <size_t X, size_t Y, typename Pixel, size_t N>
class double_bufferred_image {

    std::array<image<X, Y, Pixel, N>, 2> images;
    image<X, Y, Pixel, N>*               img;
    image<X, Y, Pixel, N>*               disp_img;

  public:
    double_bufferred_image()
        : images(), img(&images[0]), disp_img(&images[1]) {}

    image<X, Y, Pixel, N>& draw_image() { return *img; }

    const image<X, Y, Pixel, N>& display_image() { return *disp_img; }

    void swap() { std::swap(img, disp_img); }
};

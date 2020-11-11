#pragma once

#include "image_bit_slice.hpp"
#include "pixel.hpp"
#include <array>

template <size_t X, size_t Y, typename Pixel, size_t N> class image {

    std::array<image_bit_slice<X, Y, N>, Pixel::color_depth> bit_slices;

  public:
    void set_pixel(uint8_t x, uint8_t y, Pixel p) {
        for (unsigned int i = 0; i < bit_slices.size(); i++) {
            auto& bit_slice = bit_slices[i];

            uint8_t bit_offset = bit_slice.y_bit_offset(y);
            auto    data       = bit_slice.line(y).data[x];

            uint8_t bits = p.rgb_bits(i);
            data &= 0x07 << bit_offset;
            data |= bits << bit_offset;
            bit_slice.line(y).data[x] = data;
        }
    }

    void clear() { memset(this, 0, sizeof(*this)); }

    image_bit_slice<X, Y, N>& slice(uint8_t bit) { return bit_slices[bit]; }
};

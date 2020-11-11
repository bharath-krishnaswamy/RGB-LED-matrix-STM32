#pragma once

#include "image_bit_scan_line.hpp"
#include "pixel.hpp"
#include <array>

template <size_t X, size_t Y, size_t N, size_t Scan = Y / (2 * N),
          class = typename std::enable_if<Scan == 8 || Scan == 16 ||
                                          Scan == 32>::type>
struct image_bit_slice {

    std::array<image_bit_scan_line<X, N>, Scan> scan_lines;

    image_bit_scan_line<X, N>& line(uint8_t y) { return scan_lines[y % Scan]; }

    const image_bit_scan_line<X, N>& line(uint8_t y) const {
        return scan_lines[y % Scan];
    }

    /**
     * Calculate the bit offset needed to access y-th row of Scan_line.data
     * (0*Scan..1*Scan-1) -> 0
     * (1*Scan..2*Scan-1) -> 3
     * (2*Scan..3*Scan-1) -> 6  <-- applicable only if N==2
     * (3*Scan..4*Scan-1) -> 9  <-- applicable only if N==2
     */
    constexpr uint8_t y_bit_offset(uint8_t y) { return 3 * (y / Scan); }
};

#pragma once

#include <array>
#include <type_traits>

template <size_t X, size_t N,
          class = typename std::enable_if<N == 1 || N == 2>::type>
struct image_bit_scan_line {

    using T = typename std::conditional<N == 1, uint8_t, uint16_t>::type;

    std::array<T, X> data;
};

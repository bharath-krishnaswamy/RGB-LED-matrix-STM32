#pragma once

#include <cstdint>

template <size_t Depth> struct pixel {

    using Dummy = typename std::enable_if<Depth == 4 || Depth == 5>::type;

    static constexpr uint8_t color_depth = Depth;

    uint16_t data;

    static constexpr pixel from(uint8_t r, uint8_t g, uint8_t b) {
        constexpr uint8_t mask = (1 << Depth) - 1;
        r >>= 8 - Depth;
        g >>= 8 - Depth;
        b >>= 8 - Depth;
        return {(r & mask) | (g & mask) << Depth | (b & mask) << 2 * Depth};
    }

    /**
     * Get a "bit slice" of the pixel
     * Extracts a given bit from each color channel and squishes them together
     * into a uint8_t with format 0b0000 0BGR
     */
    constexpr uint8_t rgb_bits(uint8_t bit) {
        const uint8_t mask = 1 << bit;
        return ((data >> (0 + bit)) & 1) | ((data >> (Depth + bit)) & 1) << 1 |
               ((data >> (2 * Depth + bit)) & 1) << 2;
    }
};

template <> struct pixel<3> {
    static constexpr uint8_t color_depth = 3;

    uint8_t data;

    static constexpr pixel<3> from(uint8_t r, uint8_t g, uint8_t b) {
        return {(r & 0xE0) | ((g >> 3) & 0x1C) | ((b >> 6) & 0x03)};
    }

    constexpr uint8_t rgb_bits(uint8_t bit) {
        return ((data >> (5 + bit)) & 1) | ((data >> (1 + bit)) & 2) |
               (bit == 0 ? 0 : ((data << (3 - bit)) & 4));
    }
};

static_assert(sizeof(pixel<3>) == 1);
static_assert(pixel<3>::from(0, 0, 0).data == 0);
static_assert(pixel<3>::from(0xFF, 0, 0).data == 0xE0);
static_assert(pixel<3>::from(0, 0xFF, 0).data == 0x1C);
static_assert(pixel<3>::from(0, 0, 0xFF).data == 0x03);

static_assert(pixel<3>::from(0, 0, 0).rgb_bits(0) == 0);
static_assert(pixel<3>::from(0, 0, 0).rgb_bits(1) == 0);
static_assert(pixel<3>::from(0, 0, 0).rgb_bits(2) == 0);

static_assert(pixel<3>::from(0x80, 0x80, 0x80).rgb_bits(0) == 0);
static_assert(pixel<3>::from(0x80, 0x80, 0x80).rgb_bits(1) == 0);
static_assert(pixel<3>::from(0x80, 0x80, 0x80).rgb_bits(2) == 7);

static_assert(pixel<3>::from(0xA0, 0xA0, 0xA0).rgb_bits(0) ==
              3); // Blue bit is zero because it is not stored
static_assert(pixel<3>::from(0xA0, 0xA0, 0xA0).rgb_bits(1) == 0);
static_assert(pixel<3>::from(0xA0, 0xA0, 0xA0).rgb_bits(2) == 7);

static_assert(pixel<3>::from(0xFF, 0xFF, 0xFF).rgb_bits(0) ==
              3); // Blue bit is zero because it is not stored
static_assert(pixel<3>::from(0xFF, 0xFF, 0xFF).rgb_bits(1) == 7);
static_assert(pixel<3>::from(0xFF, 0xFF, 0xFF).rgb_bits(2) == 7);

static_assert(sizeof(pixel<4>) == 2);
static_assert(pixel<4>::from(0, 0, 0).data == 0);
static_assert(pixel<4>::from(0xFF, 0, 0).data == 0x000F);
static_assert(pixel<4>::from(0, 0xFF, 0).data == 0x00F0);
static_assert(pixel<4>::from(0, 0, 0xFF).data == 0x0F00);

static_assert(pixel<4>::from(0, 0, 0).rgb_bits(0) == 0);
static_assert(pixel<4>::from(0, 0, 0).rgb_bits(1) == 0);
static_assert(pixel<4>::from(0, 0, 0).rgb_bits(2) == 0);
static_assert(pixel<4>::from(0, 0, 0).rgb_bits(3) == 0);

static_assert(pixel<4>::from(0x80, 0x80, 0x80).rgb_bits(0) == 0);
static_assert(pixel<4>::from(0x80, 0x80, 0x80).rgb_bits(1) == 0);
static_assert(pixel<4>::from(0x80, 0x80, 0x80).rgb_bits(2) == 0);
static_assert(pixel<4>::from(0x80, 0x80, 0x80).rgb_bits(3) == 7);

static_assert(pixel<4>::from(0xA0, 0xA0, 0xA0).rgb_bits(0) == 0);
static_assert(pixel<4>::from(0xA0, 0xA0, 0xA0).rgb_bits(1) == 7);
static_assert(pixel<4>::from(0xA0, 0xA0, 0xA0).rgb_bits(2) == 0);
static_assert(pixel<4>::from(0xA0, 0xA0, 0xA0).rgb_bits(3) == 7);

static_assert(pixel<4>::from(0xFF, 0xFF, 0xFF).rgb_bits(0) == 7);
static_assert(pixel<4>::from(0xFF, 0xFF, 0xFF).rgb_bits(1) == 7);
static_assert(pixel<4>::from(0xFF, 0xFF, 0xFF).rgb_bits(2) == 7);
static_assert(pixel<4>::from(0xFF, 0xFF, 0xFF).rgb_bits(3) == 7);

static_assert(sizeof(pixel<5>) == 2);
static_assert(pixel<5>::from(0, 0, 0).data == 0);
static_assert(pixel<5>::from(0xFF, 0, 0).data == 0x001F);
static_assert(pixel<5>::from(0, 0xFF, 0).data == 0x03E0);
static_assert(pixel<5>::from(0, 0, 0xFF).data == 0x7C00);

static_assert(pixel<5>::from(0, 0, 0).rgb_bits(0) == 0);
static_assert(pixel<5>::from(0, 0, 0).rgb_bits(1) == 0);
static_assert(pixel<5>::from(0, 0, 0).rgb_bits(2) == 0);
static_assert(pixel<5>::from(0, 0, 0).rgb_bits(3) == 0);
static_assert(pixel<5>::from(0, 0, 0).rgb_bits(4) == 0);

static_assert(pixel<5>::from(0x80, 0x80, 0x80).rgb_bits(0) == 0);
static_assert(pixel<5>::from(0x80, 0x80, 0x80).rgb_bits(1) == 0);
static_assert(pixel<5>::from(0x80, 0x80, 0x80).rgb_bits(2) == 0);
static_assert(pixel<5>::from(0x80, 0x80, 0x80).rgb_bits(3) == 0);
static_assert(pixel<5>::from(0x80, 0x80, 0x80).rgb_bits(4) == 7);

static_assert(pixel<5>::from(0xA0, 0xA0, 0xA0).rgb_bits(0) == 0);
static_assert(pixel<5>::from(0xA0, 0xA0, 0xA0).rgb_bits(1) == 0);
static_assert(pixel<5>::from(0xA0, 0xA0, 0xA0).rgb_bits(2) == 7);
static_assert(pixel<5>::from(0xA0, 0xA0, 0xA0).rgb_bits(3) == 0);
static_assert(pixel<5>::from(0xA0, 0xA0, 0xA0).rgb_bits(4) == 7);

static_assert(pixel<5>::from(0xFF, 0xFF, 0xFF).rgb_bits(0) == 7);
static_assert(pixel<5>::from(0xFF, 0xFF, 0xFF).rgb_bits(1) == 7);
static_assert(pixel<5>::from(0xFF, 0xFF, 0xFF).rgb_bits(2) == 7);
static_assert(pixel<5>::from(0xFF, 0xFF, 0xFF).rgb_bits(3) == 7);
static_assert(pixel<5>::from(0xFF, 0xFF, 0xFF).rgb_bits(4) == 7);

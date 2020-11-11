#pragma once

#include "double_bufferred_image.hpp"
#include "gpio.hpp"
#include "image.hpp"
#include "timer.hpp"

#define MICROS_BASE 100

template <size_t X, size_t Y, size_t N, size_t M, typename Pixel> class hub75 {

    double_bufferred_image<M * X, N * Y, Pixel, N> db_image;
    uint8_t                                        current_bit;
    timer                                          t;
    gpio                                           io;

  public:
    hub75(timer t, gpio io) : db_image(), current_bit(0), t(t), io(io) {}

    image<M * X, N * Y, Pixel, N>& draw_image() {
        return db_image.draw_image();
    }

    void swap() { db_image.swap(); }

    void start() { t.start_once(MICROS_BASE * (1 << current_bit)); }

    void interrupt_handler() {
        auto image = db_image.display_image();
        auto slice = image.slice(current_bit);

        io.send(slice);

        current_bit = (current_bit + 1) % 4;
        start();
    }
};

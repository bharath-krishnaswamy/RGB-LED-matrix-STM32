#pragma once

#include "image_bit_slice.hpp"
#include "stm32f4xx_hal.h"

class gpio {

    GPIO_TypeDef* port;

  public:
    gpio(GPIO_TypeDef* port) : port(port) {}

    template <size_t X, size_t Y, size_t N>
    void send(const image_bit_slice<X, Y, N>& slice) {
        // output_enable(true);
        // for (int line = 0; line < Y/2; line++){
        //     auto scan_line = slice.line(line);
        //
        //     row_select(line);
        //     for(uint8_t d : scan_line.data) {
        //         data(d);
        //         clock(true);
        //         clock(false);
        //     }
        //     latch(true);
        //     latch(false);
        // }
    }
};

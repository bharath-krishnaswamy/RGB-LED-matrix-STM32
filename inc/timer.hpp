#pragma once

#include "stm32f4xx_hal.h"
#include <cstdint>

class timer {

    TIM_HandleTypeDef& tim;

  public:
    timer(TIM_HandleTypeDef& tim) : tim(tim) {}

    void start_once(uint16_t us) {
        tim.Init.Period = us;
        HAL_TIM_Base_Init(&tim);
        HAL_TIM_Base_Start_IT(&tim);
    }

    void stop() { HAL_TIM_Base_Stop_IT(&tim); }
};

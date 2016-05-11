cmake_minimum_required(VERSION 3.4)
project(arm_ethernetboard)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -std=c++11 -nostartfiles")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -O0 -g -nostartfiles")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp")

set(CHIBIOS deps/ChibiOS_16.1.2)

include_directories(
        ${CHIBIOS}/os/ext/CMSIS/include
        ${CHIBIOS}/os/ext/CMSIS/ST/STM32F1xx
)

include(cmakefiles/startup.cmake)
include(cmakefiles/chibios.cmake)
#include(cmakefiles/lwip.cmake)
set(SOURCE_FILES ${SOURCE_FILES} deps/tinyprintf/tinyprintf.c)
include_directories(deps/tinyprintf)

enable_language(ASM)

add_definitions(-DSTM32F103xB)

include_directories(.)
include_directories(config/)
set(SOURCE_FILES ${SOURCE_FILES} main.c board/board.c debug.c lcd.c lcd.h board/board_btn.c board/board_btn.h test_hw.c test_hw.h board/board_adc.c board/board_adc.h median.c median.h board/board_uart.c board/board_uart.h dmx.c dmx.c dmx.h)
add_executable(dmx_controller ${SOURCE_FILES})


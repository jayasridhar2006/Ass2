cmake_minimum_required(VERSION 3.12)

# Set project name
project(tsl2561-library C CXX)

# Initialize Pico SDK
include(pico_sdk_import.cmake)

# Add executable
add_executable(tsl2561-example
    proximitysensor.c
)

# Link pico_stdlib
target_link_libraries(tsl2561-example pico_stdlib hardware_spi)

# Enable usb output, disable uart output
pico_enable_stdio_usb(tsl2561-example 1)
pico_enable_stdio_uart(tsl2561-example 0)

# Create map/bin/hex file
pico_add_extra_outputs(tsl2561-example)

#include "pico/stdlib.h"
#include "tsl2561.h"

int main() {
    stdio_init_all();

    // Initialize SPI and the TSL2561 sensor
    tsl2561_init(spi0, CS_PIN);

    // Power on the sensor
    tsl2561_power_on();

    while (1) {
        // Read light intensity (lux value)
        uint32_t lux = tsl2561_read_data();
        printf("Light Intensity (Lux): %u\n", lux);

        sleep_ms(1000);  // Wait for 1 second before the next reading
    }

    return 0;
}


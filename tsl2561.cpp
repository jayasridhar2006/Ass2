#include "tsl2561.h"

#define CS_PIN 17  // Chip Select Pin for SPI

// Initialize SPI for TSL2561
void tsl2561_init(spi_inst_t *spi, uint8_t cs_pin) {
    gpio_init(cs_pin);
    gpio_set_dir(cs_pin, GPIO_OUT);
    gpio_put(cs_pin, 1);  // Set CS high to deselect the device

    // Initialize SPI at a clock speed of 1 MHz (adjust as needed)
    spi_init(spi, 1000000); // 1 MHz SPI speed
}

// Power on the TSL2561 sensor
void tsl2561_power_on() {
    tsl2561_write_register(TSL2561_CONTROL_REG, TSL2561_POWER_ON);
}

// Power off the TSL2561 sensor
void tsl2561_power_off() {
    tsl2561_write_register(TSL2561_CONTROL_REG, TSL2561_POWER_OFF);
}

// Read the raw data from the TSL2561 sensor
uint32_t tsl2561_read_data() {
    uint8_t data[4];
    uint32_t lux = 0;
    
    // Read 4 bytes of data
    for (int i = 0; i < 4; i++) {
        data[i] = tsl2561_read_register(TSL2561_DATA_REG + i);
    }

    lux = (data[1] << 8) | data[0];  // Combine high and low bytes
    return lux;
}

// Read a specific register from the TSL2561
uint8_t tsl2561_read_register(uint8_t reg) {
    uint8_t data[1] = {0};

    gpio_put(CS_PIN, 0);  // Select the device
    spi_write_read_blocking(spi0, &reg, 1, data, 1);  // Send register address and read data
    gpio_put(CS_PIN, 1);  // Deselect the device

    return data[0];
}

// Write to a specific register of the TSL2561
void tsl2561_write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};

    gpio_put(CS_PIN, 0);  // Select the device
    spi_write_blocking(spi0, data, 2);  // Write register address and value
    gpio_put(CS_PIN, 1);  // Deselect the device
}

// Set timing for the TSL2561 (gain and integration time)
void tsl2561_set_timing(uint8_t timing) {
    tsl2561_write_register(TSL2561_TIMING_REG, timing);
}

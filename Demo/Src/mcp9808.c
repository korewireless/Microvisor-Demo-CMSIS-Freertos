#include "main.h"


extern      I2C_HandleTypeDef   i2c;


/**
    @brief  Check the device is connected and operational.
    @retval `true` if we can read values and they are right,
            otherwise `false`.
 */
bool MCP9808_init() {
    // Prep data storage buffers
    uint8_t mid_data[2] = {0};
    uint8_t did_data[2] = {0};

    // Read bytes from the sensor: MID...
    uint8_t cmd = MCP9808_REG_MANUF_ID;
    HAL_I2C_Master_Transmit(&i2c, MCP9808_I2CADDR_DEFAULT << 1, &cmd,      1, 100);
    HAL_I2C_Master_Receive(&i2c,  MCP9808_I2CADDR_DEFAULT << 1, mid_data, 2, 100);

    // ...DID
    cmd = MCP9808_REG_DEVICE_ID;
    HAL_I2C_Master_Transmit(&i2c, MCP9808_I2CADDR_DEFAULT << 1, &cmd,      1, 100);
    HAL_I2C_Master_Receive(&i2c,  MCP9808_I2CADDR_DEFAULT << 1, did_data, 2, 100);

    // Bytes to integers
    const uint16_t mid_value = (mid_data[0] << 8) | mid_data[1];
    const uint16_t did_value = (did_data[0] << 8) | did_data[1];
    printf("MID: 0x%04x\nDID: 0x%04x\n", mid_value, did_value);

    // Returns true if the device is initialized, false otherwise.
    return (mid_value == 0x0054 && did_value == 0x0400);
}


/**
    @brief  Check the device is connected and operational.
    @retval `true` if the sensor is correct, otherwise `false`.
 */
double MCP9808_read_temp() {
    // Read sensor and return its value in degrees celsius.
    uint8_t temp_data[2] = { 0 };
    uint8_t cmd = MCP9808_REG_AMBIENT_TEMP;
    HAL_I2C_Master_Transmit(&i2c, MCP9808_I2CADDR_DEFAULT << 1, &cmd,      1, 100);
    HAL_I2C_Master_Receive(&i2c,  MCP9808_I2CADDR_DEFAULT << 1, temp_data, 2, 100);

    // Scale and convert to signed value.
    const uint32_t temp_raw = (temp_data[0] << 8) | temp_data[1];
    double temp_cel = (temp_raw & 0x0FFF) / 16.0;
    if (temp_raw & 0x1000) temp_cel -= 256.0;
    return temp_cel;
}
#include "main.h"


extern      I2C_HandleTypeDef    i2c;
extern      uint8_t              display_buffer[17];


// The hex character set
char        CHARSET[19] = "\x3F\x06\x5B\x4F\x66\x6D\x7D\x07\x7F\x6F\x5F\x7C\x58\x5E\x7B\x71\x40\x63";

// Map display digits to bytes in the buffer
uint8_t     POS[4] = {0, 2, 6, 8};


/*
 * HT16K33 Functions
 */
void HT16K33_init() {
    HT16K33_write_cmd(0x21);     // System on
    HT16K33_write_cmd(0x81);     // Display on
    HT16K33_write_cmd(0xEF);     // Set brightness
    HT16K33_clear_buffer();
}


void HT16K33_write_cmd(uint8_t cmd) {
    HAL_I2C_Master_Transmit(&i2c, HT16K33_ADDR << 1, &cmd, 1, 100);
}


void HT16K33_clear_buffer() {
    for (uint8_t i = 0 ; i < 17 ; ++i) {
        display_buffer[i] = 0;
    }
}


void HT16K33_draw() {
    // Set up the buffer holding the data to be
    // transmitted to the LED
    uint8_t tx_buffer[17] = { 0 };
    memcpy(tx_buffer + 1, display_buffer, 16);

    // Display the buffer and flash the LED
    HAL_I2C_Master_Transmit(&i2c, HT16K33_ADDR << 1, tx_buffer, sizeof(tx_buffer), 100);
}


void HT16K33_show_value(int16_t value) {
    // Convert the value to BCD...
    uint32_t bcd_val = bcd(value);
    HT16K33_clear_buffer();
    HT16K33_set_number((bcd_val >> 12) & 0x0F, 0, false);
    HT16K33_set_number((bcd_val >> 8)  & 0x0F, 1, false);
    HT16K33_set_number((bcd_val >> 4)  & 0x0F, 2, false);
    HT16K33_set_number(bcd_val & 0x0F,         3, false);
    HT16K33_draw();
}


void HT16K33_set_number(uint32_t number, uint32_t digit, bool has_dot) {
    if (digit > 4) return;
    if (number > 9) return;
    HT16K33_set_alpha('0' + number, digit, has_dot);
}


void HT16K33_set_alpha(char chr, uint32_t digit, bool has_dot) {
    if (digit > 4) return;

    uint8_t char_val = 0xFF;
    if (chr >= 'a' && chr <= 'f') {
        char_val = (uint8_t)chr - 87;
    } else if (chr >= '0' && chr <= '9') {
        char_val = (uint8_t)chr - 48;
    }

    if (char_val == 0xFF) return;
    display_buffer[POS[digit]] = CHARSET[char_val];
    if (has_dot) display_buffer[POS[digit]] |= 0x80;
}


uint32_t bcd(uint32_t base) {
    if (base > 9999) base = 9999;
    for (uint32_t i = 0 ; i < 16 ; ++i) {
        base = base << 1;
        if (i == 15) break;
        if ((base & 0x000F0000) > 0x0004FFFF) base += 0x00030000;
        if ((base & 0x00F00000) > 0x004FFFFF) base += 0x00300000;
        if ((base & 0x0F000000) > 0x04FFFFFF) base += 0x03000000;
        if ((base & 0xF0000000) > 0x4FFFFFFF) base += 0x30000000;
    }

    return (base >> 16) & 0xFFFF;
}
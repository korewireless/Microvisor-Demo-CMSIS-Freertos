#ifndef _HT16K33_HEADER_
#define _HT16K33_HEADER_


/*
 * CONSTANTS
 */
#define     HT16K33_ADDR            0x70


/*
 * PROTOTYPES
 */
void HT16K33_init();
void HT16K33_write_cmd(uint8_t cmd);
void HT16K33_draw();
void HT16K33_clear_buffer();
void HT16K33_show_value(int16_t value);
void HT16K33_set_alpha(char chr, uint32_t digit, bool has_dot);
void HT16K33_set_number(uint32_t number, uint32_t digit, bool has_dot);

uint32_t bcd(uint32_t base);


#endif  // _HT16K33_HEADER_
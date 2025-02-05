#pragma once

#define LCD_H_RES           128
#define LCD_V_RES           128
#define LCD_BITS_PIXEL      16
#define LCD_OFFSET_X        2
#define LCD_OFFSET_Y        1

#define LCD_BUF_LINES      16
#define LCD_DOUBLE_BUFFER  1
#define LCD_DRAWBUF_SIZE   (LCD_H_RES * LCD_BUF_LINES)

#define LCD_MIRROR_X       (false)
#define LCD_MIRROR_Y       (false)

#define LCD_PIXEL_CLOCK_HZ (20 * 1000 * 1000)
#define LCD_CMD_BITS       (8)
#define LCD_PARAM_BITS     (8)

#define LCD_SPI_HOST       SPI2_HOST
#define LCD_SPI_CLK        (gpio_num_t) GPIO_NUM_18
#define LCD_SPI_MOSI       (gpio_num_t) GPIO_NUM_23
#define LCD_SPI_MISO       (gpio_num_t) GPIO_NUM_19
#define LCD_DC             (gpio_num_t) GPIO_NUM_17
#define LCD_CS             (gpio_num_t) GPIO_NUM_26
#define LCD_RESET          (gpio_num_t) GPIO_NUM_16
#define LCD_BUSY           (gpio_num_t) GPIO_NUM_NC

#define LCD_BACKLIGHT      (gpio_num_t) GPIO_NUM_13
#define LCD_BACKLIGHT_LEDC_CH  (1)

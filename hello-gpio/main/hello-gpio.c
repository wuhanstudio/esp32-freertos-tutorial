#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include "driver/gpio.h"

#include "esp_log.h"

static const char *TAG = "example";

#define RGB_GPIO_R GPIO_NUM_27
#define RGB_GPIO_G GPIO_NUM_32
#define RGB_GPIO_B GPIO_NUM_33

static uint8_t s_led_state = 0;

void app_main(void)
{
    printf("Hello world!\n");

    gpio_set_direction(RGB_GPIO_R, GPIO_MODE_OUTPUT);

    while(1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        gpio_set_level(RGB_GPIO_R, s_led_state);
        s_led_state = !s_led_state;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

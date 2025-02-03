#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <esp_log.h>

static const char *TAG = "hello";

void app_main(void)
{
    while (1) {
        ESP_LOGI(TAG, "Hello FreeRTOS");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

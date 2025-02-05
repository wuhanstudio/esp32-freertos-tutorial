#include <stdio.h>
#include <math.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <freertos/semphr.h>

#include <esp_system.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_check.h>

#include <lvgl.h>
#include <esp_lvgl_port.h>

#include "lcd.h"

static const char *TAG="demo";

static esp_err_t app_lvgl_main(void)
{
    // Set the default font to a larger one, like `lv_font_montserrat_16` or `lv_font_montserrat_32`
    // lv_theme_set_current(lv_theme_material_init(0, NULL)); // set theme (optional)
    lv_obj_set_style_text_font(lv_scr_act(), &lv_font_montserrat_10, LV_PART_MAIN); // Set the font for the active screen

    lv_obj_t *scr = lv_scr_act();

    lvgl_port_lock(0);

    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_text(label, "Hello LVGL 9!");
    lv_obj_set_style_text_color(label, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);

    lvgl_port_unlock();

    return ESP_OK;
}


void app_main(void)
{
    esp_lcd_panel_io_handle_t lcd_io;
    esp_lcd_panel_handle_t lcd_panel;
    lv_display_t *lvgl_display = NULL;

    ESP_ERROR_CHECK(lcd_display_brightness_init());

    ESP_ERROR_CHECK(app_lcd_init(&lcd_io, &lcd_panel));
    lvgl_display = app_lvgl_init(lcd_io, lcd_panel);
    if (lvgl_display == NULL)
    {
        ESP_LOGI(TAG, "Fatal error in app_lvgl_init");
        esp_restart();
    }
    
    ESP_ERROR_CHECK(lcd_display_brightness_set(75));
    ESP_ERROR_CHECK(lcd_display_rotate(lvgl_display, LV_DISPLAY_ROTATION_0));
    ESP_ERROR_CHECK(app_lvgl_main());

    while(1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

#include <stdio.h>
#include <time.h>
#include <freertos/FreeRTOS.h>

#include <esp_log.h>
#include <driver/gpio.h>

#include "st7735.h"

static const char *TAG = "ST7735";

// ST7735 stuff
#define CONFIG_WIDTH  128
#define CONFIG_HEIGHT 128

#define OFFSET_X 2
#define OFFSET_Y 3
#define FRAME_BUFFER true

#define GPIO_MOSI   23
#define GPIO_SCLK   18
#define GPIO_CS     26
#define GPIO_DC     17
#define GPIO_RESET  16

#define GPIO_BL     13

TickType_t FillTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, RED);
	lcdDrawFinish(dev);
	vTaskDelay(50);
	lcdFillScreen(dev, GREEN);
	lcdDrawFinish(dev);
	vTaskDelay(50);
	lcdFillScreen(dev, BLUE);
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t ColorBarTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t y1,y2;
	y1 = height/3;
	y2 = (height/3)*2;
	//ESP_LOGI(TAG, "y1=%d y2=%d",y1,y2);
	lcdDrawFillRect(dev, 0, 0, width-1, y1-1, RED);
	lcdDrawFillRect(dev, 0, y1-1, width-1, y2-1, GREEN);
	lcdDrawFillRect(dev, 0, y2-1, width-1, height-1, BLUE);
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t LineTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t color;
	//lcdFillScreen(dev, WHITE);
	lcdFillScreen(dev, BLACK);
	color=RED;
	for(int ypos=0;ypos<height;ypos=ypos+10) {
		lcdDrawLine(dev, 0, ypos, width, ypos, color);
	}

	for(int xpos=0;xpos<width;xpos=xpos+10) {
		lcdDrawLine(dev, xpos, 0, xpos, height, color);
	}
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t CircleTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t color;
	//lcdFillScreen(dev, WHITE);
	lcdFillScreen(dev, BLACK);
	color = GRAY;
	uint16_t xpos = width/2;
	uint16_t ypos = height/2;
	for(int i=5;i<height;i=i+5) {
		lcdDrawCircle(dev, xpos, ypos, i, color);
	}
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t RoundRectTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t color;
	//lcdFillScreen(dev, WHITE);
	lcdFillScreen(dev, BLACK);
	color = BLUE;
	for(int i=5;i<width;i=i+5) {
		if (i > (width-i-1) ) break;
		//ESP_LOGI(TAG, "i=%d, width-i-1=%d",i, width-i-1);
		lcdDrawRoundRect(dev, i, i, (width-i-1), (height-i-1), 10, color);
	}
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t FillRectTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t color;
	lcdFillScreen(dev, WHITE);

	uint16_t red;
	uint16_t green;
	uint16_t blue;
	srand( (unsigned int)time( NULL ) );
	for(int i=1;i<100;i++) {
		red=rand()%255;
		green=rand()%255;
		blue=rand()%255;
		color=rgb565(red, green, blue);
		uint16_t xpos=rand()%width;
		uint16_t ypos=rand()%height;
		uint16_t size=rand()%(width/5);
		lcdDrawFillRect(dev, xpos, ypos, xpos+size, ypos+size, color);
	}
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

TickType_t ColorTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t color;
	lcdFillScreen(dev, WHITE);
	color = RED;
	uint16_t delta = height/16;
	uint16_t ypos = 0;
	for(int i=0;i<16;i++) {
		//ESP_LOGI(TAG, "color=0x%x",color);
		lcdDrawFillRect(dev, 0, ypos, width-1, ypos+delta, color);
		color = color >> 1;
		ypos = ypos + delta;
	}
	lcdDrawFinish(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%"PRIu32,diffTick*portTICK_PERIOD_MS);
	return diffTick;
}

void tft(void *pvParameters)
{
	TFT_t dev;
	spi_master_init(&dev, GPIO_MOSI, GPIO_SCLK, GPIO_CS, GPIO_DC, GPIO_RESET);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, OFFSET_X, OFFSET_Y, FRAME_BUFFER);

	while (1) {
		ESP_LOGD(TAG, "Mainloop Start");

		FillTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		ColorBarTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		LineTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		CircleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		RoundRectTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		FillRectTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		ColorTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		vTaskDelay(500);

		ESP_LOGD(TAG, "Mainloop End");
	}
}

void app_main(void)
{
	gpio_reset_pin(GPIO_BL);
    gpio_set_direction(GPIO_BL, GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_BL, 1);
	xTaskCreate(tft, "TFT", 4096, NULL, 2, NULL);
}

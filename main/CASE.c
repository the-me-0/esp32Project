#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "DHT.h"

static const char *TAG = "#_x2eq1";

#define LED_GPIO 18
#define DHT_GPIO 4

// LED variables
static led_strip_handle_t led_strip;
static enum {
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    RED,
} s_color = BLUE;


// DHT variables
static float humidity;
static float temperature;


static void color_led(void)
{
    switch (s_color) {
    case BLUE:
        led_strip_set_pixel(led_strip, 0, 0, 0, 255);
        break;
    case GREEN:
        led_strip_set_pixel(led_strip, 0, 0, 255, 0);
        break;
    case YELLOW:
        led_strip_set_pixel(led_strip, 0, 255, 255, 0);
        break;
    case ORANGE:
        led_strip_set_pixel(led_strip, 0, 255, 165, 0);
        break;
    case RED:
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        break;
    }

    /* Refresh the strip to send data */
    led_strip_refresh(led_strip);
}

static void update_color(void)
{
    if (temperature < 19)
        s_color = BLUE;
    else if (temperature < 20)
        s_color = GREEN;
    else if (temperature < 21)
        s_color = YELLOW;
    else if (temperature < 22)
        s_color = ORANGE;
    else
        s_color = RED;
    ESP_LOGI(TAG, "Color: %d", s_color);
    color_led();
}

static void getDHTValues(void)
{
    errorHandler(readDHT());
    temperature = getTemperature();
    humidity = getHumidity();
}

static void init(void)
{
    ESP_LOGI(TAG, "Led configuration...");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);

    ESP_LOGI(TAG, "DHT configuration...");
    /* Set the GPIO pin for the DHT sensor */
    setDHTgpio(DHT_GPIO);
}


void app_main(void)
{
    /* Configure the peripheral according to the LED type */
    init();

    ESP_LOGI(TAG, "All configured. Starting main loop...");

    while (1) {
        // update the temp & hum values
        getDHTValues();

        // update the led color according to the humidity
        update_color();

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
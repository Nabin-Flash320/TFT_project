#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"

#include "lcd_com.h"
#include "lcd_lib.h"
#include "fontx.h"
#include "bmpfile.h"
#include "decode_jpeg.h"
#include "decode_png.h"
#include "pngle.h"
#include "esp_random.h"
#include "temperature_profiles.h"
#include "driver/gpio.h"

#include "ili9486.h"
#define DRIVER "ST7796"
#define INIT_FUNCTION(a, b, c, d, e) ili9486_lcdInit(a, b, c, d, e)

static const char *TAG = "MAIN";
static e_profile_idx_t profile_selected = 1;
static uint8_t max = 0;
static uint8_t min = 0;

static TFT_t dev;
static uint8_t *temperatureProfile = NULL;

// Check memory leek
void traceHeap()
{
	static int flag = 0;
	static uint32_t _first_free_heap_size = 0;
	if (flag == 0)
	{
		flag++;
	}
	else if (flag == 1)
	{
		_first_free_heap_size = esp_get_free_heap_size();
		flag++;
	}
	else
	{
		int _diff_free_heap_size = _first_free_heap_size - esp_get_free_heap_size();
		ESP_LOGI(__FUNCTION__, "_diff_free_heap_size=%d", _diff_free_heap_size);
	}
}

static void profile_selector_gpio_handler(void *arg)
{
	clear_profile_graph(&dev, temperatureProfile, 36, 36, min, max);
	++profile_selected;
	if (TEMP_PROJECT_PROFILE_MAX == profile_selected)
	{
		profile_selected = 1;
	}
	temperatureProfile = select_profile(&dev, profile_selected);
	temperatureProfile = select_profile(&dev, profile_selected);
	highlight_profile(&dev, profile_selected);
	draw_profile_graph(&dev, temperatureProfile, 36, 36, min, max, WHITE);
}

void TFT(void *pvParameters)
{

	uint16_t background_color = BLACK;
	uint16_t rectangle_color = WHITE;
	uint16_t font_color = WHITE;
	// set font file
	FontxFile fx16G[2];
	FontxFile fx24G[2];
	FontxFile fx32G[2];
	InitFontx(fx16G, "/spiffs/ILGH16XB.FNT", ""); // 8x16Dot Gothic
	InitFontx(fx24G, "/spiffs/ILGH24XB.FNT", ""); // 12x24Dot Gothic
	InitFontx(fx32G, "/spiffs/ILGH32XB.FNT", ""); // 16x32Dot Gothic

	FontxFile fx16M[2];
	FontxFile fx24M[2];
	FontxFile fx32M[2];
	InitFontx(fx16M, "/spiffs/ILMH16XB.FNT", ""); // 8x16Dot Mincyo
	InitFontx(fx24M, "/spiffs/ILMH24XB.FNT", ""); // 12x24Dot Mincyo
	InitFontx(fx32M, "/spiffs/ILMH32XB.FNT", ""); // 16x32Dot Mincyo


	lcd_interface_cfg(&dev, INTERFACE_GPIO);
	INIT_FUNCTION(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

	for (int i = TEMP_PROJECT_PROFILE_1; i < TEMP_PROJECT_PROFILE_MAX; i++)
	{
		profile_add(i, rectangle_color, "Profile", font_color);
	}
	print_profiles();

	traceHeap();

	lcdFillScreen(&dev, background_color);
	lcdDrawRect(&dev, 15, 15, CONFIG_WIDTH - 15, CONFIG_HEIGHT - 120, rectangle_color);
	lcdDrawRect(&dev, 16, 16, CONFIG_WIDTH - 16, CONFIG_HEIGHT - 121, rectangle_color);
	lcdDrawRect(&dev, 17, 17, CONFIG_WIDTH - 17, CONFIG_HEIGHT - 122, rectangle_color);

	draw_profile_rects(&dev, fx16M);

	gpio_config_t profile_button_config = {
		.pin_bit_mask = (1ULL << 5),
		.mode = GPIO_MODE_INPUT,
		.pull_up_en = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_ENABLE,
		.intr_type = GPIO_INTR_POSEDGE,
	};
	gpio_config(&profile_button_config);
	gpio_install_isr_service(0);
	gpio_isr_handler_add(5, profile_selector_gpio_handler, NULL);

	while (1)
	{
		temperatureProfile = select_profile(&dev, profile_selected);
		temperatureProfile = select_profile(&dev, profile_selected);
		highlight_profile(&dev, profile_selected);
		max = get_max(temperatureProfile, 150);
		min = get_min(temperatureProfile, 150);
		draw_profile_graph(&dev, temperatureProfile, 36, 36, min, max, WHITE);
		vTaskDelay(portMAX_DELAY);
	} // end while
} // END TFT function

static void listSPIFFS(char *path)
{
	DIR *dir = opendir(path);
	assert(dir != NULL);
	while (true)
	{
		struct dirent *pe = readdir(dir);
		if (!pe)
			break;
		ESP_LOGI(__FUNCTION__, "d_name=%s d_ino=%d d_type=%x", pe->d_name, pe->d_ino, pe->d_type);
	}
	closedir(dir);
}

esp_err_t mountSPIFFS(char *path, char *label, int max_files)
{
	esp_vfs_spiffs_conf_t conf = {
		.base_path = path,
		.partition_label = label,
		.max_files = max_files,
		.format_if_mount_failed = true};

	// Use settings defined above toinitialize and mount SPIFFS filesystem.
	// Note: esp_vfs_spiffs_register is anall-in-one convenience function.
	esp_err_t ret = esp_vfs_spiffs_register(&conf);

	if (ret != ESP_OK)
	{
		if (ret == ESP_FAIL)
		{
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		}
		else if (ret == ESP_ERR_NOT_FOUND)
		{
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		}
		else
		{
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
		}
		return ret;
	}

	size_t total = 0, used = 0;
	ret = esp_spiffs_info(conf.partition_label, &total, &used);
	if (ret != ESP_OK)
	{
		ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
	}
	else
	{
		ESP_LOGI(TAG, "Mount %s to %s success", path, label);
		ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
	}

	return ret;
}

void app_main()
{
	// Initialize NVS
	ESP_LOGI(TAG, "Initialize NVS");
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		// NVS partition was truncated and needs to be erased
		// Retry nvs_flash_init
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);

	ESP_LOGI(TAG, "Initializing SPIFFS");
	esp_err_t ret;
	ret = mountSPIFFS("/spiffs", "storage0", 10);
	if (ret != ESP_OK)
		return;
	listSPIFFS("/spiffs/");

	// Image file borrowed from here
	// https://www.flaticon.com/packs/social-media-343
	ret = mountSPIFFS("/icons", "storage1", 10);
	if (ret != ESP_OK)
		return;
	listSPIFFS("/icons/");

	ret = mountSPIFFS("/images", "storage2", 14);
	if (ret != ESP_OK)
		return;
	listSPIFFS("/images/");

	xTaskCreate(TFT, "TFT", 1024 * 6, NULL, 2, NULL);
}

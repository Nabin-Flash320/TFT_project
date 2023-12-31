
#ifndef __TEMPERATURE_PROFILES_H__
#define __TEMPERATURE_PROFILES_H__

#include "stdint.h"
#include "esp_err.h"
#include "fontx.h"
#include "lcd_com.h"
#include "lcd_lib.h"

#define HIGHLIGHT true
#define LOWLIGHT false


typedef enum e_profile_idx
{
    TEMP_PROJECT_PROFILE_1 = 1,
    TEMP_PROJECT_PROFILE_2,
    TEMP_PROJECT_PROFILE_3,
    TEMP_PROJECT_PROFILE_4,
    TEMP_PROJECT_PROFILE_5,
    TEMP_PROJECT_PROFILE_MAX,
} e_profile_idx_t;

typedef struct ll_temp_project_profiles
{
    e_profile_idx_t profile_idx;
    bool highlight;
    int rect_start_x;
    int rect_start_y;
    int rect_end_x;
    int rect_end_y;
    uint16_t rect_color;
    char rect_text[40];
    int rect_text_offset_x;
    int rect_text_offset_y;
    uint16_t text_direction;
    uint16_t text_color;
    struct ll_temp_project_profiles *next;
} ll_temp_project_profiles_t;

e_profile_idx_t profile_add(e_profile_idx_t profile_idx, uint16_t rect_color, char rect_text[], uint16_t text_color);
void print_profiles();
void draw_profile_rects(TFT_t *dev, FontxFile *fx);
void draw_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color);
uint8_t *select_profile(TFT_t *dev, e_profile_idx_t profile_index);
void highlight_profile(TFT_t *dev, e_profile_idx_t profile_idx);
void draw_axies(TFT_t *dev, int offset_x, int offset_y, uint32_t color);
void draw_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color);
void clear_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max);
uint8_t get_max(uint8_t *array, size_t length);
uint8_t get_min(uint8_t *array, size_t length);

#endif // __TEMPERATURE_PROFILES_H__

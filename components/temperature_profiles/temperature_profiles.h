
#ifndef __TEMPERATURE_PROFILES_H__
#define __TEMPERATURE_PROFILES_H__

#include "stdint.h"
#include "esp_err.h"
#include "fontx.h"
#include "lcd_com.h"
#include "lcd_lib.h"

#define HIGHLIGHT true
#define LOWLIGHT false
// #define TEMP_PROJECT_PROFILE_MAX 7
#define RECTANGLE_ARRAY_SIZE 5
#define RECTANGLE_DISPLAY_SIZE 6

// typedef int e_profile_idx_t;

typedef enum e_rect_type
{
    RECT_TYPE_PROFILE = 1,
    RECT_TYPE_KEYPAD,
    RECT_TYPE_MAX
} e_rect_type_t;

typedef enum e_profile_idx
{
    TEMP_PROJECT_PROFILE_1 = 1,
    TEMP_PROJECT_PROFILE_2,
    TEMP_PROJECT_PROFILE_3,
    TEMP_PROJECT_PROFILE_4,
    TEMP_PROJECT_PROFILE_5,
    TEMP_PROJECT_PROFILE_KEYPAD,
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

typedef struct s_rectangle
{
    e_rect_type_t rect_type;
    bool highlight;
    int rect_start_x;
    int rect_start_y;
    int rect_end_x;
    int rect_end_y;
    uint16_t rect_color;
    char *rect_text;
    int rect_text_array_offset;
    int rect_text_offset_x;
    int rect_text_offset_y;
    uint16_t text_direction;
    uint16_t text_color;
} s_rectangle_t;

int rectangle_array_prepare();
e_profile_idx_t profile_add(e_profile_idx_t profile_idx, uint16_t rect_color, char rect_text[], uint16_t text_color);
void draw_profile_rects(TFT_t *dev, FontxFile *fx);
void draw_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color);
uint8_t *select_profile(TFT_t *dev, e_profile_idx_t profile_index);
void highlight_profile(TFT_t *dev, e_profile_idx_t profile_idx);
void draw_axies(TFT_t *dev, int offset_x, int offset_y, uint32_t color);
void draw_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color);
void clear_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max);
void clear_text(TFT_t *dev, FontxFile *file);
uint8_t get_max(uint8_t *array, size_t length);
uint8_t get_min(uint8_t *array, size_t length);
void add_text_with_offset(int offset);
void change_text(TFT_t *dev, FontxFile *file);

#endif // __TEMPERATURE_PROFILES_H__

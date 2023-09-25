
#include "temperature_profiles.h"
#include "string.h"

// Temperature Profile 1: Linear Increase from 25°C to 75°C
static uint8_t temperatureProfile1[150] = {
    25, 27, 29, 31, 33, 35, 37, 39, 41, 43, // 0 to 9
    45, 47, 49, 51, 53, 55, 57, 59, 61, 63, // 10 to 19
    65, 67, 69, 71, 73, 75, 75, 75, 75, 75, // 20 to 29
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 30 to 39
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 40 to 49
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 50 to 59
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 60 to 69
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 70 to 79
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 80 to 89
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 90 to 99
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 100 to 109
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 110 to 119
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 120 to 129
    75, 75, 75, 75, 75, 75, 75, 75, 75, 75, // 130 to 139
    45, 47, 49, 51, 53, 55, 57, 59, 61, 63, // 140 to 149
};

// Temperature Profile 2: Sinusoidal Variation Between 20°C and 40°C
static uint8_t temperatureProfile2[150] = {
    20, 22, 25, 29, 33, 37, 40, 37, 33, 29, // 0 to 9
    25, 22, 20, 22, 25, 29, 33, 37, 40, 37, // 10 to 19
    33, 29, 25, 22, 20, 22, 25, 29, 33, 37, // 20 to 29
    40, 37, 33, 29, 25, 22, 20, 22, 25, 29, // 30 to 39
    33, 37, 40, 37, 33, 29, 25, 22, 20, 22, // 40 to 49
    25, 29, 33, 37, 40, 37, 33, 29, 25, 22, // 50 to 59
    20, 22, 25, 29, 33, 37, 40, 37, 33, 29, // 60 to 69
    25, 22, 20, 22, 25, 29, 33, 37, 40, 37, // 70 to 79
    33, 29, 25, 22, 20, 22, 25, 29, 33, 37, // 80 to 89
    40, 37, 33, 29, 25, 22, 20, 22, 25, 29, // 90 to 99
    33, 37, 40, 37, 33, 29, 25, 22, 20, 22, // 100 to 109
    25, 29, 33, 37, 40, 37, 33, 29, 25, 22, // 110 to 119
    20, 22, 25, 29, 33, 37, 40, 37, 33, 29, // 120 to 129
    25, 22, 20, 22, 25, 29, 33, 37, 40, 37, // 130 to 139
    29, 33, 37, 40, 37, 33, 29, 25, 22, 20, // 140 to 159
};

// Temperature Profile 3: Stepwise Increase from 30°C to 90°C
static uint8_t temperatureProfile3[150] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, // 0 to 9
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40, // 10 to 19
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, // 20 to 29
    60, 60, 60, 60, 60, 60, 60, 60, 60, 60, // 30 to 39
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70, // 40 to 49
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, // 50 to 59
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, // 60 to 69
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 70 to 79
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 80 to 89
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 90 to 99
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 100 to 109
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 110 to 119
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 120 to 129
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 130 to 139
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90, // 140 to 159
};

// Temperature Profile 4: Random Variation Between 25°C and 50°C
static uint8_t temperatureProfile4[150] = {
    25, 28, 30, 32, 29, 27, 30, 35, 37, 40, // 0 to 9
    38, 35, 33, 30, 27, 25, 28, 30, 32, 29, // 10 to 19
    27, 30, 35, 37, 40, 38, 35, 33, 30, 27, // 20 to 29
    25, 28, 30, 32, 29, 27, 30, 35, 37, 40, // 30 to 39
    38, 35, 33, 30, 27, 25, 28, 30, 32, 29, // 40 to 49
    27, 30, 35, 37, 40, 38, 35, 33, 30, 27, // 50 to 59
    25, 28, 30, 32, 29, 27, 30, 35, 37, 40, // 60 to 69
    38, 35, 33, 30, 27, 25, 28, 30, 32, 29, // 70 to 79
    27, 30, 35, 37, 40, 38, 35, 33, 30, 27, // 80 to 89
    25, 28, 30, 32, 29, 27, 30, 35, 37, 40, // 90 to 99
    38, 35, 33, 30, 27, 25, 28, 30, 32, 29, // 100 to 109
    27, 30, 35, 37, 40, 38, 35, 33, 30, 27, // 110 to 119
    25, 28, 30, 32, 29, 27, 30, 35, 37, 40, // 120 to 129
    27, 25, 28, 30, 32, 29, 27, 30, 35, 37, // 130 to 139
    40, 38, 35, 33, 30, 27, 25, 28, 30, 32, // 140 to 159
};

// Temperature Profile 5: Sawtooth Pattern from 10°C to 60°C
static uint8_t temperatureProfile5[150] = {
    10, 12, 15, 18, 22, 25, 30, 35, 40, 45, // 0 to 9
    50, 55, 60, 55, 50, 45, 40, 35, 30, 25, // 10 to 19
    22, 18, 15, 12, 10, 12, 15, 18, 22, 25, // 20 to 29
    30, 35, 40, 45, 50, 55, 60, 55, 50, 45, // 30 to 39
    40, 35, 30, 25, 22, 18, 15, 12, 10, 12, // 40 to 49
    15, 18, 22, 25, 30, 35, 40, 45, 50, 55, // 50 to 59
    60, 55, 50, 45, 40, 35, 30, 25, 22, 18, // 60 to 69
    15, 12, 10, 12, 15, 18, 22, 25, 30, 35, // 70 to 79
    40, 45, 50, 55, 60, 55, 50, 45, 40, 35, // 80 to 89
    30, 25, 22, 18, 15, 12, 10, 12, 15, 18, // 90 to 99
    22, 25, 30, 35, 40, 45, 50, 55, 60, 55, // 100 to 109
    50, 45, 40, 35, 30, 25, 22, 18, 15, 12, // 110 to 119
    10, 12, 15, 18, 22, 25, 30, 35, 40, 45, // 120 to 129
    55, 60, 55, 50, 45, 40, 35, 30, 25, 22, // 130 to 139
    18, 15, 12, 10, 12, 15, 18, 22, 25, 30, // 140 to 159
};

static ll_temp_project_profiles_t *profile_rect_head = NULL;
static int profile_highlight_count = 1;
const static int profile_rect_width = 45;
const static int profile_rect_height = 100;
const static int profile_rect_margin_height = 12;
static const int horizontal_gap = 5;
static const int verticle_gap = 2;

static s_rectangle_t rectangle_array[RECTANGLE_ARRAY_SIZE] = {{0}, {0}, {0}, {0}, {0}};
static char *rectangle_display[RECTANGLE_DISPLAY_SIZE] = {"Profile 1", "Profile 2", "Profile 3", "Profile 4", "Profile 5", "Keypad"};

int rectangle_array_prepare()
{
    int ret = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            rectangle_array[i].highlight = LOWLIGHT;
            rectangle_array[i].rect_start_x = ((CONFIG_WIDTH / 4) * 3) + 14;
            rectangle_array[i].rect_start_y = CONFIG_HEIGHT - 110;
            rectangle_array[i].rect_end_x = rectangle_array[i].rect_start_x + profile_rect_width;
            rectangle_array[i].rect_end_y = rectangle_array[i].rect_start_y + profile_rect_height;
        }
        else
        {
            rectangle_array[i].highlight = LOWLIGHT;
            rectangle_array[i].rect_start_x = rectangle_array[i - 1].rect_start_x - profile_rect_margin_height - profile_rect_width;
            rectangle_array[i].rect_start_y = rectangle_array[i - 1].rect_start_y;
            rectangle_array[i].rect_end_x = rectangle_array[i].rect_start_x + profile_rect_width;
            rectangle_array[i].rect_end_y = rectangle_array[i].rect_start_y + profile_rect_height;
        }
        rectangle_array[i].rect_text_array_offset = i;
        rectangle_array[i].rect_text = rectangle_display[i];
        rectangle_array[i].rect_color = WHITE;
        rectangle_array[i].rect_text_offset_x = 15;
        rectangle_array[i].rect_text_offset_y = 13;
        rectangle_array[i].text_direction = DIRECTION90;
        rectangle_array[i].text_color = WHITE;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("rectangle_array[%d].rect_start_x is: %d\n", (i + 1), rectangle_array[i].rect_start_x);
        printf("rectangle_array[%d].rect_start_y is: %d\n", (i + 1), rectangle_array[i].rect_start_y);
        printf("rectangle_array[%d].rect_end_x is: %d\n", (i + 1), rectangle_array[i].rect_end_x);
        printf("rectangle_array[%d].rect_end_y is: %d\n", (i + 1), rectangle_array[i].rect_end_y);
        printf("rectange_array[%d].rect_text_array_offset is: %d\n", (i + 1), rectangle_array[i].rect_text_array_offset);
        printf("rectange_array[%d].rect_text is: %s\n", (i + 1), rectangle_array[i].rect_text);
        printf("***************************\n");
    }
    return ret;
}

void draw_profile_rects(TFT_t *dev, FontxFile *fx)
{
    for (int i = 0; i < RECTANGLE_ARRAY_SIZE; i++)
    {
        lcdDrawRect(dev, rectangle_array[i].rect_start_x, rectangle_array[i].rect_start_y, rectangle_array[i].rect_end_x,
                    rectangle_array[i].rect_end_y, rectangle_array[i].rect_color);
        lcdSetFontDirection(dev, rectangle_array[i].text_direction);
    }
}

void change_text(TFT_t *dev, FontxFile *file)
{
    for (int i = 0; i < RECTANGLE_ARRAY_SIZE; i++)
    {
        lcdDrawString(dev, file, rectangle_array[i].rect_start_x + rectangle_array[i].rect_text_offset_x,
                      rectangle_array[i].rect_start_y + rectangle_array[i].rect_text_offset_y,
                      (uint8_t *)rectangle_array[i].rect_text, rectangle_array[i].text_color);
    }
}

void add_text_with_offset(int offset)
{
    for (int i = 0; i < RECTANGLE_ARRAY_SIZE; i++)
    {
        rectangle_array[i].rect_text = rectangle_display[i + offset];
    }
}

void clear_text(TFT_t *dev, FontxFile *file)
{
    for (int i = 0; i < RECTANGLE_ARRAY_SIZE; i++)
    {
        lcdDrawString(dev, file, rectangle_array[i].rect_start_x + rectangle_array[i].rect_text_offset_x,
                      rectangle_array[i].rect_start_y + rectangle_array[i].rect_text_offset_y,
                      (uint8_t *)rectangle_array[i].rect_text, BLACK);
    }
}

e_profile_idx_t profile_add(e_profile_idx_t profile_idx, uint16_t rect_color, char rect_text[], uint16_t text_color)
{
    if (NULL == profile_rect_head)
    {
        profile_rect_head = (ll_temp_project_profiles_t *)malloc(sizeof(ll_temp_project_profiles_t));
        if (profile_rect_head)
        {
            memset(profile_rect_head, 0, sizeof(ll_temp_project_profiles_t));
            profile_rect_head->profile_idx = profile_idx;
            profile_rect_head->highlight = LOWLIGHT;
            profile_rect_head->rect_start_x = ((CONFIG_WIDTH / 4) * 3) + 14;
            profile_rect_head->rect_start_y = CONFIG_HEIGHT - 110;
            profile_rect_head->rect_end_x = profile_rect_head->rect_start_x + profile_rect_width;
            profile_rect_head->rect_end_y = profile_rect_head->rect_start_y + profile_rect_height;
            profile_rect_head->rect_color = rect_color;
            snprintf(profile_rect_head->rect_text, 40, "%s %d", rect_text, profile_idx);
            profile_rect_head->rect_text_offset_x = 15;
            profile_rect_head->rect_text_offset_y = 13;
            profile_rect_head->text_direction = DIRECTION90;
            profile_rect_head->text_color = text_color;
            profile_rect_head->next = NULL;
        }
    }
    else
    {

        ll_temp_project_profiles_t *current_profile = profile_rect_head;
        while (current_profile->next)
        {
            current_profile = current_profile->next;
        }
        current_profile->next = (ll_temp_project_profiles_t *)malloc(sizeof(ll_temp_project_profiles_t));
        if (current_profile->next)
        {
            memset(current_profile->next, 0, sizeof(ll_temp_project_profiles_t));
            current_profile->next->profile_idx = profile_idx;
            current_profile->next->highlight = LOWLIGHT;
            current_profile->next->rect_start_x = current_profile->rect_start_x - profile_rect_margin_height - profile_rect_width;
            current_profile->next->rect_start_y = current_profile->rect_start_y;
            current_profile->next->rect_end_x = current_profile->next->rect_start_x + profile_rect_width;
            current_profile->next->rect_end_y = current_profile->next->rect_start_y + profile_rect_height;
            current_profile->next->rect_color = rect_color;
            snprintf(current_profile->next->rect_text, 40, "%s %d", rect_text, profile_idx);
            current_profile->next->rect_text_offset_x = 15;
            current_profile->next->rect_text_offset_y = 13;
            current_profile->next->text_direction = DIRECTION90;
            current_profile->next->text_color = text_color;
            current_profile->next->next = NULL;
        }
    }
    return 0;
}

void print_profiles()
{
    if (!profile_rect_head)
    {
        printf("NULL profile head!!");
    }
    else
    {
        ll_temp_project_profiles_t *current_profile = profile_rect_head;
        while (current_profile)
        {
            printf("Profile index is %d\n", current_profile->profile_idx);
            printf("highlight: %s\n", current_profile->highlight ? "true" : "false");
            printf("rect_start_x is %d\n", current_profile->rect_start_x);
            printf("rect_start_y is %d\n", current_profile->rect_start_y);
            printf("rect_end_x is %d\n", current_profile->rect_end_x);
            printf("rect_end_y is %d\n", current_profile->rect_end_y);
            printf("rect_color is 0x%04X\n", current_profile->rect_color);
            printf("rect_text is %s\n", current_profile->rect_text);
            printf("rect_text_offset_x is %d\n", current_profile->rect_text_offset_x);
            printf("rect_text_offset_y is %d\n", current_profile->rect_text_offset_y);
            printf("text_direction is %d\n", current_profile->text_direction);
            printf("text_color is 0x%04X\n", current_profile->text_color);
            printf("***************************\n");
            current_profile = current_profile->next;
        }
    }
}

// void draw_profile_rects(TFT_t *dev, FontxFile *fx)
// {
//     if (!profile_rect_head)
//     {
//         printf("NULL profile head!!\n");
//     }
//     else
//     {
//         ll_temp_project_profiles_t *current_profile = profile_rect_head;
//         while (current_profile)
//         {
//             lcdDrawRect(dev, current_profile->rect_start_x,
//                         current_profile->rect_start_y, current_profile->rect_end_x,
//                         current_profile->rect_end_y, current_profile->rect_color);
//             lcdSetFontDirection(dev, current_profile->text_direction);
//             lcdDrawString(dev, fx, current_profile->rect_start_x + current_profile->rect_text_offset_x,
//                           current_profile->rect_start_y + current_profile->rect_text_offset_y,
//                           (uint8_t *)current_profile->rect_text, current_profile->text_color);
//             current_profile = current_profile->next;
//         }
//     }
// }

void draw_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color)
{
    static int start_x;
    static int start_y;
    static int end_x;
    static int end_y;

    start_x = offset_x + (verticle_gap * temperatureProfile[0]);
    start_y = offset_y;
    end_x = offset_x + (verticle_gap * temperatureProfile[horizontal_gap]);
    end_y = offset_y + horizontal_gap;

    for (int i = 1; i <= (151 - horizontal_gap); i += horizontal_gap)
    {
        lcdDrawLine(dev, start_x, start_y, end_x, end_y, color);

        start_x = end_x;
        start_y = end_y;

        end_x = offset_x + (verticle_gap * temperatureProfile[i + horizontal_gap]);
        end_y = offset_y + (i * 2);
        lcdDrawPixel(dev, end_x, end_y, GREEN);

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

uint8_t *select_profile(TFT_t *dev, e_profile_idx_t profile_index)
{
    uint8_t *temperatureProfile = temperatureProfile1;
    switch (profile_index)
    {
    case 1:
    {
        temperatureProfile = temperatureProfile1;
        break;
    }
    case 2:
    {
        temperatureProfile = temperatureProfile2;
        break;
    }
    case 3:
    {
        temperatureProfile = temperatureProfile3;
        break;
    }
    case 4:
    {
        temperatureProfile = temperatureProfile4;
        break;
    }
    case 5:
    {
        temperatureProfile = temperatureProfile5;
        break;
    }
    default:
    {
        break;
    }
    }
    return temperatureProfile;
}

void highlight_profile(TFT_t *dev, const e_profile_idx_t profile_idx)
{
    if ((profile_idx > 0) && (profile_idx <= 5))
    {
        for (int i = 0; i < 5; i++)
        {
            if ((profile_idx - 1) == i)
            {
                // Outer rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x - 1, rectangle_array[i].rect_start_y - 1,
                            rectangle_array[i].rect_end_x + 1, rectangle_array[i].rect_end_y + 1, GREEN);
                // Middle rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x, rectangle_array[i].rect_start_y,
                            rectangle_array[i].rect_end_x, rectangle_array[i].rect_end_y, GREEN);
                // Inner rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x + 1, rectangle_array[i].rect_start_y + 1,
                            rectangle_array[i].rect_end_x - 1, rectangle_array[i].rect_end_y - 1, GREEN);
            }
            else
            {
                // Outer rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x - 1, rectangle_array[i].rect_start_y - 1,
                            rectangle_array[i].rect_end_x + 1, rectangle_array[i].rect_end_y + 1, BLACK);
                // Middle rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x, rectangle_array[i].rect_start_y,
                            rectangle_array[i].rect_end_x, rectangle_array[i].rect_end_y, WHITE);
                // Inner rectangle
                lcdDrawRect(dev, rectangle_array[i].rect_start_x + 1, rectangle_array[i].rect_start_y + 1,
                            rectangle_array[i].rect_end_x - 1, rectangle_array[i].rect_end_y - 1, BLACK);
            }
        }
    }
}

// void highlight_profile(TFT_t *dev, e_profile_idx_t profile_idx)
// {
//     if (!profile_rect_head)
//     {
//         printf("NULL profile head!!\n");
//     }
//     else
//     {
//         ll_temp_project_profiles_t *current_profile = profile_rect_head;
//         while (current_profile)
//         {
//             if (profile_idx == current_profile->profile_idx)
//             {
//                 // Outer
//                 lcdDrawRect(dev, current_profile->rect_start_x - 1,
//                             current_profile->rect_start_y - 1, current_profile->rect_end_x + 1,
//                             current_profile->rect_end_y + 1, current_profile->rect_color);
//                 lcdDrawRect(dev, current_profile->rect_start_x + 1,
//                             current_profile->rect_start_y + 1, current_profile->rect_end_x - 1,
//                             current_profile->rect_end_y - 1, current_profile->rect_color);
//             }
//             else
//             {
//                 lcdDrawRect(dev, current_profile->rect_start_x - 1,
//                             current_profile->rect_start_y - 1, current_profile->rect_end_x + 1,
//                             current_profile->rect_end_y + 1, BLACK);
//                 lcdDrawRect(dev, current_profile->rect_start_x + 1,
//                             current_profile->rect_start_y + 1, current_profile->rect_end_x - 1,
//                             current_profile->rect_end_y - 1, BLACK);
//             }
//             current_profile = current_profile->next;
//         }
//     }
// }

void clear_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max)
{
    if (dev && temperatureProfile)
    {
        draw_graph(dev, temperatureProfile, offset_x, offset_y, min, max, BLACK);
    }
}

void draw_profile_graph(TFT_t *dev, uint8_t *temperatureProfile, int offset_x, int offset_y, int min, int max, uint32_t color)
{
    if (dev && temperatureProfile)
    {
        draw_graph(dev, temperatureProfile, offset_x, offset_y, min, max, color);
    }
}

void draw_axies(TFT_t *dev, int offset_x, int offset_y, uint32_t color)
{
    // verticle line
    lcdDrawLine(dev, offset_x, offset_y, offset_x + 250, offset_y, color);
    // horizontal line
    lcdDrawLine(dev, offset_x, offset_y, offset_x, offset_y + 300, color);

    // Verticle axis dashes
    for (int i = 0; i < 250; i += verticle_gap)
    {
        lcdDrawLine(dev, (offset_x + i), (offset_y - 2), (offset_x + i), (offset_y + 2), color);
    }

    // Horizontal line dashes
    for (int i = 0; i < 300; i += horizontal_gap)
    {
        lcdDrawLine(dev, (offset_x - 2), (offset_y + i), offset_x + 2, (offset_y + i), color);
    }
}

uint8_t get_min(uint8_t *array, size_t length)
{
    uint8_t min = array[0];
    for (int i = 0; i < length; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

uint8_t get_max(uint8_t *array, size_t length)
{
    uint8_t max = array[0];
    for (int i = 0; i < length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

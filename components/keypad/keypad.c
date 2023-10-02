
#include "keypad.h"
#include "lcd_lib.h"
#include "lcd_com.h"

#define NUMBER_DISPLAY_WIDTH 50

#define NUMBER_DISPLAYING_RECTANGLE_START_X ((CONFIG_WIDTH / 4) * 3) + 11
#define NUMBER_DISPLAYING_RECTANGLE_START_Y 19
#define NUMBER_DISPLAYING_RECTANGLE_END_X NUMBER_DISPLAYING_RECTANGLE_START_X + 50 // (CONFIG_WIDTH - 19)
#define NUMBER_DISPLAYING_RECTANGLE_END_Y (CONFIG_HEIGHT - 124)

static s_keypad_keys_t keymap[16] = {
    [0] = {
        .highlighted = true,
        .key_val = '1',
        .key_location = {210, 22, 245, 97},
    },
    [1] = {
        .highlighted = false,
        .key_val = '2',
        .key_location = {210, 107, 245, 182},
    },
    [2] = {
        .highlighted = false,
        .key_val = '3',
        .key_location = {210, 192, 245, 267},
    },
    [3] = {
        .highlighted = false,
        .key_val = 'A',
        .key_location = {210, 277, 245, 352},
    },
    [4] = {
        .highlighted = false,
        .key_val = '4',
        .key_location = {165, 22, 200, 99},
    },
    [5] = {
        .highlighted = false,
        .key_val = '5',
        .key_location = {165, 107, 200, 182},
    },
    [6] = {
        .highlighted = false,
        .key_val = '6',
        .key_location = {165, 192, 200, 267},
    },
    [7] = {
        .highlighted = false,
        .key_val = 'B',
        .key_location = {165, 277, 200, 352},
    },
    [8] = {
        .highlighted = false,
        .key_val = '7',
        .key_location = {120, 22, 155, 99},
    },
    [9] = {
        .highlighted = false,
        .key_val = '8',
        .key_location = {120, 107, 155, 182},
    },
    [10] = {
        .highlighted = false,
        .key_val = '9',
        .key_location = {120, 192, 155, 267},
    },
    [11] = {
        .highlighted = false,
        .key_val = 'C',
        .key_location = {120, 277, 155, 352},
    },
    [12] = {
        .highlighted = false,
        .key_val = '*',
        .key_location = {75, 22, 110, 99},
    },
    [13] = {
        .highlighted = false,
        .key_val = '0',
        .key_location = {75, 107, 110, 182},
    },
    [14] = {
        .highlighted = false,
        .key_val = '#',
        .key_location = {75, 192, 110, 267},
    },
    [15] = {
        .highlighted = false,
        .key_val = 'D',
        .key_location = {75, 277, 110, 352},
    },
};

void create_keypad_number_displayer(TFT_t *dev)
{
    // Number displaying rectangle.
    // Outer rectangle
    lcdDrawRoundRect(dev, (NUMBER_DISPLAYING_RECTANGLE_START_X - 1), (NUMBER_DISPLAYING_RECTANGLE_START_Y - 1),
                     NUMBER_DISPLAYING_RECTANGLE_END_X + 1, (NUMBER_DISPLAYING_RECTANGLE_END_Y + 1), 10, GREEN);
    // Inner rectangle
    lcdDrawRoundRect(dev, NUMBER_DISPLAYING_RECTANGLE_START_X, NUMBER_DISPLAYING_RECTANGLE_START_Y,
                     NUMBER_DISPLAYING_RECTANGLE_END_X, NUMBER_DISPLAYING_RECTANGLE_END_Y, 10, GREEN);

    // Floating horizontal line in number displaying rectangle.
    lcdDrawLine(dev, (NUMBER_DISPLAYING_RECTANGLE_START_X + 5), (NUMBER_DISPLAYING_RECTANGLE_START_Y + 10),
                NUMBER_DISPLAYING_RECTANGLE_END_X - 5, (NUMBER_DISPLAYING_RECTANGLE_START_Y + 10), CYAN);
    lcdDrawLine(dev, (NUMBER_DISPLAYING_RECTANGLE_START_X + 5), (NUMBER_DISPLAYING_RECTANGLE_START_Y + 11),
                NUMBER_DISPLAYING_RECTANGLE_END_X - 5, (NUMBER_DISPLAYING_RECTANGLE_START_Y + 11), CYAN);
}

void create_keypad_numbers(TFT_t *dev, FontxFile *file)
{
    size_t sizeof_keymap = (sizeof(keymap) / sizeof(keymap[0]));
    printf("The size of keymap is %d\n", sizeof_keymap);
    for (int i = 0; i < sizeof_keymap; i++)
    {
        lcdDrawRoundRect(dev, keymap[i].key_location[0], keymap[i].key_location[1], keymap[i].key_location[2], keymap[i].key_location[3], 5, CYAN);
        lcdSetFontDirection(dev, DIRECTION90);
        lcdDrawString(dev, file, keymap[i].key_location[0], keymap[i].key_location[1] + 30, (uint8_t *)&keymap[i].key_val, CYAN);
    }
}

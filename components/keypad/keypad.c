
#include "keypad.h"
#include "lcd_lib.h"
#include "lcd_com.h"

#define NUMBER_DISPLAY_WIDTH 50

#define NUMBER_DISPLAYING_RECTANGLE_START_X ((CONFIG_WIDTH / 4) * 3) + 11
#define NUMBER_DISPLAYING_RECTANGLE_START_Y 19
#define NUMBER_DISPLAYING_RECTANGLE_END_X NUMBER_DISPLAYING_RECTANGLE_START_X + 50 // (CONFIG_WIDTH - 19)
#define NUMBER_DISPLAYING_RECTANGLE_END_Y (CONFIG_HEIGHT - 124)

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

void create_keypad_numbers(TFT_t *dev)
{
    //  First row
    lcdDrawRoundRect(dev, 210, 22, 245, 97, 5, WHITE);
    lcdDrawRoundRect(dev, 210, 107, 245, 182, 5, WHITE);
    lcdDrawRoundRect(dev, 210, 192, 245, 267, 5, WHITE);
    lcdDrawRoundRect(dev, 210, 277, 245, 352, 5, WHITE);

    // Second row
    lcdDrawRoundRect(dev, 165, 22, 200, 99, 5, WHITE);
    lcdDrawRoundRect(dev, 165, 107, 200, 182, 5, WHITE);
    lcdDrawRoundRect(dev, 165, 192, 200, 267, 5, WHITE);
    lcdDrawRoundRect(dev, 165, 277, 200, 352, 5, WHITE);

    // Third row
    lcdDrawRoundRect(dev, 120, 22, 155, 99, 5, WHITE);
    lcdDrawRoundRect(dev, 120, 107, 155, 182, 5, WHITE);
    lcdDrawRoundRect(dev, 120, 192, 155, 267, 5, WHITE);
    lcdDrawRoundRect(dev, 120, 277, 155, 352, 5, WHITE);

    // Fourth row
    lcdDrawRoundRect(dev, 75, 22, 110, 99, 5, WHITE);
    lcdDrawRoundRect(dev, 75, 107, 110, 182, 5, WHITE);
    lcdDrawRoundRect(dev, 75, 192, 110, 267, 5, WHITE);
    lcdDrawRoundRect(dev, 75, 277, 110, 352, 5, WHITE);
}

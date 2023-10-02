

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "lcd_com.h"
#include "fontx.h"

typedef struct s_keypad_keys{
    uint16_t key_location[4];
    char key_val;
    bool highlighted;
}s_keypad_keys_t;

void create_keypad_number_displayer(TFT_t *dev);
void create_keypad_numbers(TFT_t *dev, FontxFile *file);

#endif // __KEYPAD_H__


#include <stdio.h>
#include <stdint.h>

#define SRC_WIDTH 2
#define SRC_HEIGHT 2
#define DST_WIDTH 4
#define DST_HEIGHT 4
#define BUFFER_ROWS 2

int main(void) {
    uint16_t source[4] = {
        0xF800, 0x07E0, 0x001F, 0xFFFF
    };
    uint16_t buffer[BUFFER_ROWS * DST_WIDTH];
    int scale = 2;
    int y;
    int x;
    for (y = 0; y < DST_HEIGHT; y++) {
        for (x = 0; x < DST_WIDTH; x++) {
            int src_x = x / scale;
            int src_y = y / scale;
            int src_index = src_y * SRC_WIDTH + src_x;
            int dst_index = DST_WIDTH * (y%BUFFER_ROWS) + x;
            buffer[dst_index] = source[src_index];
        }
        if ((y + 1)%BUFFER_ROWS == 0) {
            int k;
            for (k = 0; k < 8; k++) {
                printf("%04X ", (unsigned)buffer[k]); //this would later be "esp_lcd_panel_draw_bitmap" fuction
            }
        }
    }
    return 0;
}
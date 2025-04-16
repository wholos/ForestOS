#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

unsigned short *vga_buffer = (unsigned short *)VGA_MEMORY;
int cursor_x = 0;
int cursor_y = 0;

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = (unsigned short)0x07 << 8 | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        const int index = cursor_y * VGA_WIDTH + cursor_x;
        vga_buffer[index] = (unsigned short)0x07 << 8 | c;
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        for (int y = 1; y < VGA_HEIGHT; y++) {
            for (int x = 0; x < VGA_WIDTH; x++) {
                vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
            }
        }
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (unsigned short)0x07 << 8 | ' ';
        }
        cursor_y = VGA_HEIGHT - 1;
    }
}

void print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}

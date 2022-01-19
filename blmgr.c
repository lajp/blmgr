#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BACKLIGHT_PATH_BASE "/sys/class/backlight/intel_backlight/"

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "Too few arguments provided!\n");
        return EXIT_FAILURE;
    }
    static int change_mult = 1;
    int max_brightness;
    FILE* max_brightness_file = fopen(BACKLIGHT_PATH_BASE "max_brightness", "r");
    fscanf(max_brightness_file, "%d", &max_brightness);
    fclose(max_brightness_file);
    static int brightness;
    switch(argv[1][0]) {
    case '-':
        change_mult = -1;
    case '+':
    {
        int brightness_change;
        if(sscanf(&argv[1][1], "%d", &brightness_change) > 0) {
            int current_brightness;
            FILE* current_brightness_file = fopen(BACKLIGHT_PATH_BASE "brightness", "r");
            fscanf(current_brightness_file, "%d", &current_brightness);
            fclose(current_brightness_file);
            if(strchr(&argv[1][1], '%')) {
                brightness_change *= ((double)max_brightness/(double)100);
            }
            brightness = current_brightness + brightness_change*change_mult;
        } else {
            fprintf(stderr, "Unknown argument provded: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        break;
    }
    default:
        if(sscanf(argv[1], "%d", &brightness) > 0) {
            if(strchr(argv[1], '%')) {
                brightness *= ((double)max_brightness/(double)100);
            }
        } else {
            fprintf(stderr, "Unknown argument provded: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        break;
    }
    if(brightness > max_brightness) {
        brightness = max_brightness;
    }
    printf("Setting brightness to %d\n", brightness);
    FILE* brightness_file = fopen(BACKLIGHT_PATH_BASE "brightness", "w");
    if(!brightness_file) {
        perror("Failed to open brightness file");
        return EXIT_FAILURE;
    }
    fprintf(brightness_file, "%d", brightness);
    return 0;
}

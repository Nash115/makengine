#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../include/configuration.h"

bool confFileExists(char *path, char *cwd) {
    chdir(path);

    FILE *file = fopen(DEFAULT_CONF_FILE, "r");
    if (file) {
        fclose(file);

        chdir(cwd);
        return true;
    }

    chdir(cwd);
    return false;
}

bool loadSettingsFromConfFile(settings_t *settings_t, int *nbConfRead, char *path, char *cwd) {
    chdir(path);

    FILE *file = fopen(DEFAULT_CONF_FILE, "r");
    if (file) {
        char line[MAX_PATH];
        while (fgets(line, sizeof(line), file)) {
            int value;
            if (strstr(line, CONF_SETTING_NO_CLEAN) != NULL) {
                sscanf(line, "%*[^=]=%d", &value);
                if (value != 0 && value != 1 && value != -1) {
                    printf(COLOR_ERROR "Error: Invalid value for setting_no_clean. Must be 0, 1, or -1. Read value: %d\n" COLOR_RESET, value);
                } else {
                    *nbConfRead += 1;
                    if (value != -1) {
                        settings_t->no_clean.value = value;
                    }
                }
            } else if (strstr(line, CONF_SETTING_NO_EXEC) != NULL) {
                sscanf(line, "%*[^=]=%d", &value);
                if (value != 0 && value != 1 && value != -1) {
                    printf(COLOR_ERROR "Error: Invalid value for setting_no_exec. Must be 0, 1, or -1. Read value: %d\n" COLOR_RESET, value);
                } else {
                    *nbConfRead += 1;
                    if (value != -1) {
                        settings_t->no_exec.value = value;
                    }
                }
            }
        }
        fclose(file);
        chdir(cwd);
        return true;
    }

    chdir(cwd);
    return false;
}

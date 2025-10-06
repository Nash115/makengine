#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/settings.h"
#include "../include/arguments.h"

void setSettingInt(setting_int_t *setting, int value) {
    (*setting).value = value;
}

void setSettingStr(setting_str_t *setting, const char *value) {
    if (value != NULL) {
        strncpy((*setting).value, value, sizeof((*setting).value) - 1);
        (*setting).value[sizeof((*setting).value) - 1] = '\0';
    } else {
        (*setting).value[0] = '\0';
    }
}

settings_t initsettings(void) {
    settings_t settings;

    setSettingInt(&settings.no_clean, 0);
    setSettingInt(&settings.no_exec, 0);
    setSettingStr(&settings.init_main_name, INIT_MAIN_NAME_DEFAULT);
    setSettingStr(&settings.make_args, "");
    setSettingStr(&settings.exec_args, "");
    setSettingInt(&settings.clear_terminal, 0);

    return settings;
}

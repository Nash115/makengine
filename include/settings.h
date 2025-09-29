#ifndef SETTINGS_H
#define SETTINGS_H

#include "constantes.h"

typedef struct SettingInt {
    int value;
} setting_int_t;

typedef struct SettingStr {
    char value[MAX_PATH];
} setting_str_t;

typedef struct Settings {
    setting_int_t no_clean;
    setting_int_t no_exec;
    setting_str_t init_main_name;
    setting_str_t make_args;
    setting_str_t exec_args;
} settings_t;

void setSettingInt(setting_int_t *setting, int value);
void setSettingStr(setting_str_t *setting, const char *value);
settings_t initsettings(void);

#endif // SETTINGS_H

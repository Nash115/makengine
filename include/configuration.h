#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdbool.h>

#include "settings.h"

#define DEFAULT_CONF_FILE "makengine.conf"

#define CONF_SETTING_NO_CLEAN "setting_no_clean"
#define CONF_SETTING_NO_EXEC "setting_no_exec"

bool confFileExists(char *path, char *cwd);
bool loadSettingsFromConfFile(settings_t *settings_t, int *nbConfRead, char *path, char *cwd);

#endif // CONFIGURATION_H

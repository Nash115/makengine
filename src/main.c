#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/constantes.h"
#include "../include/types.h"
#include "../include/warnings.h"
#include "../include/utils.h"
#include "../include/version.h"
#include "../include/compilation.h"
#include "../include/arguments.h"

int main(int argc, char **argv) {
    char cwd[MAX_PATH];

    settings_t setting_no_clean = { .value = 0 };
    settings_t setting_no_exec = { .value = 0 };
    settings_t setting_init_main_name = { .value_str = INIT_MAIN_NAME_DEFAULT };

    checkWarnings();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], VERSION_ARG) == 0 || strcmp(argv[i], VERSION_SHORT_ARG) == 0) {
            handleVersion();
            return 0;
        } else if (strcmp(argv[i], HELP_ARG) == 0 || strcmp(argv[i], HELP_SHORT_ARG) == 0 || strcmp(argv[i], "help") == 0) {
            handleHelp();
            return 0;
        } else if (strcmp(argv[i], NO_CLEAN_ARG) == 0 || strcmp(argv[i], NO_CLEAN_SHORT_ARG) == 0) {
            setting_no_clean.value = 1;
            argv[i] = NULL;
        } else if (strcmp(argv[i], NO_EXEC_ARG) == 0 || strcmp(argv[i], NO_EXEC_SHORT_ARG) == 0) {
            setting_no_exec.value = 1;
            setting_no_clean.value = 1;
            argv[i] = NULL;
        } else if (strcmp(argv[i], FORCE_CLEAN_ARG) == 0 || strcmp(argv[i], FORCE_CLEAN_SHORT_ARG) == 0) {
            setting_no_clean.value = 0;
            argv[i] = NULL;
        } else if (strcmp(argv[i], INIT_MAIN_NAME_ARG) == 0 || strcmp(argv[i], INIT_MAIN_NAME_SHORT_ARG) == 0) {
            if (i + 1 < argc) {
                strcpy(setting_init_main_name.value_str, argv[i + 1]);
                argv[i] = NULL;
                argv[i + 1] = NULL;
                i++;
            } else {
                printf(COLOR_ERROR "Error: Missing argument for %s\n" COLOR_RESET, argv[i]);
                fflush(stdout);
                return 1;
            }
        }
    }

    printf(COLOR_PRIMARY "🚀 WELCOME ! makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf(COLOR_ERROR "Error: Unable to get current working directory\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) continue;
        
        if (strcmp(argv[i], UPDATE_CMD) == 0) {
            handleUpdate(cwd, setting_no_clean);
            return 0;
        } else if (strcmp(argv[i], INIT_CMD) == 0) {
            handleInit(setting_init_main_name);
            return 0;
        } else if (isCfile(argv[i])) {
            handleCFile(argv[i], setting_no_clean, setting_no_exec);
            return 0;
        } else if (isValidPath(argv[i])) {
            handlePath(argv[i], cwd, argc, argv, setting_no_clean, setting_no_exec);
            return 0;
        } else {
            printf(COLOR_WARNING "Error: Invalid argument %s. Skipped.\n" COLOR_RESET, argv[i]);
            fflush(stdout);
        }
    }

    handleMakefile(argc, argv, setting_no_clean, setting_no_exec);

    return 0;
}

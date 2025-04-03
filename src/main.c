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
    
    char action[MAX_PATH] = "make";

    settings_t setting_no_clean = { .value = 0 };
    settings_t setting_no_exec = { .value = 0 };
    settings_t setting_init_main_name = { .value_str = INIT_MAIN_NAME_DEFAULT };
    
    char path_value[MAX_PATH] = ".";
    char cfile_value[MAX_PATH] = { 0 };

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
        
        else if (isCfile(argv[i])) {
            strcpy(cfile_value, argv[i]);
            argv[i] = NULL;
            strcpy(action, "compile:c");
        } else if (isValidPath(argv[i])) {
            strcpy(path_value, argv[i]);
            argv[i] = NULL;
        }
        
        else if (strcmp(argv[i], INIT_CMD) == 0) {
            strcpy(action, "init");
        } else if (strcmp(argv[i], UPDATE_CMD) == 0) {
            strcpy(action, "update");
        }

        else {
            printf(COLOR_WARNING "Error: Invalid argument %s. Skipped.\n" COLOR_RESET, argv[i]);
            fflush(stdout);
        }
    }

    printf(COLOR_PRIMARY "🚀 WELCOME ! makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf(COLOR_ERROR "Error: Unable to get current working directory\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }

    if (strcmp(action, "make") == 0) {
        handlePath(path_value, cwd, argc, argv, setting_no_clean, setting_no_exec);
    } else if(strcmp(action, "compile:c") == 0) {
        handleCFile(cfile_value, setting_no_clean, setting_no_exec);
    } else if (strcmp(action, "init") == 0) {
        handleInit(path_value, cwd, setting_init_main_name);
    } else if (strcmp(action, "update") == 0) {
        handleUpdate(cwd, setting_no_clean);
    } else {
        printf(COLOR_ERROR "Error: Unknown action %s\n" COLOR_RESET, action);
        fflush(stdout);
        return 1;
    }

    return 0;
}

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
        } else if (isCfile(argv[i])) {
            handleCFile(argv[i], setting_no_clean);
        } else if (isValidPath(argv[i])) {
            handlePath(argv[i], cwd, argc, argv, setting_no_clean);
        } else {
            handleMakefile(argc, argv, setting_no_clean);
        }
    }

    return 0;
}

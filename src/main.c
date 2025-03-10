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

int main(int argc, char **argv) {
    char cwd[MAX_PATH];

    settings_t setting_no_clean;
    setting_no_clean.value = 0;

    checkWarnings();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            handleVersion();
            return 0;
        } else if (strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "--no-clean") == 0) {
            setting_no_clean.value = 1;
        }
    }

    printf(COLOR_PRIMARY "🚀 WELCOME ! makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf(COLOR_ERROR "Error: Unable to get current working directory\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }

    if (argc <= 1) {
        handleMakefile(argc, argv, setting_no_clean);
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "version") == 0) {
        handleVersion();
    } else if (strcmp(argv[1], "update") == 0) {
        handleUpdate(cwd, setting_no_clean);
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0) {
        handleHelp();
    } else if (isCfile(argv[1])) {
        handleCFile(argv[1], setting_no_clean);
    } else if (isValidPath(argv[1])) {
        handlePath(argv[1], cwd, argc, argv, setting_no_clean);
    } else {
        printf(COLOR_ERROR "Unable to recognize command\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    return 0;
}

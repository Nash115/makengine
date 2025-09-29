#include <stdio.h>
#include <stdlib.h>
#include "../include/warnings.h"
#include "../include/constantes.h"

void checkWarnings(void) {
    char *repo_path = getenv("MAKENGINE_REPO_PATH");
    if (repo_path == NULL) {
        printf(COLOR_WARNING "Warning: Environment variable MAKENGINE_REPO_PATH is not set\n" COLOR_RESET);
        fflush(stdout);
    }
}

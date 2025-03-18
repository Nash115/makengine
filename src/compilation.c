#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "../include/compilation.h"
#include "../include/constantes.h"
#include "../include/version.h"
#include "../include/types.h"
#include "../include/utils.h"

int compileC(char *path) {
    char command[MAX_PATH] = "";
    path[strlen(path) - 2] = '\0';
    strcat(command, "gcc ");
    strcat(command, path);
    strcat(command, ".c -o ");
    strcat(command, path);
    int r = system(command);
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    return 0;
}

int handlePath(char *path, char *cwd, int argc, char **argv, settings_t setting_no_clean, settings_t setting_no_exec) {
    chdir(path);

    int r = handleMakefile(argc, argv, setting_no_clean, setting_no_exec);

    chdir(cwd);
    return r;
}

int handleUpdate(char cwd[MAX_PATH], settings_t setting_no_clean) {
    char *repo_path = getenv("MAKENGINE_REPO_PATH");
    if (repo_path == NULL) {
        printf(COLOR_ERROR "Error: Environment variable MAKENGINE_REPO_PATH is not set\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }

    if (chdir(repo_path) != 0) {
        printf(COLOR_ERROR "Error: Unable to change directory to %s\n" COLOR_RESET, repo_path);
        fflush(stdout);
        return 1;
    }

    printf(COLOR_PRIMARY "makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);
    printf(COLOR_PRIMARY "Compiling . . .\n" COLOR_RESET);
    fflush(stdout);
    printf(COLOR_SECONDARY);
    fflush(stdout);
    int r = system("make");
    printf(COLOR_RESET);
    fflush(stdout);
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
        fflush(stdout);
        printf(COLOR_WARNING "Update Aborted\n" COLOR_RESET);
        chdir(cwd);
        return 1;
    } else {
        printf(COLOR_OK "Compiled successfully.\n" COLOR_RESET);
        fflush(stdout);
        printf("Updated version :\n");
        fflush(stdout);
        int r2 = system("./makengine --version");
        if (r2 != 0) {
            printf(COLOR_WARNING "Update available but unable to show version\n" COLOR_RESET);
            fflush(stdout);
        }
        chdir(cwd);
    }

    if (! setting_no_clean.value) {
        printf(COLOR_SECONDARY);
        fflush(stdout);
        int r3 = system("make clean");
        printf(COLOR_RESET);
        fflush(stdout);
        if (r3 != 0) {
            printf(COLOR_ERROR "Error: Unable to clean\n" COLOR_RESET);
            fflush(stdout);
            return r3;
        }
    }
    return r;
}

int handleCFile(char *path, settings_t setting_no_clean, settings_t setting_no_exec) {
    if (compileC(path) == 0) {
        if (setting_no_exec.value) {
            printf(COLOR_OK "Compiled successfully. Not executing...\n" COLOR_RESET);
            fflush(stdout);
        } else {
            printf(COLOR_PRIMARY "Compiled successfully. Executing...\n" COLOR_RESET);
            fflush(stdout);
            clock_t start = clock();
            int r = execute(path);
            clock_t end = clock();
            reportAfterExec(r, interval(start, end));
        }
        if (! setting_no_clean.value) {
            char command[MAX_PATH] = "rm -f ";
            strcat(command, path);
            printf(COLOR_SECONDARY);
            fflush(stdout);
            printf("%s\n", command);
            printf(COLOR_RESET);
            fflush(stdout);
            int r2 = system(command);
            if (r2 != 0) {
                printf(COLOR_ERROR "Error: Unable to remove\n" COLOR_RESET);
                fflush(stdout);
            }
        }
        return 0;
    } else {
        printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
}

int getOutputName(char output_name[MAX_PATH]) {
    FILE *file;
    char line[MAX_PATH];
    file = fopen("makefile", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier makefile pour lecture");
        output_name = "main";
        fclose(file);
        return 0;
    }
    if (fgets(line, sizeof(line), file) != NULL) {
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == ':') {
                line[i] = '\0';
                break;
            }
        }
        strcpy(output_name, line);
    } else {
        perror("Erreur lors de la lecture de la ligne du fichier makefile");
        output_name = "main";
        fclose(file);
        return 0;
    }

    fclose(file);

    return 1;
}

int handleMakefile(int argc, char **argv, settings_t setting_no_clean, settings_t setting_no_exec) {
    if (access("makefile", F_OK) != -1) {
        printf(COLOR_SECONDARY);
        fflush(stdout);
        int r1 = system("make");
        printf(COLOR_RESET);
        fflush(stdout);
        if (r1 != 0) {
            printf(COLOR_ERROR "Error: Unable to make\n" COLOR_RESET);
            fflush(stdout);
            return r1;
        } else {
            if (setting_no_exec.value) {
                printf(COLOR_OK "Made successfully. Not executing...\n" COLOR_RESET);
                fflush(stdout);
            } else {
                printf(COLOR_OK "Made successfully. Executing...\n" COLOR_RESET);
                fflush(stdout);
                char path[MAX_PATH];
                char output_name[MAX_PATH];
                if (getOutputName(output_name) == 0) {
                    printf(COLOR_ERROR "Error: Unable to get output name\n" COLOR_RESET);
                    fflush(stdout);
                    return 1;
                }
                sprintf(path, "%s", output_name);
                clock_t start = clock();
                int r2 = execute(path);
                clock_t end = clock();
                reportAfterExec(r2, interval(start, end));
            }
            if (! setting_no_clean.value) {
                printf(COLOR_SECONDARY);
                fflush(stdout);
                int r3 = system("make clean");
                printf(COLOR_RESET);
                fflush(stdout);
                if (r3 != 0) {
                    printf(COLOR_ERROR "Error: Unable to clean\n" COLOR_RESET);
                    fflush(stdout);
                    return r3;
                }
            }
            return 0;
        }
    } else {
        printf(COLOR_WARNING "No makefile found in the directory\n" COLOR_RESET);
        fflush(stdout);
        printUsage(argv[0]);
        return 1;
    }
}

int execute(char *path) {
    char command[MAX_PATH];
    sprintf(command, "./%s", path);
    fflush(stdout);
    int r = system(command);
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to execute\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define VERSION "v1.4.5"
#define COMP_DATE __DATE__ " " __TIME__ 

#define MAX_PATH 256

#define COLOR_PRIMARY "\033[1;34m"
#define COLOR_SECONDARY "\033[1;35m"
#define COLOR_OK "\033[1;32m"
#define COLOR_ERROR "\033[1;31m"
#define COLOR_WARNING "\033[1;33m"
#define COLOR_RESET "\033[0m"

int setting_no_clean = 0;

int change_dir(char *path);
int isValidPath(char *path);
int isCfile(char *path);
int compileC(char *path);
int execute(char *path);
void reportAfterExec(int exitCode, double time);
double interval(clock_t start, clock_t end);
void printUsage(char *programName);
int handleMakefile(int argc, char **argv);
void handleVersion();
int handleUpdate();
void handleHelp();
int handleCFile(char *path);
int handlePath(char *path, char *cwd, int argc, char **argv);

int main(int argc, char **argv) {
    char cwd[MAX_PATH];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            handleVersion();
            return 0;
        } else if (strcmp(argv[i], "-nc") == 0 || strcmp(argv[i], "--no-clean") == 0) {
            setting_no_clean = 1;
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
        handleMakefile(argc, argv);
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "version") == 0) {
        handleVersion();
    } else if (strcmp(argv[1], "update") == 0) {
        handleUpdate();
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0) {
        handleHelp();
    } else if (isCfile(argv[1])) {
        handleCFile(argv[1]);
    } else if (isValidPath(argv[1])) {
        handlePath(argv[1], cwd, argc, argv);
    } else {
        printf(COLOR_ERROR "Unable to recognize command\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    return 0;
}

int handleMakefile(int argc, char **argv) {
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
            printf(COLOR_OK "Made successfully. Executing...\n" COLOR_RESET);
            fflush(stdout);
            char path[MAX_PATH];
            sprintf(path, "main");
            clock_t start = clock();
            int r2 = execute(path);
            clock_t end = clock();
            reportAfterExec(r2, interval(start, end));
            if (! setting_no_clean) {
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
            return r2;
        }
    } else {
        printf(COLOR_WARNING "No makefile found in the directory\n" COLOR_RESET);
        fflush(stdout);
        printUsage(argv[0]);
        return 1;
    }
}

void handleVersion() {
    printf(COLOR_PRIMARY "makengine - " VERSION " - " COMP_DATE "\n" COLOR_RESET);
    fflush(stdout);
}

int handleUpdate() {
    printf(COLOR_PRIMARY "makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);
    printf(COLOR_PRIMARY "Compiling . . .\n" COLOR_RESET);
    fflush(stdout);
    int r = system("gcc main.c -o makengine");
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
        fflush(stdout);
        printf(COLOR_WARNING "Update Aborted\n" COLOR_RESET);
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
        return 0;
    }
}

void handleHelp() {
    printf("### Makengine - available commands: ###\n");
    printf("* No command\tMake (using the makefile) and execute (`main` exec) the program in the current directory (and then clean)\n");
    printf("* -v, --version, version\tShow version information\n");
    printf("* -h, --help, help\tShow help information\n");
    printf("* update\tUpdate makengine (need to be in the makengine's repo directory)\n");
    printf("* <path>\tMake (using the makefile) and execute (`main` exec) the program in the path (and then clean)\n");
    printf("* <c file>\tCompile and execute the c file using gcc\n");
    fflush(stdout);
}

int handleCFile(char *path) {
    if (compileC(path) == 0) {
        printf(COLOR_PRIMARY "Compiled successfully. Executing...\n" COLOR_RESET);
        fflush(stdout);
        clock_t start = clock();
        int r = execute(path);
        clock_t end = clock();
        reportAfterExec(r, interval(start, end));
        if (! setting_no_clean) {
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
        return r;
    } else {
        printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
}

int handlePath(char *path, char *cwd, int argc, char **argv) {
    change_dir(path);

    int r = handleMakefile(argc, argv);

    change_dir(cwd);
    return r;
}

void printUsage(char *programName) {
    printf(COLOR_ERROR "Usage: %s <command / path / c file> ...\n" COLOR_RESET, programName);
    printf("Try '%s --help' for more information.\n", programName);
    fflush(stdout);
}

int change_dir(char *path) {
    if (chdir(path) != 0) {
        perror("Unable to change directory");
        return 1;
    }
    return 0;
}

int isValidPath(char *path) {
    if (access(path, F_OK) != -1) {
        return 1;
    } else {
        return 0;
    }
}

int isCfile(char *path) {
    if (strstr(path, ".c") != NULL) {
        return 1;
    } else {
        return 0;
    }
}

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

void reportAfterExec(int exitCode, double time) {
    printf(COLOR_PRIMARY "-------------------------------------\n" COLOR_RESET);
    fflush(stdout);
    if (exitCode == 0) {
        printf(COLOR_PRIMARY "program exited with code " COLOR_OK "%d\n" COLOR_RESET, exitCode);
        fflush(stdout);
    } else {
        printf(COLOR_PRIMARY "program exited with code " COLOR_ERROR "%d\n" COLOR_RESET, exitCode);
        fflush(stdout);
    }
    printf(COLOR_PRIMARY "execution time: " COLOR_SECONDARY "%.2fms\n" COLOR_RESET, time);
    fflush(stdout);
    printf(COLOR_PRIMARY "-------------------------------------\n" COLOR_RESET);
    fflush(stdout);
}

double interval(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC * 1000;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/version.h"

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

double interval(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC * 1000;
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

void handleVersion() {
    printf(COLOR_PRIMARY "makengine - " VERSION " - " COMP_DATE "\n" COLOR_RESET);
    fflush(stdout);
}

void printUsage(char *programName) {
    printf(COLOR_ERROR "Usage: %s <command / path / c file> ...\n" COLOR_RESET, programName);
    printf("Try '%s --help' for more information.\n", programName);
    fflush(stdout);
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
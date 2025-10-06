#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/version.h"
#include "../include/arguments.h"

void handleHelp() {
    printf(COLOR_PRIMARY "#" COLOR_OK "#" COLOR_SECONDARY "#" COLOR_RESET " Makengine " COLOR_WARNING "-" COLOR_RESET " help " COLOR_SECONDARY "#" COLOR_OK "#" COLOR_PRIMARY "#" COLOR_RESET"\n");
    printf("\n");
    printf(COLOR_PRIMARY "Available usages:\n\n" COLOR_RESET);
    printf("\tNo command\t\tMake (using the makefile) and execute the program in the current directory (and then clean)\n\n");
    printf("\t" UPDATE_CMD "\t\t\tUpdate makengine (need to be in the makengine's repo directory)\n\n");
    printf("\t<path>\t\t\tMoves to the specified path, makes (using the `makefile`), and executes the program (and then cleans and returns to the initial working directory).\n\n");
    printf("\t<c file>\t\tCompile and execute the c file using gcc\n\n");
    printf("\t" INIT_CMD " <path (optn*)>\tInitialize a new `makefile` and a new `c` file in the specified (or current) path\n\n");
    printf(COLOR_SECONDARY "Available options:\n\n" COLOR_RESET);
    printf("\t" VERSION_SHORT_ARG ", " VERSION_ARG "\t\tShow version information\n\n");
    printf("\t" HELP_SHORT_ARG ", " HELP_ARG "\t\tShow help information\n\n");
    printf("\t" NO_CLEAN_SHORT_ARG ", " NO_CLEAN_ARG "\t\tDon't clean the files after execution\n\n");
    printf("\t" NO_EXEC_SHORT_ARG ", " NO_EXEC_ARG "\t\tDon't execute the program after compilation\n\n");
    printf("\t" FORCE_CLEAN_SHORT_ARG ", " FORCE_CLEAN_ARG "\tForce clean the files after execution\n\n");
    printf("\t" INIT_MAIN_NAME_SHORT_ARG " [ name ]\t\tPersonalize the main file name (default : " INIT_MAIN_NAME_DEFAULT ")\n\t" INIT_MAIN_NAME_ARG " [ name ]\n\n");
    printf("\t" MAKE_ARGS_ARG " [ args ]\tPass args to make\n\n");
    printf("\t" EXEC_ARGS_ARG " [ args ]\tPass args to the executable\n\n");
    printf("\t" CLEAR_TERMINAL_SHORT_ARG ", " CLEAR_TERMINAL_ARG "\tClear the terminal before each execution\n\n");
    printf("The (optn*) options are optional.\n");
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
    printf("Try '%s " HELP_ARG "' for more information.\n", programName);
    fflush(stdout);
}

int isValidPath(char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
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

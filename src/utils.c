#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/utils.h"
#include "../include/constantes.h"
#include "../include/version.h"

void handleHelp() {
    printf(COLOR_PRIMARY "#" COLOR_OK "#" COLOR_SECONDARY "#" COLOR_RESET " Makengine " COLOR_WARNING "-" COLOR_RESET " help " COLOR_SECONDARY "#" COLOR_OK "#" COLOR_PRIMARY "#" COLOR_RESET"\n");
    printf("\n");
    printf(COLOR_PRIMARY "Available usages:\n\n" COLOR_RESET);
    printf("\tNo command\t\tMake (using the makefile) and execute (`main` exec) the program in the current directory (and then clean)\n\n");
    printf("\tupdate\t\t\tUpdate makengine (need to be in the makengine's repo directory)\n\n");
    printf("\t<path>\t\t\tMake (using the makefile) and execute (`main` exec) the program in the path (and then clean)\n\n");
    printf("\t<c file>\t\tCompile and execute the c file using gcc\n\n");
    printf("\tinit <path (optn*)>\tInitialize a new `makefile` and a new `c` file in the specified (or current) path\n\n");
    printf(COLOR_SECONDARY "Available options:\n\n" COLOR_RESET);
    printf("\t-v, --version\t\tShow version information\n\n");
    printf("\t-h, --help\t\tShow help information\n\n");
    printf("\t-nc, --no-clean\t\tDon't clean the files after execution\n\n");
    printf("\t-ne, --no-exec\t\tDon't execute the program after compilation\n\n");
    printf("\t-fc, --force-clean\tForce clean the files after execution\n\n");
    printf("\t-ifn [ name ]\t\tForce clean the files after execution\n\t--init-file-name [ name ]\n\n");
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
    printf("Try '%s --help' for more information.\n", programName);
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
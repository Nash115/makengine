#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define VERSION "v1.4.2"
#define COMP_DATE __DATE__ " " __TIME__ 

#define MAX_PATH 256

#define COLOR_PRIMARY "\033[1;34m"
#define COLOR_SECONDARY "\033[1;35m"
#define COLOR_OK "\033[1;32m"
#define COLOR_ERROR "\033[1;31m"
#define COLOR_WARNING "\033[1;33m"
#define COLOR_RESET "\033[0m"

int change_dir(char *path);
int isValidPath(char *path);
int make(char *path);
int makeClean(char *path);
int isCfile(char *path);
int compileC(char *path);
int execute(char *path);
void reportAfterExec(int exitCode, double time);
double interval(clock_t start, clock_t end);

int main(int argc, char **argv) {
    printf(COLOR_PRIMARY "🚀 WELCOME ! makengine - " VERSION "\n" COLOR_RESET);
    fflush(stdout);

    if (argc <= 1) {
        if (access("makefile", F_OK) != -1) {
            printf(COLOR_OK "Makefile found in the current directory !\n" COLOR_RESET);
            fflush(stdout);
            int r1 = system("make");
            printf(COLOR_RESET);
            fflush(stdout);
            if (r1 != 0) {
                printf(COLOR_ERROR "Error: Unable to make\n" COLOR_RESET);
                fflush(stdout);
                return r1;
            }
            else
            {
                printf(COLOR_OK "Made successfully. Executing...\n" COLOR_RESET);
                fflush(stdout);
                char path[MAX_PATH];
                sprintf(path, "main");
                float start = clock();
                int r2 = execute(path);
                float end = clock();
                reportAfterExec(r2, interval(start, end));
                printf(COLOR_SECONDARY);
                fflush(stdout);
                int r3 = system("make clean");
                printf(COLOR_RESET);
                fflush(stdout);
                if (r3 != 0) {
                    printf(COLOR_ERROR "Error: Unable to clean\n" COLOR_RESET);
                    fflush(stdout);
                    return 1;
                }
                return r2;
            }
        } else {
            printf(COLOR_WARNING "No makefile found in the current directory\n" COLOR_RESET);
            fflush(stdout);
            printf(COLOR_ERROR "Usage: %s <command / path / c file> ...\n" COLOR_RESET, argv[0]);
            printf("Try '%s --help' for more information.\n", argv[0]);
            fflush(stdout);
            return 1;
        }
    }

    if (strcmp(argv[1], "-v") == 0  || strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "version") == 0)
    {
        printf(COLOR_PRIMARY "makengine - " VERSION " - " COMP_DATE "\n" COLOR_RESET);
        fflush(stdout);
    }
    else if (strcmp(argv[1], "update") == 0)
    {
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
            return 0;
        }
    }
    else if (strcmp(argv[1], "-h") == 0  || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0)
    {
        printf("### Makengine - available commands: ###\n");
        printf("* No command: Make (using the makefile) and execute (`main` exec) the program in the current directory (and then clear)\n");
        printf("* -v, --version, version: Show version information\n");
        printf("* -h, --help, help: Show help information\n");
        printf("* update: Update makengine (need the source code into `makengine_project` folder)\n");
        printf("* <path>: Make (using the makefile) and execute (`main` exec) the program in the path (and then clear)\n");
        printf("* <c file>: Compile and execute the c file using gcc\n");
        fflush(stdout);
    }
    else if (isCfile(argv[1]))
    {
        if (compileC(argv[1]) == 0)
        {
            printf(COLOR_PRIMARY "Compiled successfully. Executing...\n" COLOR_RESET);
            fflush(stdout);
            float start = clock();
            int r = execute(argv[1]);
            float end = clock();
            reportAfterExec(r, interval(start, end));
            return r;
        } else {
            printf(COLOR_ERROR "Error: Unable to compile\n" COLOR_RESET);
            fflush(stdout);
            return 1;
        }
    }
    else if (isValidPath(argv[1]))
    {
        if (make(argv[1]) == 0)
        {
            printf(COLOR_OK "Made successfully. Executing...\n" COLOR_RESET);
            fflush(stdout);
            char path[MAX_PATH];
            sprintf(path, "%s/main", argv[1]);
            float start = clock();
            int r = execute(path);
            float end = clock();
            reportAfterExec(r, interval(start, end));
            makeClean(argv[1]);
            return r;
        } else {
            printf(COLOR_ERROR "Error: Unable to make\n" COLOR_RESET);
            fflush(stdout);
            return 1;
        }
    }
    else
    {
        printf(COLOR_ERROR "Unable to recognize command\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    return 0;
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

int make(char *path) {
    change_dir(path);
    printf(COLOR_SECONDARY);
    fflush(stdout);
    int r = system("make");
    printf(COLOR_RESET);
    fflush(stdout);
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to make\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    int depth = 0;
    for (char *p = path; *p; p++) {
        if (*p == '/') {
            depth++;
        }
    }
    for (int i = 0; i <= depth; i++) {
        change_dir("..");
    }
    return 0;
}

int makeClean(char *path) {
    change_dir(path);
    printf(COLOR_SECONDARY);
    fflush(stdout);
    int r = system("make clean");
    printf(COLOR_RESET);
    fflush(stdout);
    if (r != 0) {
        printf(COLOR_ERROR "Error: Unable to clean\n" COLOR_RESET);
        fflush(stdout);
        return 1;
    }
    int depth = 0;
    for (char *p = path; *p; p++) {
        if (*p == '/') {
            depth++;
        }
    }
    for (int i = 0; i <= depth; i++) {
        change_dir("..");
    }
    return 0;
}

int isCfile(char *path) {
    if (strstr(path, ".c") != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int compileC(char *path) {
    char command[MAX_PATH];
    path[strlen(path) - 2] = '\0';
    sprintf(command, "gcc %s.c -o %s", path, path);
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
#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void handleHelp();
double interval(clock_t start, clock_t end);
void reportAfterExec(int exitCode, double time);
void handleVersion();
void printUsage(char *programName);
int isValidPath(char *path);
int isCfile(char *path);

#endif // UTILS_H

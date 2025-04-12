#ifndef COMPILATION_H
#define COMPILATION_H

#include "constantes.h"
#include "settings.h"

int compileC(char *path);
int execute(char *path);
int handlePath(char *path, char *cwd, int argc, char **argv, settings_t settings);
int handleCFile(char *path, settings_t settings);
int handleMakefile(int argc, char **argv, settings_t settings);
int handleUpdate(char cwd[MAX_PATH], settings_t settings);
int getOutputName(char output_name[MAX_PATH]);
int handleInit(char *path, char *cwd, settings_t settings);

#endif // COMPILATION_H
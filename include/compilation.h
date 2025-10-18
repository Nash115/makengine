#ifndef COMPILATION_H
#define COMPILATION_H

#include "constantes.h"
#include "settings.h"

int compileC(char *path);
int execute(char *path, settings_t settings);
int handlePath(char *path, char *cwd, settings_t settings);
int handleCFile(char *path, settings_t settings);
int handleMakefile(settings_t settings);
int handleUpdate(char cwd[MAX_PATH], settings_t settings);
int getOutputName(char output_name[MAX_PATH]);
int handleInit(char *path, char *cwd, settings_t settings);
int compileJavaPackage(settings_t settings);
int executeJavaPackage(settings_t settings);
int handleJavaPackage(settings_t settings);

#endif // COMPILATION_H

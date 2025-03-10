#ifndef COMPILATION_H
#define COMPILATION_H

#include "constantes.h"
#include "types.h"

int compileC(char *path);
int execute(char *path);
int handlePath(char *path, char *cwd, int argc, char **argv, settings_t setting_no_clean);
int handleCFile(char *path, settings_t setting_no_clean);
int handleMakefile(int argc, char **argv, settings_t setting_no_clean);
int handleUpdate(char cwd[MAX_PATH], settings_t setting_no_clean);

#endif // COMPILATION_H
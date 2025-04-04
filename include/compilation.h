#ifndef COMPILATION_H
#define COMPILATION_H

#include "constantes.h"
#include "types.h"

int compileC(char *path);
int execute(char *path);
int handlePath(char *path, char *cwd, int argc, char **argv, settings_t setting_no_clean, settings_t setting_no_exec);
int handleCFile(char *path, settings_t setting_no_clean, settings_t setting_no_exec);
int handleMakefile(int argc, char **argv, settings_t setting_no_clean, settings_t setting_no_exec);
int handleUpdate(char cwd[MAX_PATH], settings_t setting_no_clean);
int getOutputName(char output_name[MAX_PATH]);
int handleInit(char *path, char *cwd, settings_t setting_init_main_name);

#endif // COMPILATION_H
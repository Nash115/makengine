<img src="/src/img/Naotech-makengine.png" alt="logo de makengine" height="90em" />

# makengine

## Overview
`makengine` is a command-line tool designed to simplify the process of compiling and executing C programs. It provides a streamlined interface for building projects using `makefile` and directly compiling single C files.

## Features
- **Automatic Makefile Execution**: If a `makefile` is present in the directory, `makengine` will automatically use it to build and execute the project.
- **Single C File Compilation**: Directly compile and execute single C files.

## Installation
To install `makengine`, clone the repository and compile the source code:
```sh
git clone https://github.com/Nash115/makengine.git
cd makengine
make
```

> [!IMPORTANT]
> If you want to use `makengine` globally, you may need to add the `makengine` directory to your `PATH` environment variable.
>
> You can do this by adding the following line to your `~/.zshrc` file (or equivalent):
>
> You also need to set the `MAKENGINE_REPO_PATH` environment variable to the `makengine` directory.
>
> Replace the `...` with the actual path to the `makengine` directory where you cloned the repository.
> ```sh
> export PATH="$HOME/.../.../makengine:$PATH"
> export MAKENGINE_REPO_PATH=$HOME/.../.../makengine
> ```

### Makengine already installed ?

If you already have `makengine` installed, you can fetch and pull the latest changes and then run:
```sh
makengine update
```

## Usage
Run `makengine` with the desired command or file path:
```sh
makengine < command / path / c file >
```

### Commands
- **No command**: Make (using the `makefile`) and execute (`main` exec) the program in the current directory (and then clear).
- **update**: Update `makengine` (needs to be in the `makengine`'s repo directory).
- **[ path ]**: Make (using the `makefile`) and execute (`main` exec) the program in the specified path (and then clear).
- **[ c file ]**: Compile and execute the C file using `gcc`.
- **init [ path (optional) ]**: Initialize a new `makefile` and a new `c` file in the specified path. If no path is provided, it will create the files in the current directory. The default name for the `c` file is `main.c` (a simple Hello World file). The `makefile` will be created with a simple template.

### Options

- **-v, --version**: Show version information.
- **-h, --help**: Show help information.
- **-nc, --no-clean**: Do not clean up the build files after execution.
- **-ne, --no-exec**: Do not execute the program after building. Using this option, `makengine` will not clean after execution. You can use `-fc` to force clean the build files.
- **-fc, --force-clean**: Force clean the build files before executing. By default `makengine` will clean after execution, but this option is useful if you want to clean the build files while you are using `-ne` option.
- **-ifn [ name ], --init-file-name [ name ]**: Set the name of the `c` file to be created when using the `init` command. The default name is `main.c`.

### Configuration file
You can create a configuration file named `makengine.conf` in any directory. By executing makengine **in this directory**, `makengine` will use the configuration file to set the default options. (They could be overridden by the command line options). The configuration file is a simple text file with the following format:

```config
# makengine configuration file

setting_no_clean = <0 or 1 (or -1 for default)> 
setting_no_exec = <0 or 1 (or -1 for default)>
```

## Examples
- To compile and run a C file:
  ```sh
  makengine example.c
  ```
- To use the `makefile` in the current directory:
  ```sh
  makengine
  ```
- To display version information:
  ```sh
  makengine --version
  ```
- To update `makengine`:
  ```sh
  makengine update
  ```

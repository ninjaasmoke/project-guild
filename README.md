# project-guild

# Build
```bash
g++ -I./dependencies -I./include main.cpp commands/*.cpp src/* -o ../project-guild-test/guild
```

## Table of Contents
- [project-guild](#project-guild)
- [Build](#build)
  - [Table of Contents](#table-of-contents)
  - [Usage (so far)](#usage-so-far)

## Usage (so far)
```bash
# create a guild project file structure in the current folder and take the name of the current folder
./guild init
```
```bash
# create a guild project file structure in the current folder and take the name of the current folder
./guild init <project-name>
```
```bash
# show the help message
./guild help
```

```bash
# build the project
./guild build
```

```bash
# run the project
./guild run
```

```bash
# add simple files to project - beta
./guild add <link>

./guild add https://raw.githubusercontent.com/ninjaasmoke/guild-sample-header-lib/refs/heads/main/StringUtils.h
```
directly adds file to `/packages` folder. need to start work on package management. OMG this is soo exciting!!!

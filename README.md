# MiniChess Project

Authors: [Adrien Jayat](https://gitlab.unistra.fr/jayat)

## Get Started

This project is using two submodules:

- the [Doxygen Awesome](https://jothepro.github.io/doxygen-awesome-css/) theme for the [Doxygen](https://www.doxygen.nl/download.html) documentation generation tool.

- the [Stockfish](https://stockfishchess.org/) chess engine.

First, clone the project and its submodules:

```sh
git clone https://gitlab.unistra.fr/jayat/minichess-project
cd minichess-project
git submodule init && git submodule update
```

### Dependencies

Install `make`, `gcc`, `doxygen` and `graphviz` with your package manager :

#### Ubuntu

```sh
sudo apt update
sudo apt install make gcc doxygen graphviz
```

#### Arch Linux

```sh
sudo pacman -Syu
sudo pacman -S make gcc doxygen graphviz
```

### Build

#### Windows

Install MinGW, CMake and make with Chocolatey, then run the following command in the project root directory:

```bash
cmake . -G "MinGW Makefiles"
```

#### Linux

```bash
cmake . -G "Unix Makefiles"
```

Then, run `make` to build the project.

To use the Stockfish engine, you need to build it with the following command:

```bash
cd Stockfish/src
make -j profile-build
```

You can also run `make docs` to generate the documentation.

Preview it with `firefox docs/html/index.html` for instance.

## How to use

After building the project, you can run the `./echecs` executable to start the program.

### Options

The program accepts the following options:

| Option | Description |
|:------ |:----------- |
| `--engine` | Black are played by the Stockfish engine.|

### Tests

To test the program, you can run the `test-level.sh` script in the `tests` directory. For example, to test the level 1, run the following command:

```bash
cd tests && bash test-level.sh 1 ../echecs
```

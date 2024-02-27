# MiniChess Project

## Get Started

This project is two submodules:

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

You can also run `make docs` to generate the documentation.

## How to use

After building the project, you can run the `./MiniChess` executable to start the program.

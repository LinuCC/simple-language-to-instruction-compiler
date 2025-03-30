# SLICC Compiler

## Introduction

SLICC (Simple Language to Instruction Compiler in C++) is a compiler that translates code written in Simple Language (Slang)—a C and Pascal-like programming language—into RISC-V machine code.

## Installation

### Linux

Install the necessary dependencies:

```bash
sudo apt update
sudo apt install cmake clang bison flex
```

### Nix-Darwin / NixOS

Use the flake in `nix-dev`.
With direnv for example add a `.envrc` with the content `use flake ./nix-dev`, run `direnv allow` and you are good to go.

### macOS

Install the Xcode Command Line Tools:

```bash
xcode-select --install
```

You may also need to install additional dependencies using Homebrew:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install cmake bison flex
```

## Building

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/LinuCC/simple-language-to-instruction-compiler.git
cd slicc
```

Build the compiler:

### Release Build

```bash
cmake . -DCMAKE_BUILD_TYPE=Release
make
```

### Debug Build

```bash
cmake . -DCMAKE_BUILD_TYPE=Debug
make
```

After a successful build, the `slicc` binary will be located in the project root.

## Running

To compile a Slang program, pipe the code into `slicc`:

```bash
cat ./examples/input.slang | ./slicc
```

## Developing

For `clangd` to work you might need to generate compile commands:

```
 cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

## Examples

Sample Slang programs can be found in the `examples` directory.

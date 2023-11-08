# asciiartgen

> c++ cli program to convert images to ascii art

 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A C++ program that takes an image file and converts it to ASCII art.

# Getting Started

## Prerequisites

- Git
- A compiler that supports C++17 such as Clang or MSVC.
- CMake 3.9 or above.

## Build Instructions

Clone the repository using Git:

```console
$ git clone https://github.com/toggysmith/asciiartgen/
```

Generate build files with CMake:

```console
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
```

Build the project using the build files:

```console
$ cmake --build build --config release
```

## Running Tests

Run tests by executing the test runner:

```console
$ ./build/test_runner
```

# Usage Example

## Getting Help With Command-Line Options

```console
$ asciiartgen --help
```

## Converting a File

```console
$ asciiartgen --input ./data/test_image.png
```

The converted file is written to stdout as ASCII art, which allows you to take advantage of IO redirection. For example, on Windows you can pipe the output to your clipboard:

```console
$ asciiartgen --input ./data/test_image.png | clip
```

## Saving to a File

```console
$ asciiartgen --input ./data/test_image.png --output ./data/ascii_art.txt
```

## Resizing the Input Image Before the Conversion

```console
$ asciiartgen --input ./data/test_image.png --size 80 60
```

This can be useful for extra large images.
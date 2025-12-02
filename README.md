# ComplexNumberLib

A CMake-based C++ library project demonstrating how to create, install, and consume custom libraries with both static and shared library configurations.

### Project Structure

```
complexNumberLib/
├── complexNumberLib-static-shared/  # Library source and build system
├── complexNumberLib-consumer/       # Example consumer application
├── generated_libs/                  # Installation directory for built libraries
└── README.md
```

### Quick Start

#### Build and Install the Library

```bash
# Build and install shared library (Release)
cd complexNumberLib-static-shared
cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=ON
cmake --build build --config Release
cmake --install build --prefix "../generated_libs/complexNumber" --config Release
```

#### Build the Consumer Application

```bash
cd complexNumberLib-consumer
cmake -B build -DCMAKE_PREFIX_PATH="../generated_libs/complexNumber" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Features

- **Dual Library Support**: Build as either static or shared library using `-DENABLE_SHARED=ON/OFF`
- **Multi-configuration**: Supports both Debug and Release builds
- **Proper Installation**: Libraries, headers, and CMake config files installed to structured directories
- **DLL Management**: Automatic DLL copying for Windows shared library consumers
- **CMake Package Configuration**: Generated config files enable easy consumption via `find_package()`

### Building All Configurations

```bash
# One-liner to build all configurations
cd complexNumberLib-static-shared
cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=OFF && cmake --build build --config Release && cmake --install build --prefix "../generated_libs/complexNumber" --config Release
# Repeat for other configurations as needed...
```

### Key Learning Points

This project demonstrates:
1. Creating export/import macros for cross-platform DLL/SO symbol visibility
2. Installing libraries with proper CMake package configuration
3. Consuming installed libraries via `find_package()`
4. Automatic DLL management for Windows shared libraries
5. Multi-configuration (Debug/Release) support

### Usage in Other Projects

After installation, consume the library in your CMake projects:

```cmake
find_package(complexNumbers REQUIRED)
target_link_libraries(your_target PRIVATE complexNumbers::complexNumbers)
```

## Detailed Build & Install cmake calls

```bash
cd complexNumberLib-static-shared

cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=ON
 && cmake --build build --config Release
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Release
```

Debug type
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SHARED=ON
 && cmake --build build --config Debug
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Debug
```

### Consumer Build

```bash
cd complexNumberLib-consumer

cmake -B build -DCMAKE_PREFIX_PATH="../generated_libs/complexNumber" -DCMAKE_BUILD_TYPE=Release
 && cmake --build build --config Release
```

### All Build

One Liner
```bash
cd complexNumberLib-static-shared

 && cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=OFF
 && cmake --build build --config Release
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Release

 && cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SHARED=OFF
 && cmake --build build --config Debug
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Debug

 && cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=ON
 && cmake --build build --config Release
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Release

 && cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SHARED=ON
 && cmake --build build --config Debug
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Debug

 && cd .. && cd complexNumberLib-consumer

 && cmake -B build -DCMAKE_PREFIX_PATH="../generated_libs/complexNumber" -DCMAKE_BUILD_TYPE=Release
 && cmake --build build --config Release

 && cmake -B build -DCMAKE_PREFIX_PATH="../generated_libs/complexNumber" -DCMAKE_BUILD_TYPE=Debug
 && cmake --build build --config Debug
```

reference: https://cfd.university/learn/automating-cfd-solver-and-library-compilation-using-cmake/how-to-compile-install-and-use-custom-libraries-with-cmake/
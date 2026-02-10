# Kafka From Scratch

A simplified implementation of Apache Kafka built from scratch in C++.

## Project Structure

- `src/`: Source code implementation (main, server, etc.)
- `include/`: Header files
- `build/`: Build directory (ignored by git)

## Build Instructions

To build the project, use CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Server

After building, run the executable:

```bash
./build/kafka
```

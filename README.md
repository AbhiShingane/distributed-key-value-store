# KVStore

A simple in-memory key-value store implemented in C++.

## Project layout

- `src/InMemoryKVstore.cpp` contains the concrete `InMemoryKVStore` implementation.
- `include/kvstore.h` defines the abstract `KVStore` interface.
- `KVStore/CMakeLists.txt` builds the project from the repository root.

## Build

From the `KVStore` directory:

```bash
cmake -S . -B build
cmake --build build
```

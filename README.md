# Distributed In-Memory Key-Value Store

A distributed, thread-safe in-memory key-value storage system implemented in **Modern C++17**. The project simulates a distributed cluster where each record is owned by a single node using hash-based partitioning. It supports concurrent access, bulk loading from CSV files, and per-node statistics collection.

---

## Features

- Thread-safe in-memory key-value store
- Distributed cluster with multiple logical nodes
- Hash-based partitioning for even record distribution
- Bulk loading from one or multiple CSV files
- Per-node operation statistics
- Modular and extensible architecture
- Modern C++17 implementation
- CMake build system

---

## Architecture

```
                          +------------------+
                          |      Loader      |
                          +------------------+
                                   |
                     Read Records / CSV Files
                                   |
                                   ▼
                          +------------------+
                          |     Cluster      |
                          +------------------+
                                   |
                          Hash-based Routing
                                   |
                    +--------------+--------------+
                    |              |              |
                    ▼              ▼              ▼
              +---------+    +---------+    +---------+
              | Node 0  |    | Node 1  |    | Node N  |
              +---------+    +---------+    +---------+
                    |              |              |
                    ▼              ▼              ▼
          +----------------+ +----------------+ +----------------+
          | InMemoryKVStore| | InMemoryKVStore| | InMemoryKVStore|
          +----------------+ +----------------+ +----------------+
                    |
                    ▼
           Thread-safe Hash Map
```

---

## Data Flow

```
                 Record (Key, Value)
                        |
                        ▼
                   Partitioner
                        |
           hash(key) % totalNodes
                        |
                        ▼
                 Owner Node Selected
                        |
                        ▼
               InMemoryKVStore
```

---

## Project Structure

```
distributed-key-value-store/
│
├── CMakeLists.txt
├── README.md
├── data/
│   ├── node1.csv
│   ├── node2.csv
│   └── node3.csv
│
├── include/
│   ├── Cluster.h
│   ├── InMemoryKVStore.h
│   ├── KVStore.h
│   ├── Loader.h
│   ├── Node.h
│   ├── Partitioner.h
│   ├── Record.h
│   └── Statistics.h
│
├── src/
│   ├── Cluster.cpp
│   ├── InMemoryKVStore.cpp
│   ├── Loader.cpp
│   ├── Node.cpp
│   ├── Partitioner.cpp
│   ├── Record.cpp
│   └── Statistics.cpp
│
└── test/
    └── main.cpp
```

---

## Components

### InMemoryKVStore

Thread-safe key-value storage implementation.

Supports:

- set()
- get()
- delete()
- exists()
- size()

Synchronization is implemented using `std::shared_mutex`.

---

### Record

Represents a key-value record.

```cpp
Record(key, value)
```

---

### Partitioner

Determines the owner node for each record.

Current partitioning strategy:

```
ownerNode = hash(key) % numberOfNodes
```

This ensures a near-even distribution of records.

---

### Node

Represents one logical storage node.

Responsibilities:

- Owns one InMemoryKVStore
- Performs CRUD operations
- Maintains operation statistics

---

### Statistics

Tracks per-node operations.

Metrics collected:

- Number of PUT operations
- Number of GET operations
- Number of DELETE operations

Implemented using atomic counters.

---

### Cluster

The central coordinator of the distributed system.

Responsibilities:

- Creates all nodes
- Routes requests to owner node
- Uses Partitioner
- Aggregates cluster statistics

Example:

```
PUT(key,value)

      │
      ▼

 Cluster

      │

Partitioner

      │

Owner Node

      │

KV Store
```

---

### Loader

Loads records into the cluster.

Supports:

- Loading individual records
- Loading from a CSV file
- Loading from multiple CSV files

Example CSV:

```
apple,fruit
car,vehicle
linux,operating system
```

---

## Thread Safety

The storage layer is thread-safe.

Synchronization uses:

- std::shared_mutex
- std::shared_lock
- std::unique_lock

Multiple readers can access the store simultaneously while writes remain exclusive.

---

## Build Instructions

### Clone

```bash
git clone https://github.com/AbhiShingane/distributed-key-value-store.git
cd distributed-key-value-store
```

### Configure

```bash
mkdir build
cd build

cmake ..
```

### Build

```bash
make
```

### Run

```bash
./kvstore_app
```

---

## Sample Output

```
========== Direct Record Loading ==========

Apple -> Fruit
Dog -> Animal
Linux -> Operating System

========== Contains ==========
Contains Apple : Yes
Contains Tiger : No

========== Delete ==========
Contains Dog : No

========== Cluster Statistics ==========

Node 0
Records : 4
Puts    : 6
Gets    : 3
Deletes : 1

Node 1
Records : 3
Puts    : 5
Gets    : 2
Deletes : 0

Total Records : 7
```

---

## Design Decisions

- Separation of concerns
- Thread-safe storage
- Smart pointer ownership
- Modular architecture
- Hash-based routing
- Easy to extend with real networking

---


## Technologies Used

- C++17
- STL
- std::unordered_map
- std::shared_mutex
- std::optional
- std::atomic
- Smart Pointers
- CMake

---
## License

This project is intended for educational and interview preparation purposes.

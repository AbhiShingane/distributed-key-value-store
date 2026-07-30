# Distributed Key-Value Store

> A configurable, schema-aware distributed key-value store implemented in modern C++.

## Overview

This project simulates a distributed key-value store with:
- Configurable cluster size
- Schema-driven record validation
- Consistent hash-based partitioning
- Mock network transport
- Record serialization/deserialization
- Thread-safe in-memory storage
- Cluster statistics and ownership verification
- Google Test unit tests
- Build/run automation scripts
- Automatic log generation

## High-Level Architecture

```text
               +----------------+
               |   config.txt   |
               +-------+--------+
                       |
                ConfigParser
                       |
                SchemaConfig
                       |
                 +-----v------+
CSV Files -----> |   Loader   |
                 +-----+------+
                       |
                    Record
                       |
                 +-----v------+
                 |  Cluster   |
                 +-----+------+
                       |
                Partitioner
                       |
             +---------+---------+
             |                   |
        NetworkMock         Serializer
             |                   |
      +------+------+------------+
      |      |      |      |
    Node0  Node1  Node2  NodeN
      |      |      |      |
      +------+------+------+
             |
      InMemoryKVStore
```

## Data Flow

```text
CSV
 │
 ▼
Loader
 │
 ▼
Schema Validation
 │
 ▼
Record
 │
 ▼
Partitioner
 │
 ▼
NetworkMock
 │
 ▼
Serializer
 │
 ▼
Destination Node
 │
 ▼
InMemoryKVStore
```

## Repository Structure

```text
distributed-key-value-store/
├── src/
├── include/
├── test/
├── data/
├── scripts/
├── build/
├── logs/
├── CMakeLists.txt
├── config.txt
└── README.md
```

### Folder Purpose

| Folder | Description |
|--------|-------------|
| src | Source implementation |
| include | Header files |
| test | Google Test unit tests |
| data | CSV input files |
| scripts | build.sh, run.sh, tests.sh, generate_data.sh |
| build | CMake build output |
| logs | Timestamped execution logs |

## Major Components

### ConfigParser
Reads configuration from `config.txt`.

Example:

```text
nodes=4
field=id,string
field=age,int32
field=score,int32
```

### SchemaConfig
Stores ordered schema and validates incoming records.

### Loader
Loads CSV files, validates rows, creates `Record` objects and sends them to the cluster.

### Record
Represents a row:
- Primary key
- Field values

### Partitioner
Maps record keys to owner nodes using:

```cpp
std::hash<std::string>{}(key) % totalNodes;
```

### Cluster
Responsible for:
- put/get/delete
- ownership verification
- network processing
- load distribution
- statistics

### NetworkMock
Simulates network communication using queues.

### Serializer
Converts `Record` ↔ byte stream.

### Node
Owns:
- InMemoryKVStore
- Statistics

### InMemoryKVStore
Thread-safe storage using `std::shared_mutex`.

## Building

Requirements

- C++17
- CMake
- GNU Make

```bash
cd scripts
./build.sh
```

## Running

```bash
./run.sh node1.csv node2.csv
```

Debug mode

```bash
./run.sh --debug node1.csv
```

## Logging

Every run creates

```text
logs/report_ddmmyyyy_hhmmss.log
```

All console output is redirected into the report.

## Data Generation

Generate CSV data:

```bash
./generate_data.sh
```

The script asks:
- Number of files
- File name
- Number of records
- Generate duplicate records (Y/N)

Generated files are placed in:

```text
data/
```

## Testing

Google Test is integrated.

Run:

```bash
./tests.sh
```

Current test suites:

- test_node.cpp
- test_cluster.cpp
- test_loader.cpp
- test_kvstore.cpp

Coverage includes:
- CRUD
- Ownership
- Loader validation
- Network processing
- Serialization
- Statistics

## Load Distribution

Cluster reports:
- Total records
- Records/node
- Ideal load
- Min/Max
- Deviation
- Balance status

## Ownership Verification

Verifies every key belongs to the correct node according to the partitioner.

## Network Statistics

Reports:
- Packets sent
- Packets received
- Pending packets
- Active queues

## Scalability

Current implementation scales by:
- Increasing node count in config
- Adding CSV files
- Hash-based partitioning
- Thread-safe storage

Future improvements:
- Replication
- Consistent hashing ring
- Virtual nodes
- Persistent storage
- TCP/gRPC networking
- Raft consensus
- Replication factor
- Rebalancing after node joins/leaves
- Compression
- Bloom filters
- WAL
- Snapshotting

## Example Execution

```text
./run.sh node1.csv node2.csv node3.csv node4.csv

Configuration Loaded
Records Loaded
Network Processing
Ownership Verification
Load Distribution
Cluster Statistics
Network Statistics
```

## Design Highlights

- Modern C++17
- RAII
- Smart pointers
- Thread-safe containers
- Modular architecture
- Separation of concerns
- Schema-driven validation
- Mock distributed networking


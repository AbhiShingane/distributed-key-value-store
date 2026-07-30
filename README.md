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



---

# Example Execution Output

The following is a sample execution of the application using four CSV files.

```text
Running with files:
/home/abhilash/project/distributed-key-value-store/data/data1.csv
/home/abhilash/project/distributed-key-value-store/data/data2.csv
/home/abhilash/project/distributed-key-value-store/data/data3.csv
/home/abhilash/project/distributed-key-value-store/data/data4.csv

========== Processing Network ==========

Network Statistics
------------------
Packets Sent      : 40
Packets Received  : 40
Packets Pending   : 0
Active Queues     : 8
Network Status    : HEALTHY

Ownership Report
----------------
Node 0 : 6 records
Node 1 : 4 records
Node 2 : 5 records
Node 3 : 4 records
Node 4 : 10 records
Node 5 : 6 records
Node 6 : 2 records
Node 7 : 3 records

Ownership Verification
----------------------
All records successfully verified.
Verification Result : PASS

Load Distribution
-----------------
Total Records      : 40
Total Nodes        : 8
Ideal / Node       : 5.00

Node      Records     Ideal       Difference
-----------------------------------------------
0         6           5.00        +1.00
1         4           5.00        -1.00
2         5           5.00        +0.00
3         4           5.00        -1.00
4         10          5.00        +5.00
5         6           5.00        +1.00
6         2           5.00        -3.00
7         3           5.00        -2.00

Minimum Records      : 2
Maximum Records      : 10
Record Difference    : 8
Max Difference       : 5.00 records
Average Difference   : 1.75 records
Overall Imbalance    : 35.00%
Allowed Difference   : ±9.00 records

Cluster Status       : BALANCED

Cluster Statistics
------------------
Node 0 : Records=6  Puts=6
Node 1 : Records=4  Puts=4
Node 2 : Records=5  Puts=5
Node 3 : Records=4  Puts=4
Node 4 : Records=10 Puts=10
Node 5 : Records=6  Puts=6
Node 6 : Records=2  Puts=2
Node 7 : Records=3  Puts=3

Total Nodes   : 8
Total Records : 40
```

## Understanding the Output

| Section | Purpose |
|---------|---------|
| Processing Network | Delivers serialized records to destination nodes. |
| Network Statistics | Displays packets sent, received, pending packets and queue health. |
| Ownership Report | Lists all records stored on each node. |
| Ownership Verification | Confirms every record resides on its correct owner node. |
| Load Distribution | Shows how evenly records are distributed across the cluster. |
| Cluster Statistics | Reports per-node CRUD statistics and total record counts. |

This sample demonstrates a healthy cluster where:
- All packets are successfully delivered.
- Ownership verification passes.
- No packets remain pending.
- The cluster is considered balanced according to the configured load-balancing policy.

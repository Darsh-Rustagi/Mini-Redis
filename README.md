# Mini Redis

> A Redis-inspired in-memory key-value database built from scratch in **Modern C++23** to explore systems programming, networking, database internals, memory management, and high-performance software design.

![C++](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20+-green)
![Docker](https://img.shields.io/badge/Docker-Enabled-blue)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

# Overview

Mini Redis is an educational implementation of an in-memory key-value database inspired by Redis.

The objective is **not to clone Redis feature-by-feature**, but to understand how an in-memory database works internally while experimenting with modern C++ features, modular software architecture, networking, and performance optimization techniques.

Instead of treating Redis as a black box, every subsystem in this project is built independently to understand:

* TCP networking
* Command parsing
* Command dispatching
* Storage engines
* Memory management
* Persistence
* Replication
* High-performance data structures
* Modern C++ design principles

As the project evolves, components will be replaceable and independently optimizable, allowing experimentation with custom allocators, advanced networking APIs, lock-free data structures, and cache-friendly algorithms.

---

# Project Goals

The primary goals of Mini Redis are:

* Learn modern systems programming using C++23.
* Understand how Redis works internally.
* Build a modular in-memory database.
* Explore database architecture from scratch.
* Experiment with performance optimizations.
* Create a clean and maintainable codebase.
* Benchmark against Redis in future development stages.

---

# Current Status

## Project Phase

**Phase 1.5 — Project Hardening**

### Completed

* TCP Server
* Client Connection Handling
* Socket Management
* Command Parser (Whitespace Parser)
* Command Dispatcher
* Storage Engine
* String Key-Value Storage
* Basic Redis-like Commands
* Configuration System
* Docker Support
* Docker Compose

### In Progress

* Logger
* Unit Testing
* CI/CD Pipeline

### Planned

* RESP Parser
* `redis-cli` Compatibility
* Persistence
* Transactions
* Replication
* Cluster Mode
* Performance Optimizations

---

# Current Features

## Networking

* TCP server using POSIX sockets.
* Multiple client connections (handled sequentially).
* Configurable listening port.
* Graceful client disconnect handling.

---

## Storage Engine

Current storage implementation uses:

* `std::unordered_map`

Supported data type:

* String

Future versions will replace or extend this implementation with more advanced data structures.

---

## Command Processing

Current pipeline:

```text
Client
    │
    ▼
TCP Server
    │
    ▼
Whitespace Command Parser
    │
    ▼
Command Dispatcher
    │
    ▼
Storage Engine
    │
    ▼
Response
```

---

## Implemented Commands

| Command | Status |
| ------- | :----: |
| SET     |    ✅   |
| GET     |    ✅   |
| DEL     |    ✅   |
| EXISTS  |    ✅   |
| INCR    |    ✅   |

---

## Current Client

Currently supported client:

* Netcat (`nc`)

Example:

```bash
nc localhost 6375
```

Future versions will support:

* `redis-cli`

through the Redis Serialization Protocol (RESP).

---

# Implemented Components

```
✓ TCP Server

✓ Socket Creation

✓ Socket Binding

✓ Listening

✓ Client Accept Loop

✓ Command Parser

✓ Command Dispatcher

✓ Storage Engine

✓ SET Command

✓ GET Command

✓ DEL Command

✓ EXISTS Command

✓ INCR Command

✓ Config System

✓ Docker

✓ Docker Compose

⬜ RESP Parser

⬜ redis-cli Compatibility

⬜ Persistence

⬜ Transactions

⬜ Replication

⬜ Cluster

⬜ Benchmarks

⬜ Custom Memory Allocator
```

---

# High-Level Architecture

```
                  +----------------------+
                  |      TCP Server      |
                  +----------+-----------+
                             |
                             ▼
                 Whitespace Command Parser
                             |
                             ▼
                  Command Dispatcher
                             |
                             ▼
                    Storage Engine
                             |
                             ▼
                  std::unordered_map
```

---

# Future Architecture

```
                        TCP Server
                             │
                             ▼
                      RESP Parser
                             │
                             ▼
                  Command Dispatcher
                             │
       +-----------+---------+----------+
       |           |                    |
       ▼           ▼                    ▼
    Strings      Hashes              Lists
       │           │                    │
       +-----------+--------------------+
                    │
                    ▼
              Storage Engine
                    │
         +----------+----------+
         |                     |
         ▼                     ▼
  Memory Manager        Persistence
                    │
                    ▼
               Replication
```

---

# Repository Structure

```
mini-redis/
│
├── docker/
│   └── Dockerfile
│
├── include/
│   ├── commands/
│   ├── config/
│   ├── memory/
│   ├── network/
│   ├── persistence/
│   ├── protocol/
│   ├── replication/
│   ├── storage/
│   └── utils/
│
├── src/
│   ├── commands/
│   ├── config/
│   ├── memory/
│   ├── network/
│   ├── persistence/
│   ├── protocol/
│   ├── replication/
│   ├── storage/
│   ├── utils/
│   ├── Server.cpp
│   └── main.cpp
│
├── tests/
│
├── benchmarks/
│
├── docs/
│
├── scripts/
│
├── docker-compose.yml
├── CMakeLists.txt
├── README.md
├── LICENSE
└── .gitignore
```

---

# Technology Stack

## Language

* Modern C++23

---

## Build System

* CMake
* Ninja

---

## Containerization

* Docker
* Docker Compose

---

## Networking

Current:

* POSIX TCP Sockets

Planned:

* epoll
* io_uring

---

## Testing

Planned:

* GoogleTest

---

## Profiling

Planned:

* AddressSanitizer
* ThreadSanitizer
* Valgrind
* perf
* heaptrack

---

# Design Philosophy

Mini Redis follows a modular architecture where every subsystem has a single responsibility.

Current separation of responsibilities:

```
Network
    ↓
Parser
    ↓
Dispatcher
    ↓
Storage
```

Because each component is independent, future improvements (RESP, persistence, custom hash tables, replication, etc.) can be added without major architectural changes.

The long-term objective is to build a clean, maintainable, and extensible codebase while learning how high-performance database systems are designed internally.

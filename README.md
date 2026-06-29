src/

Contains implementation files.

Example

Server.cpp
Storage.cpp
Parser.cpp
include/

Contains header files.

Server.hpp
Storage.hpp
Parser.hpp

Separating headers from source is standard practice in C++.

tests/

Later you'll add small programs to verify that individual components work correctly.

docker/

Stores everything needed to build the project in a reproducible environment.

docs/

Architecture diagrams and design notes.

build/

CMake generates build artifacts here.

Never edit files inside this directory manually.
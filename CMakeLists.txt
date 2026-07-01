cmake_minimum_required(VERSION 3.20)

project(MiniRedis VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini-redis
    src/main.cpp
    src/server.cpp
    src/network/TcpServer.cpp
    src/storage/StorageEngine.cpp
    src/protocol/CommandParser.cpp
    src/commands/CommandDispatcher.cpp
    src/config/config.cpp
    src/utils/logger.cpp
)

target_include_directories(mini-redis
    PRIVATE
        include
)
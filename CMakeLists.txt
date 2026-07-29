cmake_minimum_required(VERSION 3.16)
project(KVStore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(kvstore STATIC
            src/InMemoryKVstore.cpp
            src/Node.cpp
            src/Statistics.cpp
            src/loader.cpp
            src/Partitioner.cpp
            src/Cluster.cpp
            include/Record.h
            include/Datatype.h
            src/SchemaConfig.cpp
            src/ConfigParser.cpp
            src/Serializer.cpp
            src/NetworkMock.cpp
)

target_include_directories(kvstore PUBLIC include)

add_executable(kvstore_app
    test/main.cpp
)

target_link_libraries(kvstore_app PRIVATE kvstore)
target_include_directories(kvstore_app PRIVATE include)

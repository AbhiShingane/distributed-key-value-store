find_package(GTest REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    kvstore_tests

    test_main.cpp

    test_record.cpp
    test_node.cpp
    test_cluster.cpp
    test_loader.cpp
    test_kvstore.cpp
)

target_link_libraries(
    kvstore_tests

    kvstore

    GTest::gtest
    GTest::gtest_main
    pthread
)

include(GoogleTest)

gtest_discover_tests(kvstore_tests)
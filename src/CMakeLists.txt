cmake_minimum_required(VERSION 3.26.4)

add_subdirectory(TrieKeyValueStore)

add_executable("${PROJECT_NAME}Main"
    main.cpp
)

target_link_libraries("${PROJECT_NAME}Main" TrieKeyValueStoreLib)

cmake_minimum_required(VERSION 3.26.4)

add_library(TrieKeyValueStoreLib
    TrieNode.h
    TrieNodeWithValue.h
    Trie.h
    TrieNode.cpp
    TrieNodeWithValue.cpp
    Trie.cpp
    ReaderWriterLatch.h
    ReaderWriterLatch.cpp
)

target_include_directories(TrieKeyValueStoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

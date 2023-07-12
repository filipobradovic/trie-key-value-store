#include <cstdio>
#include <string>
#include <thread>
#include <bitset>

#include "Trie.h"

int main()
{
    Trie trie;
    constexpr int num_words = 1000;
    constexpr int num_bits = 10;

    std::vector<std::thread> threads;
    threads.reserve(num_words);

    auto insert_task = [&](const std::string& key, int value) {
        bool success = trie.insert(key, value);
        std::printf("%d\n", success);
    };

    for (int i = 0; i < num_words; i++) {
        std::string key = std::bitset<num_bits>(i).to_string();
        threads.emplace_back(std::thread { insert_task, key, i });
    }

    for (int i = 0; i < num_words; i++) {
        threads[i].join();
    }

    threads.clear();

    auto get_task = [&](const std::string& key, int value) {
        bool success = false;
        int tval = trie.get_value<int>(key, &success);
        std::printf("%d\n", success);
        std::printf("%d = %d\n", tval, value);
    };

    for (int i = 0; i < num_words; i++) {
        std::string key = std::bitset<num_bits>(i).to_string();
        threads.emplace_back(std::thread { get_task, key, i });
    }

    for (int i = 0; i < num_words; i++) {
        threads[i].join();
    }
    
    threads.clear();

    return 0;
}

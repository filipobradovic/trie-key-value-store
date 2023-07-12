#include <bitset>
#include <functional>
#include <gtest/gtest.h>
#include <thread>

#include "Trie.h"
#include "TrieNode.h"

TEST(TrieTest, TrieNodeInsertTest)
{
    TrieNode t('a');
    auto child_node = t.insert_child_node('b', std::make_unique<TrieNode>('b'));
    EXPECT_NE(child_node, nullptr);
    EXPECT_EQ((*child_node)->get_trie_char(), 'b');

    child_node = t.insert_child_node('b', std::make_unique<TrieNode>('b'));
    EXPECT_EQ(child_node, nullptr);

    child_node = t.insert_child_node('d', std::make_unique<TrieNode>('b'));
    EXPECT_EQ(child_node, nullptr);

    child_node = t.insert_child_node('c', std::make_unique<TrieNode>('c'));
    EXPECT_EQ((*child_node)->get_trie_char(), 'c');
}

TEST(TrieTest, TrieNodeRemoveTest)
{
    TrieNode t('a');
    auto child_node = t.insert_child_node('b', std::make_unique<TrieNode>('b'));
    child_node = t.insert_child_node('c', std::make_unique<TrieNode>('c'));

    t.remove_child_node('b');
    EXPECT_EQ(t.has_child('b'), false);
    EXPECT_EQ(t.has_children(), true);
    child_node = t.get_child_node('b');
    EXPECT_EQ(child_node, nullptr);

    t.remove_child_node('c');
    EXPECT_EQ(t.has_child('c'), false);
    EXPECT_EQ(t.has_children(), false);
    child_node = t.get_child_node('c');
    EXPECT_EQ(child_node, nullptr);
}

TEST(TrieTest, TrieInsertTest)
{
    {
        Trie trie;
        trie.insert<std::string>("abc", "d");
        bool success = true;
        auto val = trie.get_value<std::string>("abc", &success);
        EXPECT_EQ(success, true);
        EXPECT_EQ(val, "d");
    }

    {
        Trie trie;
        auto success = trie.insert<std::string>("", "d");
        EXPECT_EQ(success, false);
        trie.get_value<std::string>("", &success);
        EXPECT_EQ(success, false);
    }

    {
        Trie trie;
        bool success = trie.insert<int>("abc", 5);
        EXPECT_EQ(success, true);

        success = trie.insert<int>("abc", 6);
        EXPECT_EQ(success, false);

        auto val = trie.get_value<int>("abc", &success);
        EXPECT_EQ(success, true);
        EXPECT_EQ(val, 5);
    }

    {
        Trie trie;
        bool success = trie.insert<int>("a", 5);
        EXPECT_EQ(success, true);
        success = trie.insert<std::string>("aa", "val");
        EXPECT_EQ(success, true);

        EXPECT_EQ(trie.get_value<int>("a", &success), 5);
        EXPECT_EQ(success, true);
        EXPECT_EQ(trie.get_value<std::string>("aa", &success), "val");
        EXPECT_EQ(success, true);

        trie.get_value<int>("aaaa", &success);
        EXPECT_EQ(success, false);
    }
}

TEST(TrieTest, RemoveTest)
{
    {
        Trie trie;
        bool success = trie.insert<int>("a", 5);
        EXPECT_EQ(success, true);
        success = trie.insert<int>("aa", 6);
        EXPECT_EQ(success, true);
        success = trie.insert<int>("aaa", 7);
        EXPECT_EQ(success, true);

        success = trie.remove("aaa");
        EXPECT_EQ(success, true);
        trie.get_value<int>("aaa", &success);
        EXPECT_EQ(success, false);

        success = trie.insert("aaa", 8);
        EXPECT_EQ(success, true);
        EXPECT_EQ(trie.get_value<int>("aaa", &success), 8);
        EXPECT_EQ(success, true);

        success = trie.remove("aaaa");
        EXPECT_EQ(success, false);

        success = trie.remove("aa");
        EXPECT_EQ(success, true);
        success = trie.remove("a");
        EXPECT_EQ(success, true);
        success = trie.remove("aaa");
        EXPECT_EQ(success, true);
    }
}

TEST(TrieTest, ConcurrentTest1)
{
    Trie trie;
    constexpr int num_words = 1000;
    constexpr int num_bits = 10;

    std::vector<std::thread> threads;
    threads.reserve(num_words);

    auto insert_task = [&](const std::string& key, int value) {
        bool success = trie.insert(key, value);
        EXPECT_EQ(success, true);
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
        EXPECT_EQ(success, true);
        EXPECT_EQ(tval, value);
    };
    for (int i = 0; i < num_words; i++) {
        std::string key = std::bitset<num_bits>(i).to_string();
        threads.emplace_back(std::thread { get_task, key, i });
    }
    for (int i = 0; i < num_words; i++) {
        threads[i].join();
    }
    threads.clear();
}

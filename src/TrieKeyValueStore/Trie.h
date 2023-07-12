#pragma once

#include "Trie.h"
#include "TrieNode.h"
#include "TrieNodeWithValue.h"
#include "ReaderWriterLatch.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Trie {

public:

    Trie();

    template <typename T>
    bool insert(const std::string& key, T value)
    {
        if (key.empty()) {
            return false;
        }

        if (contains_key(key)) {
            return false;
        }

        std::unique_ptr<TrieNode>* travel_node = &m_root;
        m_latch.w_lock();

        int index = 0;
        bool node_exists = true;
        for (int i = 0; i < key.length(); i++) {
            index = i;

            if (!travel_node->get()->has_child(key[i])) {
                node_exists = false;
                break;
            }

            travel_node = travel_node->get()->get_child_node(key[i]);
        }

        if (node_exists) {
            *travel_node = std::make_unique<TrieNodeWithValue<T>>(
                std::move(*(travel_node->get())), value);
        } else {
            for (int i = index; i < key.length() - 1; i++) {
                travel_node->get()->insert_child_node(
                    key[i], std::make_unique<TrieNode>(key[i]));
                travel_node = travel_node->get()->get_child_node(key[i]);
                index = i + 1;
            }

            travel_node->get()->insert_child_node(key[index],
                std::make_unique<TrieNodeWithValue<T>>(key[index], value));
        }

        m_latch.w_unlock();
        return true;
    }

    bool remove(const std::string& key);

    template <typename T>
    T get_value(const std::string& key, bool* success)
    {
        if (key.empty()) {
            *success = false;
            return T();
        }

        std::unique_ptr<TrieNode>* tmp = get_node_ptr_for_key(key);
        m_latch.r_lock();

        if (tmp == nullptr) {
            *success = false;
            m_latch.r_unlock();
            return T();
        }

        auto* c = dynamic_cast<TrieNodeWithValue<T>*>(tmp->get());
        if (c != nullptr) {
            *success = true;
            T val = c->get_value();
            m_latch.r_unlock();
            return val;
        } else {
            *success = false;
            m_latch.r_unlock();
            return T();
        }
    }

private:
    bool contains_key(const std::string& key);
    std::unique_ptr<TrieNode>* get_node_ptr_for_key(const std::string& key);

    std::unique_ptr<TrieNode> m_root;
    ReaderWriterLatch m_latch;
};

#pragma once

#include "TrieNode.h"

template <typename T>
class TrieNodeWithValue : public TrieNode {

public:
    TrieNodeWithValue(TrieNode&& trieNode, T value)
        : TrieNode(std::move(trieNode))
        , m_value(value)
    {
        TrieNode::set_is_end_node(true);
    }

    TrieNodeWithValue(char key_char, T value)
        : TrieNode(key_char)
        , m_value(value)
    {
        TrieNode::set_is_end_node(true);
    }

    ~TrieNodeWithValue() override = default;

    T get_value() const
    {
        return m_value;
    }

private:
    T m_value;
};

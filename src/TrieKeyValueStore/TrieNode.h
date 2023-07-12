#pragma once

#include <memory>
#include <unordered_map>

class TrieNode {

public:
    explicit TrieNode(char key_char);

    TrieNode(TrieNode&& other_trie_node) noexcept;

    virtual ~TrieNode() = default;

    bool has_child(char key_char) const;

    bool has_children() const;

    bool is_end_node() const;

    char get_trie_char() const;

    std::unique_ptr<TrieNode>* insert_child_node(
        char key_char, std::unique_ptr<TrieNode>&& child);

    std::unique_ptr<TrieNode>* get_child_node(char key_char);

    void remove_child_node(char key_char);

    void set_is_end_node(bool is_end);

    int get_number_of_children();

private:
    char m_key_char;
    bool m_is_end = false;
    std::unordered_map<char, std::unique_ptr<TrieNode>> m_children;
};

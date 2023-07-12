#include "TrieNode.h"

TrieNode::TrieNode(char key_char)
    : m_key_char(key_char)
    , m_is_end(false)
{
}

TrieNode::TrieNode(TrieNode&& other_trie_node) noexcept
    : m_key_char(other_trie_node.m_key_char)
    , m_is_end(other_trie_node.m_is_end)
{
    m_children = std::move(other_trie_node.m_children);
}

bool TrieNode::has_child(char key_char) const
{
    return m_children.find(key_char) != m_children.end();
}

bool TrieNode::has_children() const
{
    return m_children.size() > 0;
}

bool TrieNode::is_end_node() const
{
    return m_is_end;
}

char TrieNode::get_trie_char() const
{
    return m_key_char;
}

std::unique_ptr<TrieNode>* TrieNode::insert_child_node(
    char key_char, std::unique_ptr<TrieNode>&& child)
{
    if (has_child(key_char)) {
        return nullptr;
    }

    if (child->m_key_char != key_char) {
        return nullptr;
    }

    m_children[key_char] = std::move(child);

    return &m_children[key_char];
}

std::unique_ptr<TrieNode>* TrieNode::get_child_node(char key_char)
{
    if (!has_child(key_char)) {
        return nullptr;
    }

    return &m_children[key_char];
}

void TrieNode::remove_child_node(char key_char)
{
    if (!has_child(key_char)) {
        return;
    }

    m_children.erase(key_char);
}

void TrieNode::set_is_end_node(bool is_end)
{
    m_is_end = is_end;
}

int TrieNode::get_number_of_children()
{
    return m_children.size();
}

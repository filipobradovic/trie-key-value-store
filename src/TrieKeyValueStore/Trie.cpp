#include "Trie.h"

Trie::Trie()
    : m_root(std::make_unique<TrieNode>('\0'))
{
}

bool Trie::remove(const std::string& key)
{
    if (key.empty()) {
        return false;
    }

    std::unique_ptr<TrieNode>* tmp = get_node_ptr_for_key(key);
    m_latch.w_lock();

    if (tmp == nullptr) {
        m_latch.w_unlock();
        return false;
    }

    if (tmp->get()->has_children()) {
        *tmp = std::make_unique<TrieNode>(std::move(*(tmp->get())));
        m_latch.w_unlock();
        return true;
    }

    std::vector<std::unique_ptr<TrieNode>*> for_deletion;
    std::unique_ptr<TrieNode>* last_end_node = &m_root;
    std::unique_ptr<TrieNode>* travel_node = &m_root;

    for (int i = 0; i < key.size() - 1; i++) {
        travel_node = travel_node->get()->get_child_node(key[i]);
        if (travel_node->get()->is_end_node()
            || travel_node->get()->get_number_of_children() > 1) {
            for_deletion.clear();
            last_end_node = travel_node;
        } else {
            for_deletion.push_back(travel_node);
        }
    }
    for_deletion.push_back(
        travel_node->get()->get_child_node(key[key.size() - 1]));

    for (int i = for_deletion.size() - 2; i >= 0; i--) {
        for_deletion[i]->get()->remove_child_node(
            for_deletion[i + 1]->get()->get_trie_char());
    }

    last_end_node->get()->remove_child_node(
        for_deletion[0]->get()->get_trie_char());

    m_latch.w_unlock();
    return true;
}

bool Trie::contains_key(const std::string& key)
{
    m_latch.w_lock();
    std::unique_ptr<TrieNode>* travel_node = &m_root;

    for (char c : key) {
        if (!travel_node->get()->has_child(c)) {
            m_latch.w_unlock();
            return false;
        }

        travel_node = travel_node->get()->get_child_node(c);
    }

    bool contains = travel_node->get()->is_end_node();
    m_latch.w_unlock();
 
    return contains;
}

std::unique_ptr<TrieNode>* Trie::get_node_ptr_for_key(const std::string& key)
{
    m_latch.w_lock();
    std::unique_ptr<TrieNode>* travel_node = &m_root;

    for (char c : key) {
        if (!travel_node->get()->has_child(c)) {
            m_latch.w_unlock();
            return nullptr;
        }

        travel_node = travel_node->get()->get_child_node(c);
    }

    m_latch.w_unlock();

    return travel_node;
}

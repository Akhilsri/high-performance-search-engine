#include "Trie.h"

Trie::Trie() {
    root = new Node();
}

void Trie::insert(const std::string& word) {
    Node* node = root;
    for (char c : word) {
        if (!node->children[c])
            node->children[c] = new Node();
        node = node->children[c];
    }
    node->isEnd = true;
}

void Trie::dfs(Node* node, std::string& path,
               std::vector<std::string>& results) const {
    if (node->isEnd) results.push_back(path);

    for (auto& p : node->children) {
        path.push_back(p.first);
        dfs(p.second, path, results);
        path.pop_back();
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) const {
    Node* node = root;
    for (char c : prefix) {
        if (!node->children.count(c)) return {};
        node = node->children.at(c);
    }

    std::vector<std::string> results;
    std::string path = prefix;
    dfs(node, path, results);
    return results;
}

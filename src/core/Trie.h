#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Trie {
private:
    struct Node {
        bool isEnd = false;
        std::unordered_map<char, Node*> children;
    };

    Node* root;

    void dfs(Node* node, std::string& path,
             std::vector<std::string>& results) const;

public:
    Trie();
    void insert(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix) const;
};

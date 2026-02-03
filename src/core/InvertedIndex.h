#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Document.h"
#include "Trie.h"

class InvertedIndex {
private:
    // word -> docId -> positions
    std::unordered_map<std::string,
        std::unordered_map<int, std::vector<int>>> index;

    int totalDocuments;
    Trie trie;

public:
    InvertedIndex();

    void addDocument(const Document& doc);

    const std::unordered_map<int, std::vector<int>>*
    getPostingList(const std::string& word) const;

    int getTotalDocuments() const;

    const std::unordered_map<std::string,
        std::unordered_map<int, std::vector<int>>>&
    getIndex() const;

    std::vector<std::string> autocomplete(const std::string& prefix) const;
};

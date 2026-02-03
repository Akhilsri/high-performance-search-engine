#include "InvertedIndex.h"
#include "Tokenizer.h"

InvertedIndex::InvertedIndex() : totalDocuments(0) {}

void InvertedIndex::addDocument(const Document& doc) {
    totalDocuments++;
    auto tokens = Tokenizer::tokenize(doc.content);

    for (int pos = 0; pos < (int)tokens.size(); pos++) {
        const std::string& word = tokens[pos];
        index[word][doc.id].push_back(pos);
        trie.insert(word);
    }
}

const std::unordered_map<int, std::vector<int>>*
InvertedIndex::getPostingList(const std::string& word) const {
    auto it = index.find(word);
    if (it == index.end()) return nullptr;
    return &it->second;
}

int InvertedIndex::getTotalDocuments() const {
    return totalDocuments;
}

const std::unordered_map<std::string,
    std::unordered_map<int, std::vector<int>>>&
InvertedIndex::getIndex() const {
    return index;
}

std::vector<std::string>
InvertedIndex::autocomplete(const std::string& prefix) const {
    return trie.autocomplete(prefix);
}

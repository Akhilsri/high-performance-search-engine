#pragma once
#include <vector>
#include <string>
#include "InvertedIndex.h"

class SearchEngine {
private:
    InvertedIndex index;

public:
    void indexDocuments(const std::vector<Document>& docs);

    std::vector<int> search(const std::string& query);
    std::vector<int> searchRanked(const std::string& query, int k);

    std::vector<int> phraseSearch(const std::string& phrase);
    std::vector<std::string> autocomplete(const std::string& prefix);
};

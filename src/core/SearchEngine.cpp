#include "SearchEngine.h"
#include "Tokenizer.h"
#include "Ranker.h"

#include <unordered_set>
#include <queue>
#include <algorithm>

void SearchEngine::indexDocuments(const std::vector<Document>& docs) {
    for (const auto& doc : docs) {
        index.addDocument(doc);
    }
}

std::vector<int> SearchEngine::search(const std::string& query) {
    auto tokens = Tokenizer::tokenize(query);
    std::unordered_set<int> result;

    for (const auto& word : tokens) {
        auto postings = index.getPostingList(word);
        if (!postings) continue;

        for (const auto& entry : *postings) {
            result.insert(entry.first);
        }
    }

    return std::vector<int>(result.begin(), result.end());
}

std::vector<int> SearchEngine::searchRanked(const std::string& query, int k) {
    auto tokens = Tokenizer::tokenize(query);
    auto scores = Ranker::computeTFIDF(
        tokens, index.getIndex(), index.getTotalDocuments()
    );

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> heap;

    for (auto& s : scores) {
        heap.push({s.second, s.first});
        if ((int)heap.size() > k) heap.pop();
    }

    std::vector<int> result;
    while (!heap.empty()) {
        result.push_back(heap.top().second);
        heap.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> SearchEngine::phraseSearch(const std::string& phrase) {
    auto tokens = Tokenizer::tokenize(phrase);
    if (tokens.empty()) return {};

    const auto& idx = index.getIndex();
    if (!idx.count(tokens[0])) return {};

    std::vector<int> results;

    for (const auto& entry : idx.at(tokens[0])) {
        int docId = entry.first;
        const std::vector<int>& posList = entry.second;

        bool match = true;

        for (int i = 1; i < (int)tokens.size(); i++) {
            if (!idx.count(tokens[i]) ||
                !idx.at(tokens[i]).count(docId)) {
                match = false;
                break;
            }

            bool found = false;
            const auto& nextPos = idx.at(tokens[i]).at(docId);

            for (int pos : posList) {
                if (std::find(nextPos.begin(),
                              nextPos.end(),
                              pos + i) != nextPos.end()) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                match = false;
                break;
            }
        }

        if (match) results.push_back(docId);
    }

    return results;
}


std::vector<std::string>
SearchEngine::autocomplete(const std::string& prefix) {
    return index.autocomplete(prefix);
}

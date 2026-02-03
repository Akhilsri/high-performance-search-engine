#include "Ranker.h"
#include <cmath>

std::unordered_map<int, double>
Ranker::computeTFIDF(
    const std::vector<std::string>& query,
    const std::unordered_map<std::string,
        std::unordered_map<int, std::vector<int>>>& index,
    int totalDocs
) {
    std::unordered_map<int, double> scores;

    for (const auto& term : query) {
        if (!index.count(term)) continue;

        int df = index.at(term).size();
        double idf = std::log((double)totalDocs / (1 + df));

        for (const auto& entry : index.at(term)) {
            int docId = entry.first;
            int tf = entry.second.size();
            scores[docId] += tf * idf;
        }
    }
    return scores;
}

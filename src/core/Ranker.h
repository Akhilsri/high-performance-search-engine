#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Ranker {
public:
    static std::unordered_map<int, double>
    computeTFIDF(
        const std::vector<std::string>& query,
        const std::unordered_map<std::string,
            std::unordered_map<int, std::vector<int>>>& index,
        int totalDocs
    );
};

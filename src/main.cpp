#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

#include "core/SearchEngine.h"

int main() {
    SearchEngine engine;

    std::ifstream file("big_docs.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open big_docs.txt\n";
        return 1;
    }

    std::string line;
    int docId = 1;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, line)) {
        Document doc{docId++, line};
        engine.indexDocuments({doc});
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Indexed " << (docId - 1) << " documents.\n";
    std::cout << "Indexing time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end - start
                 ).count()
              << " ms\n";

    std::string query;
    while (true) {
        std::cout << "\nQuery (exit to quit): ";
        std::getline(std::cin, query);
        if (query == "exit") break;

        auto results = engine.searchRanked(query, 5);
        std::cout << "Ranked Results: ";
        for (int id : results) std::cout << id << " ";
        std::cout << "\n";
    }
}

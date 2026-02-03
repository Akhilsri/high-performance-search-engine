# High-Performance Search Engine (C++)

A high-performance, algorithm-driven search engine implemented in C++, designed to efficiently index and retrieve documents using core information-retrieval techniques.

## Features
- Positional inverted index for fast keyword-based document retrieval
- TF-IDF–based relevance ranking
- Heap-optimized Top-K search (O(N log K))
- Exact phrase search using positional indexing
- Trie-based autocomplete for prefix queries
- Scalable to large document collections with low query latency

## Tech Stack
- C++
- STL (unordered_map, vector, priority_queue)
- File I/O

## Author

Akhil Srivastava

## How to Run
```bash
g++ src/main.cpp src/core/*.cpp -I src -std=c++17 -O2 -o search
./search

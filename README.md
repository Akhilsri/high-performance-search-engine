# High-Performance Search Engine (C++)

A high-performance, algorithm-driven search engine implemented in C++.

## Features
- Positional Inverted Index
- TF-IDF based relevance ranking
- Heap-optimized Top-K search
- Exact phrase search
- Trie-based autocomplete
- Scalable to large document collections

## Tech Stack
- C++
- STL (unordered_map, vector, priority_queue)
- File I/O

## How to Run
```bash
g++ src/main.cpp src/core/*.cpp -I src -std=c++17 -O2 -o search
./search

## Author

Akhil Srivastava

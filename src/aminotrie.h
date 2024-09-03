#ifndef AMINOTRIE_AMINOTRIE_H
#define AMINOTRIE_AMINOTRIE_H

#include <atomic>
#include <cstddef>
#include <mutex>

#define ALPHABET_SIZE 20

class AminoTrieNode {
  uint64_t children_idx[ALPHABET_SIZE];
};

class AminoTrie {
  char *backing_memory = nullptr;
  size_t mem_size = 0;
  std::mutex resize_mutex;
  std::atomic<size_t> next_free;

public:
  AminoTrie();
  ~AminoTrie();
  AminoTrieNode* new_node();
  inline AminoTrieNode &offset_to_node(size_t offset) { return }
};

class AminoTrieTraveller {
    AminoTrie& base_tree;
    AminoTrieNode *empty_node;
public:
    AminoTrieTraveller(AminoTrie& AT) : base_tree(AT), empty_node(AT.new_node());
}

#endif /* AMINOTRIE_AMINOTRIE_H */
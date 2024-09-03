#include <sys/mman.h>

#include "aminotrie.h"


AminoTrie::AminoTrie()
{
    std::lock_guard<std::mutex> lock(resize_mutex);
    mem_size = sizeof(AminoTrieNode) * 4096;
    backing_memory = static_cast<char*>(mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
    new_node();
}

AminoTrie::~AminoTrie()
{
    munmap(backing_memory, mem_size);
}

void AminoTrie::resize(size_t new_size)
{
    std::lock_guard<std::mutex> lock(resize_mutex);
    if(new_size > mem_size) return;
    const size_t old_size = mem_size;
    while(new_size > mem_size) mem_size *= 2;
    backing_memory = mremap(backing_memory, old_size, mem_size, MREMAP_MAYMOVE);
}

AminoTrieNode AminoTrie::new_node()
{
    size_t next_offset = next_free.fetch_add(sizeof(AminoTrieNode), std::memory_order_relaxed);
    if(next_offset + sizeof(AminoTrieNode) >= mem_size)
        resize(next_offset + sizeof(AminoTrieNode));
    auto next_ptr = backing_memory + next_offset;
    return *(new (next_ptr) AminoTrieNode());
}

AminoTrieNode& AminoTrie::travel(AminoTrieNode& current, uint8_t next_letter)
{
    
}

AminoTrie::add_seq(const std::vector<uint8_t>& seq, uint64_t id)
{

}
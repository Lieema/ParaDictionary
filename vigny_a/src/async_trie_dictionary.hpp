#pragma once
#include <future>
#include <mutex>
#include <string>
#include <vector>

#include "IAsyncDictionary.hpp"
#include "trie_dictionary.hpp"

class AsyncTrieDictionary : public IAsyncDictionary
{
  public:
    AsyncTrieDictionary();
    void init(const std::vector<std::string>& word_list);
    std::future<result_t> search(const std::string& w) const;
    std::future<void> insert(const std::string& w);
    std::future<void> erase(const std::string& w);

    friend class TrieDictionary;

  private:
    mutable std::mutex mutex_;
    TrieDictionary trie_;
};
